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

#include <antlr3.h>
#include "math_bridge_API_types.h"

#ifdef __cplusplus
extern "C" {
#endif

ComplexPtr newMrComplex();
void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type);
void getAns(ComplexPtr dest);

void mr_pi(ComplexPtr dest);
void mr_e(ComplexPtr dest);
void si_ref(MR_MATH_SI_PREFIXES si_prefix, ComplexPtr dest);

ComplexPtr mr_binary_operator (MR_MATH_BINARY_OPERATORS which, 
							   ComplexConstPtr lv, ComplexConstPtr rv);
ComplexPtr mr_binary_bitwise_operator (MR_MATH_BINARY_BITWISE_OPERATORS which, 
									   ComplexConstPtr lv, ComplexConstPtr rv);
ComplexPtr mr_unary_operator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val);

ComplexPtr mr_unary_function (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val);
ComplexPtr mr_binary_function (MR_MATH_BINARY_FUNCTIONS which,  
							   ComplexConstPtr arg1, ComplexConstPtr arg2);

void strToReal(const pANTLR3_STRING str, RealPtr dest);
void strHexToReal(const pANTLR3_STRING str, RealPtr dest);
void strOctToReal(const pANTLR3_STRING str, RealPtr dest);
void strBinToReal(const pANTLR3_STRING str, RealPtr dest);

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_BRIDGE
