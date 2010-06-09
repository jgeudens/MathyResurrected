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

#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "math_bridge_globals.h"

using namespace std; 
using namespace boost;

/*! All lexer errors are collected here during lexing phase. After that and before parser is 
invoked, this can be used to generate error message.
@todo All this data is currently ignored by MathEvaluator and no detailed errors are produced 
(it is only checked if there are errors or not and itsIsValid is set properly. */
vector <LexerErrorPair> lexerErrorsCollection;

/*! Data storage for factory produced objects. */
vector< boost::shared_ptr< mrComplex_t > > complexFactoryData;

mrComplex_ptr newMrComplex() {
	mrComplex_ptr p = new mrComplex_t;
	p->real = 0; p->imag = 0;
	boost::shared_ptr< mrComplex_t > sp(p);
	complexFactoryData.push_back(sp);
	return p;
}

/*! Collects lexer errors during lexing phase so they can be used
to check for things like unmatched parentheses, illegal input etc... */
void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_code) {
	LexerErrorPair p;
	p.char_index = char_index;
	p.err_type = err_code;
	lexerErrorsCollection.push_back(p);
}

unsigned int countLexerErrors() {
	return static_cast<unsigned int>(lexerErrorsCollection.size());
}

LexerErrorPair getLexerError(unsigned int which) {
	return lexerErrorsCollection.at(which);
}

void clear_factories() {
	lexerErrorsCollection.clear();
	complexFactoryData.clear();
}

mrComplex_t ans;

void setAns(mrNumeric_t real, mrNumeric_t imag) {
	ans.real = real;
	ans.imag = imag;
}

mrComplex_ptr mr_ans() {
	mrComplex_ptr retv = newMrComplex();
	retv->real = ans.real;
	retv->imag = ans.imag;
	return retv;
}