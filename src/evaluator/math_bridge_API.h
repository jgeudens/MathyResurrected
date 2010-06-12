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

/*! @file
Wrapper API for C++ complex math. ANTLR curently generates parsers
for C only so this API is used to comunicate ANTLR generated,
C parser/lexer/evaluator with C++ std::complex */

#ifndef MATHY_RESURRECTED_MATH_BRIDGE
#define MATHY_RESURRECTED_MATH_BRIDGE

#include "math_bridge_API_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! Returns pointer to new mrComplex_t. This pointer should never 
be deleted directly, it is handled automatically. */
mrComplex_ptr newMrComplex();
void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type);
void setAns(mrReal real, mrReal imag);
mrComplex_ptr getAns();

/*! Return value of PI */
mrReal mr_pi();
/*! Return value of e */
mrReal mr_e();

/*! To avoid passing around ANTLR3_STRING as much as possible
and to simplify implementation of SI unit conversion, this enum 
is used. 
@see si_calc */
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
mrReal si_ref(MR_MATH_SI_PREFIXES si_prefix);

typedef enum {
	MR_PLUS, MR_MINUS, MR_MULTI, MR_DIV, MR_MOD, MR_POW
} MR_MATH_BINARY_OPERATORS;
mrComplex_ptr mr_binary_operator (MR_MATH_BINARY_OPERATORS which, mrComplex_ptr lv, mrComplex_ptr rv);

typedef enum {
	MR_BITWISE_AND, MR_BITWISE_OR, 
	MR_BITWISE_NAND, MR_BITWISE_NOR, 
	MR_BITWISE_XOR, MR_BITWISE_XNOR,
	MR_BITWISE_SHL, MR_BITWISE_SHR
} MR_MATH_BINARY_BITWISE_OPERATORS;
mrComplex_ptr mr_binary_bitwise_operator (MR_MATH_BINARY_BITWISE_OPERATORS which, mrComplex_ptr lv, mrComplex_ptr rv);

typedef enum {
	MR_BITWISE_NOT
} MR_MATH_UNARY_OPERATORS;
mrComplex_ptr mr_unary_operator (MR_MATH_UNARY_OPERATORS which, mrComplex_ptr val);

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
mrComplex_ptr mr_unary_function (MR_MATH_UNARY_FUNCTIONS which, mrComplex_ptr val);

typedef enum {
	MR_FUN2_ATAN2
} MR_MATH_BINARY_FUNCTIONS;
mrComplex_ptr mr_binary_function (MR_MATH_BINARY_FUNCTIONS which, mrComplex_ptr arg1, mrComplex_ptr arg2);

mrReal parse_mrNumeric_t (pANTLR3_STRING str);
mrReal parse_hex_mrNumeric_t (pANTLR3_STRING str);
mrReal parse_oct_mrNumeric_t (pANTLR3_STRING str);
mrReal parse_bin_mrNumeric_t (pANTLR3_STRING str);

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_BRIDGE
