/* 
* Copyright (C) 2009, 2010
* Tomislav Adamic <tomislav.adamic@gmail.com>
* 
* This file is part of MathyResurrected - Launchy advanced calculator plugin
* 
* MathyResurrected is free software: you can redistribute it and/or modify 
* it under the terms of the GNU General Public License as published by the 
* Free Software Foundation, either version 3 of the License, or (at your 
* option) any later version.
* 
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License 
* along with MathyResurrected. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Conversion.h"
#include <QLocale>
#include <cassert>
#include "Settings.h"
#include "math_bridge_globals.h"

using namespace std;

namespace mathy_resurrected {

quint8 Conversion::convert_u8b(RealConstPtr val) {
	return convert<quint8>(val);
}

quint16 Conversion::convert_u16b(RealConstPtr val) {
	return convert<quint16>(val);
}

quint32 Conversion::convert_u32b(RealConstPtr val) {
	return convert<quint32>(val);
}

quint64 Conversion::convert_u64b(RealConstPtr val) {
	return convert<quint64>(val);
}

/** Converts Real number to unsigned, fixed precision integer. 
Rounds to nearest integer first. If @a val is to be to fit into
return value, cyclic arithmetic of 2's complement is simulated */
template <class unsignedIntegerType>
unsignedIntegerType Conversion::convert(RealConstPtr val) {
	unsignedIntegerType retv, tmp;
	mpz_t intOut, intTemp;

	mpz_init(intOut);
	mpfr_get_z(intOut, val, MPFR_RNDN);

	// This simulates cyclic arithmetic of fixed precision integers
	tmp = -1;
	mpz_init_set_ui(intTemp, tmp);
	mpz_mod(intOut, intOut, intTemp);

	retv = static_cast<unsignedIntegerType>(mpz_get_ui(intOut));

	mpz_clear(intOut);
	mpz_clear(intTemp);
	return retv;
}

void Conversion::strToReal (const QByteArray& strin, RealPtr dest) {
	assert(dest != 0);
	mpfr_set_str(dest, strin.constData(), 10, MPFR_RNDN);
}

void Conversion::strHexToReal (const QByteArray& strin, RealPtr dest) {
	assert(dest != 0);
	mpfr_set_str(dest, strin.constData(), 16, MPFR_RNDN);
}

void Conversion::strOctToReal (const QByteArray& strin, RealPtr dest) {
	assert(dest != 0);
	mpfr_set_str(dest, strin.constData(), 8, MPFR_RNDN);
}

void Conversion::strBinToReal (const QByteArray& strin, RealPtr dest) {
	assert(dest != 0);
	mpfr_set_str(dest, strin.constData(), 2, MPFR_RNDN);
}

bool Conversion::isBelowZeroTreshold(RealConstPtr val, int treshExp) {
	RealPtr tres = BridgeAPIGlobals::newMrReal();
	bool retv;
	mpfr_set_ui(tres, 10, MPFR_RNDN);
	mpfr_pow_si(tres, tres, treshExp, MPFR_RNDN);
	retv = mpfr_cmpabs(val, tres) <= 0;
	return retv;
}

const QString Conversion::toString(NumberBase base, const Settings& sett, const ComplexConstPtr& num) {
	QString im_sign;
	QString re_str, im_str;
	bool add_i = false;
	QString retv;

	// If number is close enough to zero, we make it zero 
	// explicitly (but for display purposes only)
	RealPtr im_disp, re_disp;
	re_disp = BridgeAPIGlobals::newMrReal();
	im_disp = BridgeAPIGlobals::newMrReal();
	mpfr_set(re_disp, mpc_realref(num), MPFR_RNDN);
	mpfr_set(im_disp, mpc_imagref(num), MPFR_RNDN);

	if (isBelowZeroTreshold(im_disp, sett.zeroTresholdExp())) {
		mpfr_set_ui(im_disp, 0, MPFR_RNDN);
	}
	if (isBelowZeroTreshold(re_disp, sett.zeroTresholdExp())) {
		mpfr_set_ui(re_disp, 0, MPFR_RNDN);
	}

	// Formating output of imaginary part
	if (mpfr_sgn(im_disp) != 0) {
		if (base == DECIMAL) {
			if (mpfr_sgn(im_disp) > 0) {
				im_sign = " + ";
			} else {
				im_sign = " - ";
			}
			mpfr_abs(im_disp, im_disp, MPFR_RNDN);
		} else { // Display as any other base
			im_sign = " + ";
		}
		im_str = numberToString(base, sett, im_disp);
		add_i = true;
	}
	re_str = numberToString(base, sett, re_disp);
	retv = re_str;
	if (add_i) {
		retv +=  im_sign + im_str + "i";
	}

	return retv;
}

