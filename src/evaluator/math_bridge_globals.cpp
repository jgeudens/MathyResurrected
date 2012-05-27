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

#include "math_bridge_globals.h"

BridgeAPIGlobals::BridgeAPIGlobals() {
	ans.real = ans.imag = 0;
}

BridgeAPIGlobals& BridgeAPIGlobals::getGlobals() {
	static BridgeAPIGlobals globalData;
	return globalData;
}

ComplexPtr BridgeAPIGlobals::newMrComplex() {
	ComplexPtr p = new Complex;
	p->real = 0; p->imag = 0;
	boost::shared_ptr< Complex > sp(p);
	getGlobals().complexFactoryData.push_back(sp);
	return p;
}

void BridgeAPIGlobals::clearComplexFactory() {
	getGlobals().complexFactoryData.clear();
}

void BridgeAPIGlobals::collectlexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err_type) {
	mr_LexerErrorPair p;
	p.char_index = char_index;
	p.err_type = err_type;
	getGlobals().lexerErrorsCollection.push_back(p);
}

void BridgeAPIGlobals::clearLexerErrors() {
	getGlobals().lexerErrorsCollection.clear();
}

const BridgeAPIGlobals::LexerErrorsCollection& BridgeAPIGlobals::getLexerErrors() {
	return getGlobals().lexerErrorsCollection;
}

void BridgeAPIGlobals::setAns(mrReal real, mrReal imag) {
	getGlobals().ans.real = real;
	getGlobals().ans.imag = imag;
}

ComplexConstPtr BridgeAPIGlobals::getAns() {
	return &(getGlobals().ans);
}

unsigned char BridgeAPIGlobals::bitWidth() {
	return getGlobals().bit_width;
}

void BridgeAPIGlobals::setBitWidth(unsigned char nw) {
	getGlobals().bit_width = nw;
}