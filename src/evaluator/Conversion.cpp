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
Rounds to nearest integer first. If @a val is to big to fit into
return value, cyclic arithmetic of 2's complement is simulated */
template <class unsignedIntegerType>
unsignedIntegerType Conversion::convert(RealConstPtr val) {
	unsignedIntegerType retv;
	
	// First, we need to get multiple precision integer from Real
	mpz_t roundedInt;
	mpz_init(roundedInt);
	mpfr_get_z(roundedInt, val, MPFR_RNDN);

	// max value that can fit into unsignedIntegerType
	// mpz_init_set_ui(intTemp, tmp); -> This won't work for 64bit integers on all platforms
	// they could get truncated while using mpz_init_ui and similar methods. Instead we use 
	// Qt strings for intermediary data type. These strings allow conversion from/to long long
	QByteArray intStr = QByteArray::number(static_cast<unsignedIntegerType>(-1), 10);
	mpz_t maxUnsigned;
	mpz_init_set_str(maxUnsigned, intStr.constData(), 10);

	// Now we need to convert it to fixed width unsigned integer
	// simulating fixed width integers behavior (cyclic arithmetic)
	if (mpz_sgn(roundedInt) >= 0) {
		if (mpz_cmp(roundedInt, maxUnsigned) > 0) {
			mpz_mod(roundedInt, roundedInt, maxUnsigned);
			mpz_get_str(intStr.data(), 10, roundedInt);
			retv = static_cast<unsignedIntegerType>(intStr.toULongLong()) - 1;
		} else {
			mpz_get_str(intStr.data(), 10, roundedInt);
			retv = static_cast<unsignedIntegerType>(intStr.toULongLong());
		}
	} else {
		mpz_t intervalNum;
		mpz_init(intervalNum);
		mpz_mul_si(maxUnsigned, maxUnsigned, -1);
		mpz_tdiv_q(intervalNum, roundedInt, maxUnsigned);
		mpz_add(roundedInt, roundedInt, intervalNum);
		mpz_mul_si(maxUnsigned, maxUnsigned, -1);
		mpz_mul(intervalNum, intervalNum, maxUnsigned);
		mpz_add(roundedInt, roundedInt, intervalNum);

		if (mpz_sgn(roundedInt) < 0) {
			mpz_add(roundedInt, roundedInt, maxUnsigned);
			mpz_add_ui(roundedInt, roundedInt, 1);
		}

		mpz_get_str(intStr.data(), 10, roundedInt);
		retv = static_cast<unsignedIntegerType>(intStr.toULongLong());
		mpz_clear(intervalNum);
	}
	mpz_clear(maxUnsigned);
	mpz_clear(roundedInt);
	return retv;
}

void Conversion::mpfr_set_quint64(RealPtr dest, const quint64& src) {
	assert(dest != 0);
	QByteArray numStr = QByteArray::number(src, 10);
	mpfr_set_str(dest, numStr.constData(), 10, MPFR_RNDN);
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

bool Conversion::isBelowZeroTreshold(RealConstPtr val, const Settings& sett) {
	assert(val != 0);
	bool retv;
	if (sett.showSmallNumbersAsZero()) {
		RealPtr tres = BridgeAPIGlobals::newMrReal();
		mpfr_set_ui(tres, 10, MPFR_RNDN);
		mpfr_pow_si(tres, tres, sett.zeroTresholdExp(), MPFR_RNDN);
		retv = mpfr_cmpabs(val, tres) <= 0;
	} else {
		retv = false;
	}
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

// 	char c[100];
// 	mpfr_snprintf(&dec[0], 100, "%.*RNf", sett.precision(), val);

	if (isBelowZeroTreshold(im_disp, sett)) {
		mpfr_set_ui(im_disp, 0, MPFR_RNDN);
	}
	if (isBelowZeroTreshold(re_disp, sett)) {
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
	assert(val != 0);
	QLocale loc = QLocale::c();
	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
	QString bho_prefix, retv;

	switch (base) {
		case BINARY:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(val);
					retv += QString::number(tmpI64, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(64, '0');
					}
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(val);
					retv += QString::number(tmpI32, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(32, '0');
					}
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(val);
					retv += QString::number(tmpI16, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(val);
					retv += QString::number(tmpI8, 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(8, '0');
					}
					break;
			}
			if (sett.outputDigitGrouping()) {
				insertFromBack(retv, retv.length(), 8, ' ');
				if (sett.showBasePrefix()) {
					retv.insert(0, "0b ");
				}
			} else {
				if (sett.showBasePrefix()) {
					retv.insert(0, "0b");
				}
			}
			break;
		case HEXADECIMAL:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(val);
					retv += QString::number(tmpI64, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(val);
					retv += QString::number(tmpI32, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(8, '0');
					}
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(val);
					retv += QString::number(tmpI16, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(4, '0');
					}
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(val);
					retv += QString::number(tmpI8, 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(2, '0');
					}
					break;
			}
			if (sett.outputDigitGrouping()) {
				insertFromBack(retv, retv.length(), 2, ' ');
				if (sett.showBasePrefix()) {
					retv.insert(0, "0x ");
				}
			} else {
				if (sett.showBasePrefix()) {
					retv.insert(0, "0x");
				}
			}
			break;
		case OCTAL:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = convert_u64b(val);
					retv += QString::number(tmpI64, 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(24, '0');
					}
					break;
				case Settings::BW32:
					tmpI32 = convert_u32b(val);
					retv += QString::number(tmpI32, 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(12, '0');
					}
					break;
				case Settings::BW16:
					tmpI16 = convert_u16b(val);
					retv += QString::number(tmpI16, 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(6, '0');
					}
					break;
				case Settings::BW8:
					tmpI8 = convert_u8b(val);
					retv += QString::number(tmpI8, 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(3, '0');
					}
					break;
			}
			if (sett.outputDigitGrouping()) {
				insertFromBack(retv, retv.length(), 3, ' ');
				if (sett.showBasePrefix()) {
					retv.insert(0, "0 ");
				}
			} else {
				if (sett.showBasePrefix()) {
					retv.insert(0, "0");
				}
			}
			break;
		case DECIMAL:
		default:
			char dec[100]; // 100 should be more than enough
			if (sett.outputFormat() == Settings::AUTOMATIC) { 
				mpfr_snprintf(&dec[0], 100, "%.*RNg", sett.precision(), val);
			} else if (sett.outputFormat() == Settings::SCIENTIFFIC) {
				mpfr_snprintf(&dec[0], 100, "%.*RNe", sett.precision(), val);
			} else if (sett.outputFormat() == Settings::FIXED) {
				mpfr_snprintf(&dec[0], 100, "%.*RNf", sett.precision(), val);	
			}

			retv = QString::fromAscii(&dec[0]);

			// Post processing

			bool minusRemoved = false;
			if (retv[0] == '-') {
				retv.remove(0, 1);
				minusRemoved = true;
			}

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

			if (minusRemoved) {
				retv.insert(0, '-');
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
	if (startPos >= 0 && startPos <= dest.length()) {
		for (startPos -= step; startPos > 0; startPos -= step) {
			dest.insert(startPos, what);
		}
	} 
}

} // namespace mathy_resurrected

