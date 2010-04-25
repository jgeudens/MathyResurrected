/* 
* Copyright (C) 2009
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

#ifndef MATHY_RESURRECTED_EXCEPTIONS
#define MATHY_RESURRECTED_EXCEPTIONS

#include <stdexcept>
#include <string>

namespace mathy_resurrected {

/*! Base class for MathyResurrected exceptions. */
class MathyResurrectedException : public std::exception {
public:
	MathyResurrectedException();
	MathyResurrectedException(const std::string& message);
};

class NaN : public MathyResurrectedException {
public:
	NaN();
};

class NumericConversionError : public MathyResurrectedException {
public:
	NumericConversionError(const std::string& exp);
};

class DomainError : public MathyResurrectedException {
public:
	DomainError();
};

class IllegalOperand : public MathyResurrectedException {
public:
	IllegalOperand();
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_EXCEPTIONS
