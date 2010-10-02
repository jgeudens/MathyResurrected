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

#include "math_bridge_API.h"
#include <cassert>
#include "Conversion.h"
#include "Settings.h"
#include "MathEvaluator.h"

using namespace std;
using namespace mathy_resurrected;

/** Evaluator object that currently uses bridge 
@see setEvaluator */
MathEvaluator* currentEvaluator;

/** Sets @a evaluatorObject as current MathEvaluator instance for bridge API.
This should be called by MathEvaluator every time it tries to do evaluation 
of expression using ANTLR generated lexer/parser. @a evaluatorObject
is never deleted by bridge API methods, it's only purpose it to enable 
communication between bridge API and evaluator instance that is currently 
using bridge API through ANTLR generated code. */
void setEvaluator(void* evaluatorObject) {
	currentEvaluator = (MathEvaluator*)evaluatorObject;
}

/*! Returns pointer to new Complex. This pointer should never 
be deleted directly, it is handled automatically. */
ComplexPtr newMrComplex() {
	return currentEvaluator->newComplex();
}

void collectlexerError(ANTLR3_UINT32 char_index, MR_LEXER_ERROR_TYPES err_type) {
	currentEvaluator->collectlexerError(char_index, err_type);
}

void getAns(ComplexPtr dest) {
	assert(dest != 0);
	currentEvaluator->ans(dest);
}

void mr_pi(ComplexPtr dest) {
	MathEvaluator::pi(dest);
}

void mr_e(ComplexPtr dest) {
	MathEvaluator::e(dest);
}

void si_ref(MR_MATH_SI_PREFIXES si_prefix, ComplexPtr dest){
	currentEvaluator->SIUnit(si_prefix, dest);
}

ComplexPtr mr_binary_operator (MR_MATH_BINARY_OPERATORS which,
							   ComplexConstPtr lv, ComplexConstPtr rv) {
	return currentEvaluator->binaryOperator(which, lv, rv);
}

ComplexPtr mr_unary_function (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val) {
	return currentEvaluator->unaryFunction(which, val);
}

ComplexPtr mr_binary_function (MR_MATH_BINARY_FUNCTIONS which,
							   ComplexConstPtr arg1, ComplexConstPtr arg2) {
	return currentEvaluator->binaryFunction(which, arg1, arg2);
}

ComplexPtr mr_unary_operator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val) {
	return currentEvaluator->unaryOperator(which, val);
}

ComplexPtr 
mr_binary_bitwise_operator (MR_MATH_BINARY_BITWISE_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv) {
	return currentEvaluator->bitwiseOperator(which, lv, rv);
}

void strToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QString temp = QString::fromUtf8((const char*)utf8Str->chars, utf8Str->len);
	temp.replace(Conversion::internalDecimalPoint(), QChar('.'));
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strToReal(temp.toUtf8(), dest);
}

void strHexToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strHexToReal(bArray, dest);
}

void strOctToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strOctToReal(bArray, dest);
}

void strBinToReal(const pANTLR3_STRING str, RealPtr dest) {
	assert(dest != 0);
	pANTLR3_STRING utf8Str = str->toUTF8(str);
	QByteArray bArray ((const char*)utf8Str->chars, utf8Str->len);
	utf8Str->factory->destroy(utf8Str->factory, utf8Str);
	Conversion::strBinToReal(bArray, dest);
}
