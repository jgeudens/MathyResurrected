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

#include "math_bridge_API.h"
#include <cmath>
#include <complex>
#include <boost/math/complex.hpp>
#include "math_bridge_globals.h"
#include "Conversion.h"

using namespace boost;
using namespace boost::math;
using namespace std;
using namespace mathy_resurrected;

typedef std::complex<mrReal> StdComplex;

ComplexPtr newMrComplex() {
	return BridgeAPIGlobals::newMrComplex();
}

void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type) {
	BridgeAPIGlobals::collectlexerError(char_index, err_type);
}

ComplexConstPtr getAns() {
	return BridgeAPIGlobals::getAns();
}

/*! Converts between tree parser return value and std::complex<T> */
inline void MRCOMPLEX_2_STDCOMPLEX(StdComplex& dest, ComplexConstPtr src) {
	dest.real(src->real);
	dest.imag(src->imag);
}

/*! Converts between tree parser return value and std::complex<T> */
inline void STDCOMPLEX_2_MRCOMPLEX(ComplexPtr dest, const StdComplex& src) {
	dest->real = src.real();
	dest->imag = src.imag();
}

mrReal mr_pi() {
	static const mrReal 
		piVal = atan2((mrReal)(0.0), static_cast<mrReal>(-1.0));
	return piVal;
}

mrReal mr_e() {
	static const mrReal eVal = exp((mrReal)(1.0));
	return eVal;
}

mrReal si_ref(MR_MATH_SI_PREFIXES si_prefix) {
	mrReal suff_val;

	switch (si_prefix) {
		case MR_MATH_SI_PREFIX_YOTTA:
			suff_val = 1e24;
			break;
		case MR_MATH_SI_PREFIX_ZETTA:
			suff_val = 1e21;
			break;
		case MR_MATH_SI_PREFIX_EXA:
			suff_val = 1e18;
			break;
		case MR_MATH_SI_PREFIX_PETA:
			suff_val = 1e15;
			break;
		case MR_MATH_SI_PREFIX_TERA:
			suff_val = 1e12;
			break;
		case MR_MATH_SI_PREFIX_GIGA:
			suff_val = 1e9;
			break;
		case MR_MATH_SI_PREFIX_MEGA:
			suff_val = 1e6;
			break;
		case MR_MATH_SI_PREFIX_KILO:
			suff_val = 1e3;
			break;
		case MR_MATH_SI_PREFIX_HECTO:
			suff_val = 1e2;
			break;
		case MR_MATH_SI_PREFIX_DECA:
			suff_val = 1e1;
			break;
		case MR_MATH_SI_PREFIX_DECI:
			suff_val = 1e-1;
			break;
		case MR_MATH_SI_PREFIX_CENTI:
			suff_val = 1e-2;
			break;
		case MR_MATH_SI_PREFIX_MILLI:
			suff_val = 1e-3;
			break;
		case MR_MATH_SI_PREFIX_MICRO:
			suff_val = 1e-6;
			break;
		case MR_MATH_SI_PREFIX_NANO:
			suff_val = 1e-9;
			break;
		case MR_MATH_SI_PREFIX_PICO:
			suff_val = 1e-12;
			break;
		case MR_MATH_SI_PREFIX_FEMTO:
			suff_val = 1e-15;
			break;
		case MR_MATH_SI_PREFIX_ATTO:
			suff_val = 1e-18;
			break;
		case MR_MATH_SI_PREFIX_ZEPTO:
			suff_val = 1e-21;
			break;
		case MR_MATH_SI_PREFIX_YOCTO:
			suff_val = 1e-24;
			break;
		case MR_MATH_SI_PREFIX_KIBI:
			suff_val = pow (static_cast<double>(2), 10);
			break;
		case MR_MATH_SI_PREFIX_MEBI:
			suff_val = pow (static_cast<double>(2), 20);
			break;
		case MR_MATH_SI_PREFIX_GIBI:
			suff_val = pow (static_cast<double>(2), 30);
			break;
		case MR_MATH_SI_PREFIX_TEBI:
			suff_val = pow (static_cast<double>(2), 40);
			break;
		case MR_MATH_SI_PREFIX_PEBI:
			suff_val = pow (static_cast<double>(2), 50);
			break;
		case MR_MATH_SI_PREFIX_EXBI:
			suff_val = pow (static_cast<double>(2), 60);
			break;
		case MR_MATH_SI_PREFIX_ZEBI:
			suff_val = pow (static_cast<double>(2), 70);
			break;
		case MR_MATH_SI_PREFIX_YOBI:
			suff_val = pow (static_cast<double>(2), 80);
			break;
	}
	return suff_val;
}

