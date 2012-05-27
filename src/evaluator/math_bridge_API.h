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

/*! Return value of PI */
mrNumeric_t mr_pi();
/*! Return value of e */
mrNumeric_t mr_e();
/*! Return value of previous calculation */
mrComplex_ptr mr_ans();

/*! Returns pointer to new mrComplex_t. This pointer should never 
be deleted directly, it is handled automatically. */
mrComplex_ptr newMrComplex(); 

mrComplex_ptr mr_add (mrComplex_ptr lv, mrComplex_ptr rv);
mrComplex_ptr mr_substract (mrComplex_ptr lv, mrComplex_ptr rv);
mrComplex_ptr mr_multiply (mrComplex_ptr lv, mrComplex_ptr rv);
mrComplex_ptr mr_divide (mrComplex_ptr lv, mrComplex_ptr rv);
mrComplex_ptr mr_modulo (mrComplex_ptr lv, mrComplex_ptr rv);

mrNumeric_t si_calc(mrNumeric_t multipl, MR_MATH_SI_PREFIXES si_prefix);

mrNumeric_t parse_mrNumeric_t (pANTLR3_STRING str);
mrNumeric_t parse_hex_mrNumeric_t (pANTLR3_STRING str);
mrNumeric_t parse_oct_mrNumeric_t (pANTLR3_STRING str);
mrNumeric_t parse_bin_mrNumeric_t (pANTLR3_STRING str);

mrComplex_ptr mr_sin(mrComplex_ptr x);
mrComplex_ptr mr_cos(mrComplex_ptr x);
mrComplex_ptr mr_tan(mrComplex_ptr x);
mrComplex_ptr mr_asin(mrComplex_ptr x);
mrComplex_ptr mr_acos(mrComplex_ptr x);
mrComplex_ptr mr_atan(mrComplex_ptr x);
mrComplex_ptr mr_sinh(mrComplex_ptr x);
mrComplex_ptr mr_cosh(mrComplex_ptr x);
mrComplex_ptr mr_tanh(mrComplex_ptr x);
mrComplex_ptr mr_asinh(mrComplex_ptr x);
mrComplex_ptr mr_acosh(mrComplex_ptr x);
mrComplex_ptr mr_atanh(mrComplex_ptr x);
mrComplex_ptr mr_exp(mrComplex_ptr x);
mrComplex_ptr mr_log(mrComplex_ptr x);
mrComplex_ptr mr_log10(mrComplex_ptr x);
mrComplex_ptr mr_sqrt(mrComplex_ptr x);
mrComplex_ptr mr_abs(mrComplex_ptr x);
mrComplex_ptr mr_re(mrComplex_ptr x);
mrComplex_ptr mr_im(mrComplex_ptr x);
mrComplex_ptr mr_arg(mrComplex_ptr x);
mrComplex_ptr mr_conj(mrComplex_ptr x);
mrComplex_ptr mr_deg(mrComplex_ptr x);
mrComplex_ptr mr_rad(mrComplex_ptr x);
mrComplex_ptr mr_norm(mrComplex_ptr x);
mrComplex_ptr mr_polar(mrComplex_ptr x);

mrComplex_ptr mr_atan2 (mrComplex_ptr x, mrComplex_ptr y); 
mrComplex_ptr mr_pow (mrComplex_ptr x, mrComplex_ptr y); 

void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type); 

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_BRIDGE
