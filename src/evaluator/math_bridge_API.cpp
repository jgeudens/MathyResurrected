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
#include <cassert>
#include "math_bridge_globals.h"
#include "Conversion.h"

using namespace std;
using namespace mathy_resurrected;

ComplexPtr newMrComplex() {
	return BridgeAPIGlobals::newMrComplex();
}

void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type) {
	BridgeAPIGlobals::collectlexerError(char_index, err_type);
}

void getAns(ComplexPtr dest) {
	assert(dest != 0);
	BridgeAPIGlobals::getAns(dest);
}

void mr_pi(ComplexPtr dest) {
	assert(dest != 0);
	mpfr_const_pi(mpc_realref(dest), MPFR_RNDN);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);
}

void mr_e(ComplexPtr dest) {
	assert(dest != 0);
	mpfr_set_ui(mpc_realref(dest), 1, MPFR_RNDN);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);
	mpfr_exp(mpc_realref(dest), mpc_realref(dest), MPFR_RNDN);
}

void si_ref(MR_MATH_SI_PREFIXES si_prefix, ComplexPtr dest) {
	assert(dest != 0);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);

	switch (si_prefix) {
		case MR_MATH_SI_PREFIX_YOTTA:
			mpfr_set_str(mpc_realref(dest), "1e24", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZETTA:
			mpfr_set_str(mpc_realref(dest), "1e21", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_EXA:
			mpfr_set_str(mpc_realref(dest), "1e18", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PETA:
			mpfr_set_str(mpc_realref(dest), "1e15", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_TERA:
			mpfr_set_str(mpc_realref(dest), "1e12", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_GIGA:
			mpfr_set_str(mpc_realref(dest), "1e9", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MEGA:
			mpfr_set_str(mpc_realref(dest), "1e6", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_KILO:
			mpfr_set_str(mpc_realref(dest), "1e3", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_HECTO:
			mpfr_set_str(mpc_realref(dest), "1e2", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_DECA:
			mpfr_set_str(mpc_realref(dest), "1e1", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_DECI:
			mpfr_set_str(mpc_realref(dest), "1e-1", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_CENTI:
			mpfr_set_str(mpc_realref(dest), "1e-2", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MILLI:
			mpfr_set_str(mpc_realref(dest), "1e-3", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MICRO:
			mpfr_set_str(mpc_realref(dest), "1e-6", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_NANO:
			mpfr_set_str(mpc_realref(dest), "1e-9", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PICO:
			mpfr_set_str(mpc_realref(dest), "1e-12", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_FEMTO:
			mpfr_set_str(mpc_realref(dest), "1e-15", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ATTO:
			mpfr_set_str(mpc_realref(dest), "1e-18", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZEPTO:
			mpfr_set_str(mpc_realref(dest), "1e-21", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_YOCTO:
			mpfr_set_str(mpc_realref(dest), "1e-24", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_KIBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 20, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_GIBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 30, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_TEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 40, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 50, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_EXBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 60, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 70, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_YOBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 80, MPFR_RNDN);
			break;
	}
}

ComplexPtr mr_binary_operator (MR_MATH_BINARY_OPERATORS which,
							   ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newMrComplex();
	switch (which) {
		case MR_PLUS:
			mpc_add(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MINUS:
			mpc_sub(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MULTI:
			mpc_mul(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_DIV:
			mpc_div(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MOD:
			mpfr_fmod(mpc_realref(retv), mpc_realref(lv), mpc_realref(rv), MPFR_RNDN);
			break;
		case MR_POW:
			mpc_pow(retv, lv, rv, MPC_RNDNN);
			break;
	}
	return retv;
}

ComplexPtr mr_unary_function (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val) {
	ComplexPtr retv = newMrComplex();

	switch (which) {
		case MR_FUN_SIN:
			mpc_sin(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_COS:
			mpc_cos(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_TAN:
			mpc_tan(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ASIN:
			mpc_asin(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ACOS:
			mpc_acos(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ATAN:
			mpc_atan(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_SINH:
			mpc_sinh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_COSH:
			mpc_cosh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_TANH:
			mpc_tanh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ASINH:
			mpc_asinh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ACOSH:
			mpc_acosh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ATANH:
			mpc_atanh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_EXP:
			mpc_exp(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_LOG:
			mpc_log(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_LOG10:
			Complex logOf10;
			mpc_init2(logOf10, BridgeAPIGlobals::NUMERIC_PRECISION);
			mpc_set_ui(logOf10, 10, MPC_RNDNN);
			mpc_log(logOf10, logOf10, MPC_RNDNN);

			mpc_log(retv, val, MPC_RNDNN);
			mpc_div(retv, retv, logOf10, MPC_RNDNN);

			mpc_clear(logOf10);
			break;
		case MR_FUN_SQRT:
			mpc_sqrt(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ABS:
			mpc_abs(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_RE:
			mpc_set_fr(retv, mpc_realref(val), MPC_RNDNN);
			break;
		case MR_FUN_IM:
			mpfr_set(mpc_imagref(retv), mpc_imagref(val), MPFR_RNDN);
			break;
		case MR_FUN_ARG:
			mpc_arg(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_CONJ:
			mpc_conj(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_DEG:
			mpfr_set(mpc_realref(retv), mpc_realref(val), MPFR_RNDN);
			mpfr_const_pi(mpc_imagref(retv), MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_mul_ui(mpc_realref(retv), mpc_realref(retv), 180, MPFR_RNDN);
			mpfr_div(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 360, MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_fmod(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 0, MPFR_RNDN);
			break;
		case MR_FUN_RAD:
			mpfr_set(mpc_realref(retv), mpc_realref(val), MPFR_RNDN);
			mpfr_const_pi(mpc_imagref(retv), MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_mul(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_div_ui(mpc_realref(retv), mpc_realref(retv), 180, MPFR_RNDN);
			mpfr_mul_ui(mpc_imagref(retv), mpc_imagref(retv), 2, MPFR_RNDN);
			mpfr_fmod(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 0, MPFR_RNDN);
			break;
		case MR_FUN_NORM:
			mpc_norm(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_POLAR:
			RealPtr fn;
			fn = BridgeAPIGlobals::newMrReal();
			mpfr_cos(fn, mpc_imagref(val), MPFR_RNDN);
			mpfr_mul(mpc_realref(retv), mpc_realref(val), fn, MPFR_RNDN);
			mpfr_sin(fn, mpc_imagref(val), MPFR_RNDN);
			mpfr_mul(mpc_imagref(retv), mpc_realref(val), fn, MPFR_RNDN);
			break;
	}
	return retv;
}

ComplexPtr mr_binary_function (MR_MATH_BINARY_FUNCTIONS which,
							   ComplexConstPtr arg1, ComplexConstPtr arg2) {
	ComplexPtr retv = newMrComplex();
	switch (which) {
		case MR_FUN2_ATAN2:
			mpfr_atan2(mpc_realref(retv), mpc_realref(arg1), mpc_realref(arg2), MPFR_RNDN);
			break;
	}
	return retv;
}

void strToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QString temp = QString::fromUtf8((const char*)utf8Str->chars, utf8Str->len);
	temp.replace(Conversion::internalDecimalPoint(), QChar('.'));
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strToReal(temp.toUtf8(), dest);
}

void strHexToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strHexToReal(bArray, dest);
}

void strOctToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strOctToReal(bArray, dest);
}

void strBinToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strBinToReal(bArray, dest);
}

ComplexPtr mr_unary_operator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val) {
	ComplexPtr retv = newMrComplex();

	if (which == MR_BITWISE_NOT) {
		switch (BridgeAPIGlobals::bitWidth()) {
			case 64:
				quint64 tmpI64;
				tmpI64 = Conversion::convert_u64b(mpc_realref(val));
				tmpI64 = ~tmpI64;
				Conversion::mpfr_set_quint64(mpc_realref(retv), tmpI64);
				break;
			case 32:
				quint32 tmpI32;
				tmpI32 = Conversion::convert_u32b(mpc_realref(val));
				tmpI32 = ~tmpI32;
				mpfr_set_ui(mpc_realref(retv), tmpI32, MPFR_RNDN);
				break;
			case 16:
				quint16 tmpI16;
				tmpI16 = Conversion::convert_u16b(mpc_realref(val));
				tmpI16 = ~tmpI16;
				mpfr_set_ui(mpc_realref(retv), tmpI16, MPFR_RNDN);
				break;
			case 8:
				quint8 tmpI8;
				tmpI8 = Conversion::convert_u8b(mpc_realref(val));
				tmpI8 = ~tmpI8;
				mpfr_set_ui(mpc_realref(retv), tmpI8, MPFR_RNDN);
				break;
		}
	} else if (which == MR_UNARY_MINUS) {
		mpc_mul_si(retv, val, -1, MPC_RNDNN);
	}
	return retv;
}

ComplexPtr 
mr_binary_bitwise_operator (MR_MATH_BINARY_BITWISE_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newMrComplex();

	quint64 lv64, rv64;
	quint32 lv32, rv32;
	quint16 lv16, rv16;
	quint8 lv8, rv8;

	switch (BridgeAPIGlobals::bitWidth()) {
		case 64:
			lv64 = Conversion::convert_u64b(mpc_realref(lv));
			rv64 = Conversion::convert_u64b(mpc_realref(rv));
			break;
		case 32:
			lv32 = Conversion::convert_u32b(mpc_realref(lv));
			rv32 = Conversion::convert_u32b(mpc_realref(rv));
			break;
		case 16:
			lv16 = Conversion::convert_u16b(mpc_realref(lv));
			rv16 = Conversion::convert_u16b(mpc_realref(rv));
			break;
		case 8:
			lv8 = Conversion::convert_u8b(mpc_realref(lv));
			rv8 = Conversion::convert_u8b(mpc_realref(rv));
			break;
	}

	switch (which) {
		// bitwise AND
		case  MR_BITWISE_AND:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 & rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 & rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 & rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 & rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise OR
		case  MR_BITWISE_OR:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 | rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 | rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 | rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 | rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise NAND
		case  MR_BITWISE_NAND:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 & rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 & rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 & rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 & rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise NOR
		case  MR_BITWISE_NOR:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 | rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 | rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 | rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 | rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise XOR
		case  MR_BITWISE_XOR:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 ^ rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 ^ rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 ^ rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 ^ rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise XNOR
		case  MR_BITWISE_XNOR:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 ^ rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 ^ rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 ^ rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 ^ rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise shift left
		case  MR_BITWISE_SHL:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 << rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 << rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 << rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 << rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise shift right
		case  MR_BITWISE_SHR:
			switch (BridgeAPIGlobals::bitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 >> rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 >> rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 >> rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 >> rv8, MPFR_RNDN);
					break;
			}
			break;
	}

	return retv;
}