ComplexPtr mr_binary_operator (MR_MATH_BINARY_OPERATORS which,
							   ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newMrComplex();
	StdComplex rv_c, lv_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(rv_c,rv);
	MRCOMPLEX_2_STDCOMPLEX(lv_c,lv);

	switch (which) {
		case MR_PLUS:
			retv_c = lv_c + rv_c;
			break;
		case MR_MINUS:
			retv_c = lv_c - rv_c;
			break;
		case MR_MULTI:
			retv_c = lv_c * rv_c;;
			break;
		case MR_DIV:
			retv_c = lv_c / rv_c;;
			break;
		case MR_MOD:
			retv_c.imag(0);
			retv_c.real(static_cast<mrReal>(fmod(lv->real, rv->real)));
			break;
		case MR_POW:
			retv_c = pow(lv_c, rv_c);
			break;
	}

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

ComplexPtr 
mr_binary_bitwise_operator (MR_MATH_BINARY_BITWISE_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newMrComplex();

	quint64 lv64, rv64;
	quint32 lv32, rv32;
	quint16 lv16, rv16;
	quint8 lv8, rv8;
	bool okFlag = false;

	switch (BridgeAPIGlobals::bitWidth()) {
		case 64:
			lv64 = Conversion::safe_convert_u64b(lv->real, okFlag);
			rv64 = Conversion::safe_convert_u64b(rv->real, okFlag);
			break;
		case 32:
			lv32 = Conversion::safe_convert_u32b(lv->real, okFlag);
			rv32 = Conversion::safe_convert_u32b(rv->real, okFlag);
			break;
		case 16:
			lv16 = Conversion::safe_convert_u16b(lv->real, okFlag);
			rv16 = Conversion::safe_convert_u16b(rv->real, okFlag);
			break;
		case 8:
			lv8 = Conversion::safe_convert_u8b(lv->real, okFlag);
			rv8 = Conversion::safe_convert_u8b(rv->real, okFlag);
			break;
	}

	if (okFlag) {
		retv->imag = 0;
		switch (which) {
			// bitwise AND
			case  MR_BITWISE_AND:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = lv64 & rv64;
						break;
					case 32:
						retv->real = lv32 & rv32;
						break;
					case 16:
						retv->real = lv16 & rv16;
						break;
					case 8:
						retv->real = lv8 & rv8;
						break;
				}
				break;
			// bitwise OR
			case  MR_BITWISE_OR:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = lv64 | rv64;
						break;
					case 32:
						retv->real = lv32 | rv32;
						break;
					case 16:
						retv->real = lv16 | rv16;
						break;
					case 8:
						retv->real = lv8 | rv8;
						break;
				}
				break;
			// bitwise NAND
			case  MR_BITWISE_NAND:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = ~(lv64 & rv64);
						break;
					case 32:
						retv->real = ~(lv32 & rv32);
						break;
					case 16:
						retv->real = ~(lv16 & rv16);
						break;
					case 8:
						retv->real = ~(lv8 & rv8);
						break;
				}
				break;
			// bitwise NOR
			case  MR_BITWISE_NOR:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = ~(lv64 | rv64);
						break;
					case 32:
						retv->real = ~(lv32 | rv32);
						break;
					case 16:
						retv->real = ~(lv16 | rv16);
						break;
					case 8:
						retv->real = ~(lv8 | rv8);
						break;
				}
				break;
			// bitwise XOR
			case  MR_BITWISE_XOR:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = lv64 ^ rv64;
						break;
					case 32:
						retv->real = lv32 ^ rv32;
						break;
					case 16:
						retv->real = lv16 ^ rv16;
						break;
					case 8:
						retv->real = lv8 ^ rv8;
						break;
				}
				break;
			// bitwise XNOR
			case  MR_BITWISE_XNOR:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = ~(lv64 ^ rv64);
						break;
					case 32:
						retv->real = ~(lv32 ^ rv32);
						break;
					case 16:
						retv->real = ~(lv16 ^ rv16);
						break;
					case 8:
						retv->real = ~(lv8 ^ rv8);
						break;
				}
				break;
			// bitwise shift left
			case  MR_BITWISE_SHL:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = lv64 << rv64;
						break;
					case 32:
						retv->real = lv32 << rv32;
						break;
					case 16:
						retv->real = lv16 << rv16;
						break;
					case 8:
						retv->real = lv8 << rv8;
						break;
				}
				break;
			// bitwise shift right
			case  MR_BITWISE_SHR:
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:	
						retv->real = lv64 >> rv64;
						break;
					case 32:
						retv->real = lv32 >> rv32;
						break;
					case 16:
						retv->real = lv16 >> rv16;
						break;
					case 8:
						retv->real = lv8 >> rv8;
						break;
				}
				break;
		}
	}

	return retv;
}

