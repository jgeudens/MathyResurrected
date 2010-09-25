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

#ifndef MATHY_RESURRECTED_CONVERSION_H
#define MATHY_RESURRECTED_CONVERSION_H

#include <QString>
#include <QByteArray>
#include "math_bridge_API_types.h"

namespace mathy_resurrected {

class Settings;

/** Class responsible for conversion between numeric and 
string representation of numeric types*/
class Conversion {
public:
	static qint8 safe_convert_8b(Real val, bool& ok);
	static qint16 safe_convert_16b(Real val, bool& ok);
	static qint32 safe_convert_32b(Real val, bool& ok);
	static qint64 safe_convert_64b(Real val, bool& ok);
	static quint8 safe_convert_u8b(Real val, bool& ok);
	static quint16 safe_convert_u16b(Real val, bool& ok);
	static quint32 safe_convert_u32b(Real val, bool& ok);
	static quint64 safe_convert_u64b(Real val, bool& ok);

	static Real strToReal(const QByteArray& str);
	static Real strHexToReal(const QByteArray& str);
	static Real strOctToReal(const QByteArray& str);
	static Real strBinToReal(const QByteArray& str);

	enum NumberBase {
		DECIMAL, HEXADECIMAL, BINARY, OCTAL
	};
	static const QString toString(NumberBase base, const Settings& sett, const Complex& num);

	/*! This should return same character that was used in grammar */
	static const QChar internalDecimalPoint() { return QChar('@'); }
	/*! This should return same character that was used in grammar */
	static const QChar internalArgSeparator() { return QChar('#'); }

private:
	static const QString numberToString(NumberBase base, const Settings& sett, Real val);
	template <class intT>
	static intT safe_convert(Real val, bool& ok);
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_CONVERSION_H
