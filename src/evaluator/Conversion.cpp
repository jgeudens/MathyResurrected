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
//!
//! @file
//! @author Tomislav Adamic <tomislav.adamic@gmail.com>
//!

// This is needed because of bad design in windows.h where 
// min and max macros are defined globally creating name
// clash with their other uses.
// http://support.microsoft.com/kb/143208
#ifdef _MSC_VER
	#define NOMINMAX
#endif // MSVC

#include "Conversion.h"
#include <QLocale>
#include <QtGlobal>
#include <cassert>
#include <limits>
#include "Settings.h"

using namespace std;

namespace mathy_resurrected {

//! Number of bits used for all number representations.
const int Conversion::MAX_BINARY_DIGITS = 164;

//! Default rounding mode used for calculations with real numbers.
const mpfr_rnd_t Conversion::defaultRoundingMode() {
	return MPFR_RNDN;
}

//! Default rounding mode used for calculations with complex numbers.
const mpc_rnd_t Conversion::defaultComplexRoundingMode() {
	return MPC_RNDNN;
}

//! Converts @a val into 8-bit, unsigned integer type (rounding towards 
//! nearest and converting negative numbers using 2k complement)
quint8 Conversion::convert_u8b(RealConstPtr val) {
	return convert_uint<quint8>(val);
}

//! Converts @a val into 16-bit, unsigned integer type (rounding towards 
//! nearest and converting negative numbers using 2k complement)
quint16 Conversion::convert_u16b(RealConstPtr val) {
	return convert_uint<quint16>(val);
}

//! Converts @a val into 32-bit, unsigned integer type (rounding towards 
//! nearest and converting negative numbers using 2k complement)
quint32 Conversion::convert_u32b(RealConstPtr val) {
	return convert_uint<quint32>(val);
}

//! Converts @a val into 64-bit, unsigned integer type (rounding towards 
//! nearest and converting negative numbers using 2k complement)
quint64 Conversion::convert_u64b(RealConstPtr val) {
	return convert_uint<quint64>(val);
}

//! Generic converter from real numbers to unsigned integers.
//! Rounds towards nearest and converts negative numbers using 2k 
//! complement. Works only for types defined by std::numeric_limits
//! or types that fall-back to std::numeric_limits.
template<class unsignedIntegerT>
unsignedIntegerT Conversion::convert_uint (RealConstPtr val) {
	// Converting input real number to integer
	mpz_t roundedInt;
	mpz_init(roundedInt);
	mpfr_get_z(roundedInt, val, defaultRoundingMode());

	// Getting binary string representation
	unsignedIntegerT retv;
	QByteArray ba;

	// This will crash for val = 1e60:
	// char binstr[MAX_BINARY_DIGITS + 2];
	// mpz_get_str(&binstr[0], 2, roundedInt);
	// mpz_clear(roundedInt);

	// Below implementation is more complex one, but at least hasn't crashed 
	char *binstr = mpz_get_str(0, 2, roundedInt);
	ba = QByteArray(binstr);
	mpz_clear(roundedInt);
	void (*freefunc) (void *, size_t);
	mp_get_memory_functions (NULL, NULL, &freefunc);
	freefunc(binstr, strlen(binstr) + 1);

	// Processing result
	// If number doesn't fit into given bit width, only lower bits are 
	// returned. Additionally, negative numbers are converted using 2k 
	// complement.
	if (ba[0] == '-') {
		ba.remove(0, 1);
		retv = static_cast<unsignedIntegerT>(
			ba.right(numeric_limits<unsignedIntegerT>::digits).toULongLong(0, 2)
		);
		retv = ~retv;
		retv += 1;
	} else {
		retv = static_cast<unsignedIntegerT>(
			ba.right(numeric_limits<unsignedIntegerT>::digits).toULongLong(0, 2)
		);
	}
	return retv;
}

//! Implements safe way to set quint64 64 bit integers on all platforms
//! including 32bit ones. Native mpfr_set_ui might or might not work
//! because it uses native unsigned long type, which on 32b platforms 
//! might be either 32b or 64b long. On the other side, quint64 is 
//! guaranteed 64b long but there is no native function to convert it 
//! into mpfr_t.
void Conversion::mpfr_set_quint64(RealPtr dest, const quint64& src) {
	assert(dest != 0);
	QByteArray numStr = QByteArray::number(src, 10);
	mpfr_set_str(dest, numStr.constData(), 10, defaultRoundingMode());
}

//! Converts ANTLR3 string into real number. This is used in tree parser 
//! grammar. Because of that, method doesn't check if given string is 
//! numeric string (ANTLR parser already has done that before method is 
//! called). Thus, if @a str is not numeric string, method call results in 
//! undefined behavior.
void Conversion::strToReal (const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QString temp = QString::fromUtf8((const char*)utf8Str->chars, utf8Str->len);
	temp.replace(Conversion::internalDecimalPoint(), QChar('.'));
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	mpfr_set_str(dest, temp.toUtf8().constData(), 10, defaultRoundingMode());
}

//! Converts ANTLR3 string into real number. This is used in tree parser 
//! grammar. Because of that, method doesn't check if given string is 
//! numeric string (ANTLR parser already has done that before method is 
//! called). Thus, if @a str is not numeric string, method call results in 
//! undefined behavior.
void Conversion::strHexToReal (const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	mpfr_set_str(dest, bArray.constData(), 16, defaultRoundingMode());
}

//! Converts ANTLR3 string into real number. This is used in tree parser 
//! grammar. Because of that, method doesn't check if given string is 
//! numeric string (ANTLR parser already has done that before method is 
//! called). Thus, if @a str is not numeric string, method call results in 
//! undefined behavior.
void Conversion::strOctToReal (const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	mpfr_set_str(dest, bArray.constData(), 8, defaultRoundingMode());
}

//! Converts ANTLR3 string into real number. This is used in tree parser 
//! grammar. Because of that, method doesn't check if given string is 
//! numeric string (ANTLR parser already has done that before method is 
//! called). Thus, if @a str is not numeric string, method call results in 
//! undefined behavior.
void Conversion::strBinToReal (const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	mpfr_set_str(dest, bArray.constData(), 2, defaultRoundingMode());
}

//! Checks is @a val is smaller that some number in @a sett. 
//! This is for display purposes: in @a sett there is an option to display 
//! all numbers smaller that zero threshold number as zeros. 
bool Conversion::isBelowZeroTreshold(RealConstPtr val, const Settings& sett) {
	assert(val != 0);
	bool retv;
	if (sett.showSmallNumbersAsZero()) {
		Real tres;
		mpfr_init2(tres, MAX_BINARY_DIGITS);
		mpfr_set_ui(tres, 10, defaultRoundingMode());
		mpfr_pow_si(tres, tres, sett.zeroTresholdExp(), defaultRoundingMode());
		retv = mpfr_cmpabs(val, tres) <= 0;
		mpfr_clear(tres);
	} else {
		retv = false;
	}
	return retv;
}

//! Converts @a num to string representation for given number base @a base 
//! and user settings @a sett. 
const QString Conversion::toString(NumberBase base, const Settings& sett, const ComplexConstPtr& num) {
	QString im_sign;
	QString re_str, im_str;
	bool add_i = false;
	QString retv;

	// If number is close enough to zero, we make it zero 
	// explicitly (but for display purposes only)
	Real re_disp, im_disp;
	mpfr_init2(re_disp, MAX_BINARY_DIGITS);
	mpfr_init2(im_disp, MAX_BINARY_DIGITS);
	mpfr_set(re_disp, mpc_realref(num), defaultRoundingMode());
	mpfr_set(im_disp, mpc_imagref(num), defaultRoundingMode());

	if (isBelowZeroTreshold(im_disp, sett)) {
		mpfr_set_ui(im_disp, 0, defaultRoundingMode());
	}
	if (isBelowZeroTreshold(re_disp, sett)) {
		mpfr_set_ui(re_disp, 0, defaultRoundingMode());
	}

	// Formating output of imaginary part
	if (mpfr_sgn(im_disp) != 0) {
		if (base == DECIMAL) {
			if (mpfr_sgn(im_disp) > 0) {
				im_sign = " + ";
			} else {
				im_sign = " - ";
			}
			mpfr_abs(im_disp, im_disp, defaultRoundingMode());
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

//! Converts @a val to string representation for given number base @a base 
//! and user settings @a sett. 
const QString Conversion::numberToString(NumberBase base, const Settings& sett, RealConstPtr val) {
	assert(val != 0);
	QLocale loc = QLocale::c();
	QString bho_prefix, retv;

	switch (base) {
		case BINARY:
			switch (sett.calculationBitWidth()) {
				case Settings::BW64:
					retv += QString::number(convert_uint<quint64>(val), 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(64, '0');
					}
					break;
				case Settings::BW32:
					retv += QString::number(convert_uint<quint32>(val), 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(32, '0');
					}
					break;
				case Settings::BW16:
					retv += QString::number(convert_uint<quint16>(val), 2);
					if (sett.showLeadingZeroesBin()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW8:
					retv += QString::number(convert_uint<quint8>(val), 2);
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
					retv += QString::number(convert_uint<quint64>(val), 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(16, '0');
					}
					break;
				case Settings::BW32:
					retv += QString::number(convert_uint<quint32>(val), 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(8, '0');
					}
					break;
				case Settings::BW16:
					retv += QString::number(convert_uint<quint16>(val), 16).toUpper();
					if (sett.showLeadingZeroesHex()) {
						retv = retv.rightJustified(4, '0');
					}
					break;
				case Settings::BW8:
					retv += QString::number(convert_uint<quint8>(val), 16).toUpper();
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
					retv += QString::number(convert_uint<quint64>(val), 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(24, '0');
					}
					break;
				case Settings::BW32:
					retv += QString::number(convert_uint<quint32>(val), 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(12, '0');
					}
					break;
				case Settings::BW16:
					retv += QString::number(convert_uint<quint16>(val), 8);
					if (sett.showLeadingZeroesOct()) {
						retv = retv.rightJustified(6, '0');
					}
					break;
				case Settings::BW8:
					retv += QString::number(convert_uint<quint8>(val), 8);
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
			char dec[100]; // 100 digits for result should be more than enough
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

//! Inserts @a what into @a dest putting first character on position
//! @a pos and other characters in positions backward from original 
//! in steps determined by @a step. 
//! @warning For speed sake, doesn't check validity of any of it's params.
void Conversion::insertFromBack(QString& dest, int startPos, int step, const QChar& what) {
	if (startPos >= 0 && startPos <= dest.length()) {
		for (startPos -= step; startPos > 0; startPos -= step) {
			dest.insert(startPos, what);
		}
	} 
}

} // namespace mathy_resurrected

