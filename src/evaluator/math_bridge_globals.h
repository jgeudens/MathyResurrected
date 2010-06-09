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

#ifndef MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS
#define MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS

#include "math_bridge_API_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! Returns pointer to new mrComplex_t. This pointer should never 
be deleted directly, it is handled automatically. */
mrComplex_ptr newMrComplex();

typedef struct {
	ANTLR3_UINT32 char_index;
	MR_LEXER_ERROR_TYPES err_type;
} LexerErrorPair;

void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type);
unsigned int countLexerErrors();
LexerErrorPair getLexerError(unsigned int which);

void clear_factories();
void setAns(mrNumeric_t real, mrNumeric_t imag);
mrComplex_ptr getAns();

/*! Return value of previous calculation */
mrComplex_ptr mr_ans();

#ifdef __cplusplus
}
#endif

#endif // MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS
