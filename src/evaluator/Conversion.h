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

#ifndef D04C6E81_4698_45A7_A791_CF3CCA4AD181_CONVERSION_H
#define D04C6E81_4698_45A7_A791_CF3CCA4AD181_CONVERSION_H

#include <QString>
#include <QByteArray>
#include "MathTypes.h"

namespace mathy_resurrected {

class Settings;

//! Class responsible for conversion between numeric and 
//! string representation of numeric types
class Conversion {
public:
	static const int MAX_BINARY_DIGITS;

	//! Supported input/output number bases.
	enum NumberBase {
		DECIMAL, HEXADECIMAL, BINARY, OCTAL
	};

	static quint8 convert_u8b(RealConstPtr val);
	static quint16 convert_u16b(RealConstPtr val);
	static quint32 convert_u32b(RealConstPtr val);
	static quint64 convert_u64b(RealConstPtr val);

	static void strToReal(const pANTLR3_STRING str, RealPtr dest);
	static void strHexToReal(const pANTLR3_STRING str, RealPtr dest);
	static void strOctToReal(const pANTLR3_STRING str, RealPtr dest);
	static void strBinToReal(const pANTLR3_STRING str, RealPtr dest);

	static const QString toString(NumberBase base, const Settings& sett, const ComplexConstPtr& num);

	//!
	//! This should return same character that was used in grammar 
	static const QChar internalDecimalPoint() { return QChar('@'); }
	//!
	//! This should return same character that was used in grammar 
	static const QChar internalArgSeparator() { return QChar('#'); }

	
	static void mpfr_set_quint64(RealPtr dest, const quint64& src);

	static const mpfr_rnd_t defaultRoundingMode();
	static const mpc_rnd_t defaultComplexRoundingMode();

private:
	static const QString numberToString(NumberBase base, const Settings& sett, RealConstPtr val);

	static bool isBelowZeroTreshold(RealConstPtr val, const Settings& sett);
	static void insertFromBack(QString& dest, int startPos, int step, const QChar& what); 

	template<class unsignedIntegerT>
	static unsignedIntegerT convert_uint (RealConstPtr val);
};

} // namespace mathy_resurrected

#endif // HEADER_GUARD
