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

#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "math_bridge_API_types.h"

/** Structure that holds global variables needed by math bridge API.
Bridge API is initialized with instance of this struct and then uses
it's members to store data. This had to be done because ANTLR generates
C-api which can't be used directly with C++ */
struct BridgeAPIGlobals {
	BridgeAPIGlobals() {
		ans.real = ans.imag = 0;
	}

	typedef struct {
		unsigned int char_index;
		MR_LEXER_ERROR_TYPES err_type;
	} mr_LexerErrorPair;

	/*! All lexer errors are collected here during lexing phase. After 
	that and before parser is invoked, this can be used to generate error 
	message. */
	std::vector <mr_LexerErrorPair> lexerErrorsCollection;

	/*! Data storage for factory produced objects. */
	std::vector< boost::shared_ptr< mrComplex_t > > complexFactoryData;

	mrComplex_t ans;
};

void init_bridge_API (BridgeAPIGlobals* globs);

#endif // MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS
