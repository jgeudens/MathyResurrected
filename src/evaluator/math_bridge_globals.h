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

/*! @file */

#ifndef MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS
#define MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS

#include <vector>
#include "math_bridge_API_types.h"

/** Structure that holds global variables needed by math bridge API. */
class BridgeAPIGlobals {
public:
	~BridgeAPIGlobals();
	static ComplexPtr newMrComplex();
	static void clearComplexFactory();
	static RealPtr newMrReal();
	static void clearRealFactory();
	
	typedef struct {
		unsigned int char_index;
		MR_LEXER_ERROR_TYPES err_type;
	} mr_LexerErrorPair;

	typedef std::vector <mr_LexerErrorPair> LexerErrorsCollection;

	static void collectlexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err_type);
	static void clearLexerErrors();
	static const LexerErrorsCollection& getLexerErrors();

	static void setAns(const Real& real, const Real& imag);
	static void getAns(ComplexPtr dest);

	static unsigned char bitWidth();
	static void setBitWidth(unsigned char nw);

	static const int NUMERIC_PRECISION;

private:
	BridgeAPIGlobals();
	static BridgeAPIGlobals& getGlobals();

	typedef std::vector<ComplexPtr> ComplexVector;
	typedef std::vector<RealPtr> RealVector;
	/*! Data storage for factory produced objects. */
	ComplexVector itsComplexFactoryData;
	RealVector itsRealFactoryData;

	/*! All lexer errors are collected here during lexing phase. After 
	that and before parser is invoked, this can be used to generate error 
	message. */
	LexerErrorsCollection itsLexerErrorsCollection;

	Complex itsAns;
	unsigned char itsBitWidth;
};

#endif // MATHY_RESURRECTED_MATH_BRIDGE_GLOBALS
