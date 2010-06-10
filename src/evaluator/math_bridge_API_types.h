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

#ifndef MATHY_RESURRECTED_MATH_BRIDGE_TYPES
#define MATHY_RESURRECTED_MATH_BRIDGE_TYPES

#ifdef __cplusplus
extern "C" {
#endif

/*! Numeric type used for all math calculations */
typedef double mrReal;

/*! This is a replacement for std::complex<T>. ANTLR doesn't have C++ API
so actions inside grammar use this type to pass around complex nnumbers. */
typedef struct {
	mrReal real, imag;
} mrComplex_t;

/*! Pointer to mrComplex_t */ 
typedef mrComplex_t* mrComplex_ptr;

typedef enum MR_LEXER_ERROR_TYPES_ {
	LEX_ERR_MALFORMED_MANTISSA, LEX_ERR_MALFORMED_EXPONENT,
	LEX_ERR_BAD_INPUT
} MR_LEXER_ERROR_TYPES;

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_BRIDGE_TYPES
