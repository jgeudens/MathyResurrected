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
* along with MathyResurrected. If not, see <http://www.gnu.org/licenses/>. */

#ifndef MATHY_RESURRECTED_MATH_TYPES
#define MATHY_RESURRECTED_MATH_TYPES

#include <gmp.h>
#include <mpfr.h>
#include <mpc.h>
#include <antlr3.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Multiple precision, floating point type */
typedef mpfr_t Real;
typedef mpfr_ptr RealPtr;
typedef mpfr_srcptr RealConstPtr;

/*! Multiple precision, complex number type */
typedef mpc_t Complex;
typedef mpc_ptr ComplexPtr;
typedef mpc_srcptr ComplexConstPtr;

/** Recognized lexer errors */
typedef enum {
	LEX_ERR_MALFORMED_MANTISSA, LEX_ERR_MALFORMED_EXPONENT,
	LEX_ERR_BAD_INPUT
} MR_LEXER_ERROR_TYPES;

/** Arithmetic binary operators */
typedef enum {
	MR_PLUS, MR_MINUS, MR_MULTI, MR_DIV, MR_MOD, MR_POW
} MR_MATH_BINARY_OPERATORS;

/** SI unit prefixes */
typedef enum {
	MR_MATH_SI_PREFIX_YOTTA, MR_MATH_SI_PREFIX_ZETTA, 
	MR_MATH_SI_PREFIX_EXA, MR_MATH_SI_PREFIX_PETA, 
	MR_MATH_SI_PREFIX_TERA, MR_MATH_SI_PREFIX_GIGA, 
	MR_MATH_SI_PREFIX_MEGA, MR_MATH_SI_PREFIX_KILO, 
	MR_MATH_SI_PREFIX_HECTO, MR_MATH_SI_PREFIX_DECA, 
	MR_MATH_SI_PREFIX_DECI, MR_MATH_SI_PREFIX_CENTI, 
	MR_MATH_SI_PREFIX_MILLI, MR_MATH_SI_PREFIX_MICRO, 
	MR_MATH_SI_PREFIX_NANO, MR_MATH_SI_PREFIX_PICO, 
	MR_MATH_SI_PREFIX_FEMTO, MR_MATH_SI_PREFIX_ATTO, 
	MR_MATH_SI_PREFIX_ZEPTO, MR_MATH_SI_PREFIX_YOCTO, 
	MR_MATH_SI_PREFIX_KIBI, MR_MATH_SI_PREFIX_MEBI, 
	MR_MATH_SI_PREFIX_GIBI, MR_MATH_SI_PREFIX_TEBI, 
	MR_MATH_SI_PREFIX_PEBI, MR_MATH_SI_PREFIX_EXBI, 
	MR_MATH_SI_PREFIX_ZEBI, MR_MATH_SI_PREFIX_YOBI
} MR_MATH_SI_PREFIXES;

/** Logic binary operators */
typedef enum {
	MR_BITWISE_AND, MR_BITWISE_OR, 
	MR_BITWISE_NAND, MR_BITWISE_NOR, 
	MR_BITWISE_XOR, MR_BITWISE_XNOR,
	MR_BITWISE_SHL, MR_BITWISE_SHR
} MR_MATH_BINARY_BITWISE_OPERATORS;

/** Unary operators */
typedef enum {
	MR_BITWISE_NOT, MR_UNARY_MINUS
} MR_MATH_UNARY_OPERATORS;

/** Functions with single argument. */
typedef enum {
	MR_FUN_SIN, MR_FUN_COS, MR_FUN_TAN, 
	MR_FUN_ASIN, MR_FUN_ACOS, MR_FUN_ATAN, 
	MR_FUN_SINH, MR_FUN_COSH, MR_FUN_TANH,
	MR_FUN_ASINH, MR_FUN_ACOSH, MR_FUN_ATANH,
	MR_FUN_EXP, MR_FUN_LOG, MR_FUN_LOG10,
	MR_FUN_SQRT, MR_FUN_ABS, 
	MR_FUN_RE, MR_FUN_IM, MR_FUN_ARG, MR_FUN_CONJ,
	MR_FUN_DEG, MR_FUN_RAD, 
	MR_FUN_NORM, MR_FUN_POLAR
} MR_MATH_UNARY_FUNCTIONS;

/** Functions with two arguments. */
typedef enum {
	MR_FUN2_ATAN2
} MR_MATH_BINARY_FUNCTIONS;

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_TYPES