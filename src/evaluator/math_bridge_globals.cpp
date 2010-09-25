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

const int BridgeAPIGlobals::NUMERIC_PRECISION = 128;

BridgeAPIGlobals::BridgeAPIGlobals() {
	mpc_init2(itsAns, NUMERIC_PRECISION);
	mpc_set_ui_ui(itsAns, 0, 0, MPC_RNDNN);
}

BridgeAPIGlobals::~BridgeAPIGlobals() {
	mpc_clear(itsAns);
	clearComplexFactory();
}

BridgeAPIGlobals& BridgeAPIGlobals::getGlobals() {
	static BridgeAPIGlobals globalData;
	return globalData;
}

ComplexPtr BridgeAPIGlobals::newMrComplex() {
	ComplexPtr p = new Complex();
	mpc_init2(p, NUMERIC_PRECISION);
	mpc_set_ui_ui(p, 0, 0, MPC_RNDNN);
	getGlobals().itsComplexFactoryData.push_back(p);
	return p;
}

void BridgeAPIGlobals::clearComplexFactory() {
	ComplexVector::size_type i, iend;
	ComplexVector& fact = getGlobals().itsComplexFactoryData;
	i = 0; iend = fact.size();
	
	for (; i != iend; ++i) {
		mpc_clear(fact[i]);
		delete fact[i];
	}

	fact.clear();
}

void BridgeAPIGlobals::collectlexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err_type) {
	mr_LexerErrorPair p;
	p.char_index = char_index;
	p.err_type = err_type;
	getGlobals().itsLexerErrorsCollection.push_back(p);
}

void BridgeAPIGlobals::clearLexerErrors() {
	getGlobals().itsLexerErrorsCollection.clear();
}

const BridgeAPIGlobals::LexerErrorsCollection& BridgeAPIGlobals::getLexerErrors() {
	return getGlobals().itsLexerErrorsCollection;
}

void BridgeAPIGlobals::setAns(const Real& real, const Real& imag) {
	mpc_set_fr_fr(getGlobals().itsAns, real, imag, MPC_RNDNN);
}

ComplexConstPtr BridgeAPIGlobals::getAns() {
	return getGlobals().itsAns;
}

unsigned char BridgeAPIGlobals::bitWidth() {
	return getGlobals().itsBitWidth;
}

void BridgeAPIGlobals::setBitWidth(unsigned char nw) {
	getGlobals().itsBitWidth = nw;
}