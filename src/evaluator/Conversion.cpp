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
#include "Settings.h"
#include "math_bridge_globals.h"

using namespace std;

namespace mathy_resurrected {

quint8 Conversion::safe_convert_u8b(RealConstPtr val, bool& ok) {
	return safe_convert<quint8>(val, ok);
}

quint16 Conversion::safe_convert_u16b(RealConstPtr val, bool& ok) {
	return safe_convert<quint16>(val, ok);
}

quint32 Conversion::safe_convert_u32b(RealConstPtr val, bool& ok) {
	return safe_convert<quint32>(val, ok);
}

quint64 Conversion::safe_convert_u64b(RealConstPtr val, bool& ok) {
	return safe_convert<quint64>(val, ok);
}

/** @todo Currently always sets @a ok to true. */
template <class unsignedIntegerType>
unsignedIntegerType Conversion::safe_convert(RealConstPtr val, bool& ok) {
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
	ok = true;
	return retv;
}

RealPtr Conversion::strToReal (const QByteArray& strin) {
	RealPtr retv = BridgeAPIGlobals::newMrReal();
	mpfr_set_str(retv, strin.constData(), 10, MPFR_RNDN);
	return retv;
}

RealPtr Conversion::strHexToReal (const QByteArray& strin) {
	RealPtr retv = BridgeAPIGlobals::newMrReal();
	mpfr_set_str(retv, strin.constData(), 16, MPFR_RNDN);
	return retv;
}

RealPtr Conversion::strOctToReal (const QByteArray& strin) {
	RealPtr retv = BridgeAPIGlobals::newMrReal();
	mpfr_set_str(retv, strin.constData(), 8, MPFR_RNDN);
	return retv;
}

RealPtr Conversion::strBinToReal (const QByteArray& strin) {
	RealPtr retv = BridgeAPIGlobals::newMrReal();
	mpfr_set_str(retv, strin.constData(), 2, MPFR_RNDN);
	return retv;
}

bool Conversion::isBelowZeroTreshold(RealConstPtr val, int treshExp) {
	Real valCopy, tres;
	bool retv;
	mpfr_init_set(valCopy, val, MPFR_RNDN);
	mpfr_init_set_ui(tres, 10, MPFR_RNDN);
	mpfr_pow_ui(tres, tres, treshExp, MPFR_RNDN);
	retv = mpfr_cmpabs(valCopy, tres) <= 0;
	mpfr_clear(valCopy);
	mpfr_clear(tres);
	return retv;
}

const QString Conversion::toString(NumberBase base, const Settings& sett, const ComplexConstPtr& num) {
	QString im_sign;
	QString re_str, im_str;
	bool add_i = false;
	QString retv;

	// If number is close enough to zero, we make it zero 
	// explicitly (but for display purposes only)
	Real im_disp, re_disp;
	mpfr_init_set(re_disp, mpc_realref(num), MPFR_RNDN);
	mpfr_init_set(im_disp, mpc_imagref(num), MPFR_RNDN);
	if (isBelowZeroTreshold(im_disp, sett.zeroTresholdExp())) {
		mpfr_init_set_ui(im_disp, 0, MPFR_RNDN);
	}
	if (isBelowZeroTreshold(re_disp, sett.zeroTresholdExp())) {
		mpfr_init_set_ui(re_disp, 0, MPFR_RNDN);
	}

	// Formating output of imaginary part
	if (mpfr_zero_p(im_disp) != 0) {
		// Display as decimal
		if (base == DECIMAL) {
			if (mpfr_sgn(im_disp) >= 0) {
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

	mpfr_clear(re_disp);
	mpfr_clear(im_disp);
	return retv;
}

const QString Conversion::numberToString(NumberBase base, const Settings& sett, RealConstPtr val) {
	QLocale loc = QLocale::c();
	bool ok_flag;
	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
	QString bho_prefix, retv;
	Real absVal;
	mpfr_init_set(absVal, val, MPFR_RNDN);
	mpfr_abs(absVal, absVal, MPFR_RNDN);

	switch (base) {
		case BINARY:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 2);
						if (sett.showLeadingZeroesBin()) {
							retv = retv.rightJustified(64, '0');
						}
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 2);
						if (sett.showLeadingZeroesBin()) {
							retv = retv.rightJustified(32, '0');
						}
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 2);
						if (sett.showLeadingZeroesBin()) {
							retv = retv.rightJustified(16, '0');
						}
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 2);
						if (sett.showLeadingZeroesBin()) {
							retv = retv.rightJustified(8, '0');
						}
					} else {
						retv = "8b int range error";
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
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 16).toUpper();
						if (sett.showLeadingZeroesHex()) {
							retv = retv.rightJustified(16, '0');
						}
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 16).toUpper();
						if (sett.showLeadingZeroesHex()) {
							retv = retv.rightJustified(8, '0');
						}
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 16).toUpper();
						if (sett.showLeadingZeroesHex()) {
							retv = retv.rightJustified(4, '0');
						}
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 16).toUpper();
						if (sett.showLeadingZeroesHex()) {
							retv = retv.rightJustified(2, '0');
						}
					} else {
						retv = "8b int range error";
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
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 8);
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 8);
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 8);
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 8);
					} else {
						retv = "8b int range error";
					}
					break;
			}
			if (sett.showBasePrefix()) {
				retv.insert(0, "0");
			}
			break;
		case DECIMAL:
		default:
			char dec[100];
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
			retv[decPointPos] = internalDecimalPoint();

			// Post processing group separator. 
			if (sett.outputDigitGrouping() && sett.outputFormat() == Settings::FIXED) {
				for (decPointPos -= 3; decPointPos > 0; decPointPos -= 3) {
					retv.insert(decPointPos, sett.digitGroupingCharacterAsChar());
				} 
			}

			// Post processing decimal point. 
			retv[retv.lastIndexOf(internalDecimalPoint())] = sett.decimalPointAsChar();
			break;
	}

	mpfr_clear(absVal);
	return retv;
}

} // namespace mathy_resurrected

