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
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <QLocale>
#include "Exceptions.h"
#include "Settings.h"

using namespace std;
using namespace boost;
using namespace boost::math;

namespace mathy_resurrected {

qint8 Conversion::safe_convert_8b(Real val, bool& ok) {
	return safe_convert<qint8>(val, ok);
}

qint16 Conversion::safe_convert_16b(Real val, bool& ok) {
	return safe_convert<qint8>(val, ok);
}

qint32 Conversion::safe_convert_32b(Real val, bool& ok) {
	return safe_convert<qint32>(val, ok);
}

qint64 Conversion::safe_convert_64b(Real val, bool& ok) {
	return safe_convert<qint64>(val, ok);
}

quint8 Conversion::safe_convert_u8b(Real val, bool& ok) {
	return safe_convert<quint8>(val, ok);
}

quint16 Conversion::safe_convert_u16b(Real val, bool& ok) {
	return safe_convert<quint16>(val, ok);
}

quint32 Conversion::safe_convert_u32b(Real val, bool& ok) {
	return safe_convert<quint32>(val, ok);
}

quint64 Conversion::safe_convert_u64b(Real val, bool& ok) {
	return safe_convert<quint64>(val, ok);
}

template <class intT>
intT Conversion::safe_convert(Real val, bool& ok) {
	intT retv;
//	try {
// 		retv = numeric_cast<intT>(val);
// 		ok = true;
// 	}
// 	catch (bad_numeric_cast&) {
// 		ok = false;
// 	}
	retv = val; ok = true;
	return retv;
}

Real Conversion::strToReal (const QByteArray& strin) {
	Real retv;
	bool okFlag;
	retv = strin.toDouble(&okFlag);

	if (!okFlag) {
		throw NumericConversionError("Input conversion error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}
	return retv;
}

Real Conversion::strHexToReal (const QByteArray& strin) {
	Real retv;
	quint64 tempRetv;
	bool okFlag;
	tempRetv = strin.toULongLong(&okFlag, 16);

	if (!okFlag) {
		throw NumericConversionError("Input conversion error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}
	try {
		retv = numeric_cast<Real>(tempRetv);
	}
	catch (bad_numeric_cast&) {
		throw NumericConversionError("Input range error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}

	return retv;
}

Real Conversion::strOctToReal (const QByteArray& strin) {
	Real retv;
	quint64 tempRetv;
	bool okFlag;
	tempRetv = strin.toULongLong(&okFlag, 8);

	if (!okFlag) {
		throw NumericConversionError("Input conversion error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}
	try {
		retv = numeric_cast<Real>(tempRetv);
	}
	catch (bad_numeric_cast&) {
		throw NumericConversionError("Input range error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}

	return retv;
}

Real Conversion::strBinToReal (const QByteArray& strin) {
	Real retv;
	quint64 tempRetv;
	bool okFlag;
	tempRetv = strin.toULongLong(&okFlag, 2);

	if (!okFlag) {
		throw NumericConversionError("Input conversion error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}
	try {
		retv = numeric_cast<Real>(tempRetv);
	}
	catch (bad_numeric_cast&) {
		throw NumericConversionError("Input range error: " + 
			QString::fromUtf8(strin.constData(), strin.length()).toStdString());
	}

	return retv;
}

QString Conversion::toString(NumberBase base, const Settings& sett, const Complex& num) {
	QString im_sign;
	QString re_str, im_str;
	bool add_i = false;
	QString retv;

	// If number is close enough to zero, we make it zero 
	// explicitly (but for display purposes only)
	Real im_disp = num.imag, re_disp = num.real;
	if (abs(im_disp) < pow(10.0, sett.zeroTresholdExp())) {
		im_disp = 0;
	}
	if (abs(re_disp) < pow(10.0, sett.zeroTresholdExp())) {
		re_disp = 0;
	}

	// Formating output of imaginary part
	if ((boost::math::fpclassify)(im_disp) != FP_ZERO) {
		// Display as decimal
		if (base == DECIMAL) {
			if (im_disp > 0) {
				im_sign = " + ";
			} else { // if (imag < 0) {
				im_sign = " - ";
			}
			Real tmp = abs(im_disp);
			im_str = numberToString(base, sett, tmp);
		} else { // Display as any other base
			im_sign = " + ";
			im_str = numberToString(base, sett, im_disp);
		}
		add_i = true;
	}
	re_str = numberToString(base, sett, re_disp);
	retv = re_str;
	if (add_i) {
		retv +=  im_sign + im_str + "i";
	}
	return retv;
}

QString Conversion::numberToString(NumberBase base, const Settings& sett, Real val) {
	QLocale loc = QLocale::c();
	bool ok_flag;
	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
	QString bho_sign, bho_prefix, retv;
// 	if (val < 0) {
// 		bho_sign = "-";
// 	}
//	Real absVal = abs(val);
	Real absVal = val;
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
			retv.insert(0, bho_sign);
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
			retv.insert(0, bho_sign);
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
			retv.insert(0, bho_sign);
			break;
		case DECIMAL:
		default:
			if (sett.outputFormat() == Settings::AUTOMATIC) { 
				retv = loc.toString(val, 'g', sett.precision());
			} else if (sett.outputFormat() == Settings::SCIENTIFFIC) {
				retv = loc.toString(val, 'e', sett.precision());
			} else if (sett.outputFormat() == Settings::FIXED) {
				retv = loc.toString(val, 'f', sett.precision());		
			}

			// Post processing

			// First, "saving" decimal point from modification.
			// This is relatively safe because internally used 
			// character for decimal point representation is 
			// not likely to be used for that purpose in any 
			// existing locale. 
			retv.replace(loc.decimalPoint(), internalDecimalPoint());

			// Post processing group separator. 
			if (!sett.outputDigitGrouping()) {
				retv.remove(loc.groupSeparator());
			} else {
				retv.replace(loc.groupSeparator(), sett.digitGroupingCharacterAsChar());
			}

			// Post processing decimal point. 
			retv.replace(internalDecimalPoint(), sett.decimalPointAsChar());

			break;
	}

	return retv;
}


} // namespace mathy_resurrected