const QString Conversion::numberToString(NumberBase base, const Settings& sett, RealConstPtr val) {
	QLocale loc = QLocale::c();
	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
	QString bho_prefix, retv;
	RealPtr absVal = BridgeAPIGlobals::newMrReal();
	mpfr_set(absVal, val, MPFR_RNDN);
	mpfr_abs(absVal, absVal, MPFR_RNDN);

	switch (base) {
		case BINARY:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(absVal);
					retv += QString::number(tmpI64, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(64, '0');
					}
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(absVal);
					retv += QString::number(tmpI32, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(32, '0');
					}
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(absVal);
					retv += QString::number(tmpI16, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(absVal);
					retv += QString::number(tmpI8, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(8, '0');
					}
					break;
			}
			if (sett.showBasePrefix()) {
				retv.insert(0, "0b");
			}
			break;
		case HEXADECIMAL:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(absVal);
					retv += QString::number(tmpI64, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(absVal);
					retv += QString::number(tmpI32, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(8, '0');
					}
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(absVal);
					retv += QString::number(tmpI16, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(4, '0');
					}
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(absVal);
					retv += QString::number(tmpI8, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(2, '0');
					}
					break;
			}
			if (sett.showBasePrefix()) {
				retv.insert(0, "0x");
			}
			break;
		case OCTAL:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(absVal);
					retv += QString::number(tmpI64, 8);
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(absVal);
					retv += QString::number(tmpI32, 8);
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(absVal);
					retv += QString::number(tmpI16, 8);
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(absVal);
					retv += QString::number(tmpI8, 8);
					break;
			}
			if (sett.showBasePrefix()) {
				retv.insert(0, "0");
			}
			break;
		case DECIMAL:
		default:
			char dec[100]; // 100 should be more than enough
			if (sett.outputFormat() == Settings::AUTOMATIC) { 
				mpfr_snprintf(&dec[0], 100, "%.*RNg", sett.precision(), absVal);
			} else if (sett.outputFormat() == Settings::SCIENTIFFIC) {
				mpfr_snprintf(&dec[0], 100, "%.*RNe", sett.precision(), absVal);
			} else if (sett.outputFormat() == Settings::FIXED) {
				mpfr_snprintf(&dec[0], 100, "%.*RNf", sett.precision(), absVal);	
			}

			retv = QString::fromAscii(&dec[0]);

			// Post processing

			// First, "saving" decimal point from modification.
			// This is relatively safe because internally used 
			// character for decimal point representation is 
			// not likely to be used for that purpose in any 
			// existing locale. 
			int decPointPos = retv.lastIndexOf(loc.decimalPoint());
			if (decPointPos != -1) {
				retv[decPointPos] = internalDecimalPoint();
			} else {
				decPointPos = retv.size();
			}

			// Post processing group separator. 
			if (sett.outputDigitGrouping() && sett.outputFormat() == Settings::FIXED) {
				insertFromBack(retv, decPointPos, 3, sett.digitGroupingCharacterAsChar());
			}

			// Post processing decimal point. 
			decPointPos = retv.lastIndexOf(internalDecimalPoint());
			if (decPointPos != -1) {
				retv[decPointPos] = sett.decimalPointAsChar();
			}
			break;
	}
	return retv;
}

void Conversion::insertFromBack(QString& dest, int startPos, int step, const QChar& what) {
	if (startPos >= 0 && startPos < dest.length()) {
		for (startPos -= step; startPos > 0; startPos -= step) {
			dest.insert(startPos, what);
		}
	} 
}

} // namespace mathy_resurrected