ComplexPtr mr_unary_operator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val) {
	ComplexPtr retv = newMrComplex();

	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
 	bool okFlag;

	switch (BridgeAPIGlobals::bitWidth()) {
		case 64:
			tmpI64 = Conversion::safe_convert_u64b(val->real, okFlag);
			break;
		case 32:
			tmpI32 = Conversion::safe_convert_u32b(val->real, okFlag);
			break;
		case 16:
			tmpI16 = Conversion::safe_convert_u16b(val->real, okFlag);
			break;
		case 8:
			tmpI8 = Conversion::safe_convert_u8b(val->real, okFlag);
			break;
	}

	if (okFlag) {
		switch (which) {
			case  MR_BITWISE_NOT:
				retv->imag = 0;
				switch (BridgeAPIGlobals::bitWidth()) {
					case 64:
						tmpI64 = ~tmpI64;
						retv->real = tmpI64;
						break;
					case 32:
						tmpI32 = ~tmpI32;
						retv->real = tmpI32;
						break;
					case 16:
						tmpI16 = ~tmpI16;
						retv->real = tmpI16;
						break;
					case 8:
						tmpI8 = ~tmpI8;
						retv->real = tmpI8;
						break;
				}
				break;
		}
	}

	return retv;
}

ComplexPtr mr_unary_function (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val) {
	ComplexPtr retv = newMrComplex();
	StdComplex arg_c, retv_c;
	MRCOMPLEX_2_STDCOMPLEX(arg_c, val);

	switch (which) {
		case MR_FUN_SIN:
			retv_c = std::sin(arg_c);
			break;;
		case MR_FUN_COS:
			retv_c = std::cos(arg_c);
			break;;
		case MR_FUN_TAN:
			retv_c = std::tan(arg_c);
			break;;
		case MR_FUN_ASIN:
			retv_c = boost::math::asin(arg_c);
			break;;
		case MR_FUN_ACOS:
			retv_c = boost::math::acos(arg_c);
			break;;
		case MR_FUN_ATAN:
			retv_c = boost::math::atan(arg_c);
			break;;
		case MR_FUN_SINH:
			retv_c = std::sinh(arg_c);
			break;;
		case MR_FUN_COSH:
			retv_c = std::cosh(arg_c);
			break;;
		case MR_FUN_TANH:
			retv_c = std::tanh(arg_c);
			break;;
		case MR_FUN_ASINH:
			retv_c = boost::math::asinh(arg_c);
			break;;
		case MR_FUN_ACOSH:
			retv_c = boost::math::acosh(arg_c);
			break;;
		case MR_FUN_ATANH:
			retv_c = boost::math::atanh(arg_c);
			break;;
		case MR_FUN_EXP:
			retv_c = std::exp(arg_c);
			break;;
		case MR_FUN_LOG:
			retv_c = std::log(arg_c);
			break;;
		case MR_FUN_LOG10:
			retv_c = std::log10(arg_c);
			break;;
		case MR_FUN_SQRT:
			retv_c = std::sqrt(arg_c);
			break;;
		case MR_FUN_ABS:
			retv_c = std::abs(arg_c);
			break;;
		case MR_FUN_RE:
			retv_c.real(val->real); retv_c.imag(0.0);
			break;;
		case MR_FUN_IM:
			retv_c.real(0.0); retv_c.imag(val->imag);
			break;;
		case MR_FUN_ARG:
			retv_c = std::arg(arg_c);
			break;;
		case MR_FUN_CONJ:
			retv_c = std::conj(arg_c);
			break;;
		case MR_FUN_DEG:
			retv_c.real(fmod(val->real * 180 / mr_pi(), 360));
			retv_c.imag(0.0);
			break;;
		case MR_FUN_RAD:
			retv_c.real(fmod(val->real * mr_pi() / 180, 2*mr_pi()));
			retv_c.imag(0.0);
			break;;
		case MR_FUN_NORM:
			retv_c = std::norm(arg_c);
			break;;
		case MR_FUN_POLAR:
			retv_c = std::polar(val->real, val->imag);
			break;;
	}

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

ComplexPtr mr_binary_function (MR_MATH_BINARY_FUNCTIONS which,
							   ComplexConstPtr arg1, ComplexConstPtr arg2) {
	ComplexPtr retv = newMrComplex();
	StdComplex arg1_c, arg2_c, retv_c;

	MRCOMPLEX_2_STDCOMPLEX(arg1_c, arg1);
	MRCOMPLEX_2_STDCOMPLEX(arg2_c, arg2);

	switch (which) {
		case MR_FUN2_ATAN2:
			retv_c.real(std::atan2(arg1->real, arg2->real));
			retv_c.imag(0.0);
			break;
	}

	STDCOMPLEX_2_MRCOMPLEX(retv, retv_c);
	return retv;
}

mrReal strToReal(const pANTLR3_STRING str) {
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	
	QString temp = QString::fromUtf8((const char*)utf8Str->chars, utf8Str->len);
	temp.replace(Conversion::internalDecimalPoint(), QChar('.'));

	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	return Conversion::strToReal(temp.toUtf8());
}

mrReal strHexToReal(const pANTLR3_STRING str) {
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	return Conversion::strHexToReal(bArray);
}

mrReal strOctToReal(const pANTLR3_STRING str) {
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	return Conversion::strOctToReal(bArray);
}

mrReal strBinToReal(const pANTLR3_STRING str) {
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	return Conversion::strBinToReal(bArray);
}