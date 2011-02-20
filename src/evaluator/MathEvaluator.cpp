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

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <QByteArray>

#include <cassert>
#include "MathEvaluator.h"
#include "Settings.h"
#include "Exceptions.h"
#include "Conversion.h"

#include "ComplexLexer.h"
#include "ComplexParser.h"
#include "ComplexEval.h"

using namespace std;
using namespace mathy_resurrected;

namespace mathy_resurrected {

/** Evaluator object that currently uses ANTLR parser/lexer. 
ANTLR parser lexer uses evaluator instance as factory object and for
retrieving ans() data. Thus, any evaluator operation that needs to 
use ANTLR generated lexer/parser must ensure that it is registered
through this pointer before calling ANTLR functions. */
MathEvaluator* currentEvaluator;

MathEvaluator* getEvaluatorInstance() {
	return currentEvaluator;
}

/** Number of bits uses for all number representations. */
const int MathEvaluator::NUMERIC_PRECISION = 164;

#ifdef _DEBUG
void MathEvaluator::printLexerErrors() const {
	unsigned int i = 0;
	unsigned int iend = itsLexerErrorsCollection.size();

	for (; i != iend; ++i) {
		cout << "Char at: " << itsLexerErrorsCollection[i].char_index;
		cout << " Error: ";
		switch (itsLexerErrorsCollection[i].err_type) {
			case LEX_ERR_MALFORMED_MANTISSA:
				cout << "LEX_ERR_MALFORMED_MANTISSA";
				break;
			case LEX_ERR_MALFORMED_EXPONENT:
				cout << "LEX_ERR_MALFORMED_EXPONENT";
				break;
			case LEX_ERR_BAD_INPUT:
				cout << "LEX_ERR_BAD_INPUT";
				break;
		}
	}
	cout << "\n";
}
#endif // _DEBUG

/*! Convenience class that is used to setup basic components of 
ANTLR lexer and parser for use by evaluate() and validate() 
methods. */
class MathEvaluator::LexerParser {
public:
	LexerParser(const QString& expression);
	~LexerParser();
	
	pANTLR3_INPUT_STREAM inputStream;
	pComplexLexer lexer;
	pANTLR3_COMMON_TOKEN_STREAM	tokenStream;
	pComplexParser parser;
	ComplexParser_prog_return expressionAST;
	pANTLR3_COMMON_TREE_NODE_STREAM	nodes;
	pComplexEval treeParser;

	bool malloc_error;
};

/*! @note Assumes that @a expression has been preprocessed.
@see MathEvaluator::itsExprString. */
MathEvaluator::LexerParser::LexerParser(const QString& expression) {
	malloc_error = false;

	// Possibly problematic cast!
	// ANTLR expects UCS2 encoded string, and we provide UTF16 one.
	// Should make no difference for strings that contain only math
	// expressions.
	inputStream = antlr3NewUCS2StringInPlaceStream(
			(pANTLR3_UINT16)(expression.utf16()), 
			expression.length(), NULL);
	if (inputStream == NULL) {
		malloc_error = true;
	}

	if (!malloc_error) {
		lexer	= ComplexLexerNew(inputStream);
		if (inputStream == NULL) {
			malloc_error = true;
		}
	}

	if (!malloc_error) {
		tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
		if (inputStream == NULL) {
			malloc_error = true;
		}
	}

	if (!malloc_error) {
		parser = ComplexParserNew(tokenStream);
		if (inputStream == NULL) {
			malloc_error = true;
		}
	}

	nodes = NULL;
	treeParser = NULL;
}

MathEvaluator::LexerParser::~LexerParser() {
	if (nodes != NULL) { nodes->free (nodes); nodes = NULL; }
	if (treeParser != NULL) { treeParser->free (treeParser); treeParser = NULL; }
	if (parser != NULL) { parser->free (parser); parser = NULL; }
	if (tokenStream != NULL) { tokenStream->free (tokenStream); tokenStream = NULL; }
	if (lexer != NULL) { lexer->free (lexer); lexer = NULL; }
	if (inputStream != NULL) { inputStream->close (inputStream); inputStream = NULL; }
}


MathEvaluator::MathEvaluator(const Settings* app_settings, QObject* parent) : 
	QObject(parent),
 	itsIsValid(false), itsIsValidated(false), itsIsEvaluated(false)
{
	currentEvaluator = this;
	
	if (app_settings == 0) {
		throw invalid_argument("Null pointer to evaluator settings!");
	}
	itsSettings = app_settings;

	mpc_init2(itsValue, NUMERIC_PRECISION);
	mpc_set_ui_ui(itsValue, 0, 0, MPC_RNDNN);
	mpc_init2(itsAns, NUMERIC_PRECISION);
	mpc_set_ui_ui(itsAns, 0, 0, MPC_RNDNN);
}

MathEvaluator::~MathEvaluator() {
	mpc_clear(itsValue);
	mpc_clear(itsAns);
	clearComplexFactory();
	clearRealFactory();
	mpfr_free_cache();
}

/*! Sets expression to be evaluated. */
void MathEvaluator::setExpression(const QString& expression) {
	itsIsValidated = false;
	itsIsValid = false;
	itsIsEvaluated = false;
	
	itsExprString = expression;
	// Preprocessing expression...
	itsExprString.replace(itsSettings->decimalPointAsChar(), Conversion::internalDecimalPoint());
	itsExprString.replace(itsSettings->functionArgSeparatorAsChar(), Conversion::internalArgSeparator());
}

/*! Validates expression. Doesn't evaluate it. */
bool MathEvaluator::validate() {
	
	if (!itsIsValidated) {
		LexerParser lpr (itsExprString);

		if (!lpr.malloc_error) {
			lpr.expressionAST = lpr.parser->prog(lpr.parser);
#ifdef _DEBUG
			printLexerErrors();
#endif // _DEBUG
			// Currently just counting errors. In the future we could 
			// use collection of lexer errors provided by bridge API
			// to analyze things before invoking parser.
			if (lpr.parser->pParser->rec->state->errorCount > 0) {
				itsIsValid = false;
				itsErrStr = "Malformed expression";
			} else {
				itsIsValid = true;
			}		
		}
		itsIsValidated = true;
	}

	clearComplexFactory();
	itsLexerErrorsCollection.clear();
	return itsIsValid;
}

/*! Validates expression if it hasn't been validated and 
evaluates it. Returns true if expression is valid. Results
can be read using Re() and Im() methods. */
bool MathEvaluator::evaluate() {
	itsLexerErrorsCollection.clear();
	// Connect to bridge API
	currentEvaluator = this;
	if (!itsIsEvaluated) {
		if (validate()) {

			itsErrStr.clear();

			LexerParser lpr (itsExprString);

			if (!lpr.malloc_error) {
				// No need to check if this fails because it was done during 
				// validate() phase, we are now just connecting things together
				// knowing for sure that they will work.
				lpr.expressionAST = lpr.parser->prog(lpr.parser);
			}
			if (!lpr.malloc_error) {
				lpr.nodes	= antlr3CommonTreeNodeStreamNewTree(lpr.expressionAST.tree, ANTLR3_SIZE_HINT); // sIZE HINT WILL SOON BE DEPRECATED!!
				if (lpr.nodes == NULL) {
					lpr.malloc_error = true;
				}
			}
			if (!lpr.malloc_error) {
				lpr.treeParser	= ComplexEvalNew(lpr.nodes);
				if (lpr.treeParser == NULL) {
					lpr.malloc_error = true;
				}
			}

			if (!lpr.malloc_error) {
				ComplexPtr retv_val;

				try {
					retv_val = lpr.treeParser->prog(lpr.treeParser);
					mpc_set(itsValue, retv_val, MPC_RNDNN);
				}
				catch (NumericConversionError& e) {
					itsIsValid = false;
					itsErrStr = e.what();
				}
			}
		}
		itsIsEvaluated = true;
	}

	clearComplexFactory();
	return itsIsValid;
}

/** Stores current state of calculation for future use by "ans" 
variable in expression. */
void MathEvaluator::storeAns() {
	mpfr_set(mpc_realref(itsAns), mpc_realref(itsValue), MPFR_RNDN);
	mpfr_set(mpc_imagref(itsAns), mpc_imagref(itsValue), MPFR_RNDN);
}

const QString MathEvaluator::toString() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::DECIMAL, *itsSettings, itsValue);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

const QString MathEvaluator::toStringBin() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::BINARY, *itsSettings, itsValue);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

const QString MathEvaluator::toStringHex() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::HEXADECIMAL, *itsSettings, itsValue);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

const QString MathEvaluator::toStringOct() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::OCTAL, *itsSettings, itsValue);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

/*! Returns result of evaluation. If expression hasn't been evaluated, 
or is invalid, return value is unspecified. */
const Real& MathEvaluator::Re() const { return mpc_realref(itsValue); }
/*! Returns result of evaluation. If expression hasn't been evaluated, 
or is invalid, return value is unspecified. */
const Real& MathEvaluator::Im() const { return mpc_imagref(itsValue); }

void MathEvaluator::pi(ComplexPtr dest) {
	assert(dest != 0);
	mpfr_const_pi(mpc_realref(dest), MPFR_RNDN);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);
}

void MathEvaluator::e(ComplexPtr dest) {
	assert(dest != 0);
	mpfr_set_ui(mpc_realref(dest), 1, MPFR_RNDN);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);
	mpfr_exp(mpc_realref(dest), mpc_realref(dest), MPFR_RNDN);
}

const Settings& MathEvaluator::settings() const { return *itsSettings; }

void MathEvaluator::ans(ComplexPtr dest) {
	assert(dest != 0);
	mpfr_set(mpc_realref(itsAns), mpc_realref(dest), MPFR_RNDN);
	mpfr_set(mpc_imagref(itsAns), mpc_imagref(dest), MPFR_RNDN);
}

ComplexPtr MathEvaluator::newComplex() {
	ComplexPtr p = new Complex();
	mpc_init2(p, NUMERIC_PRECISION);
	mpc_set_ui_ui(p, 0, 0, MPC_RNDNN);
	itsComplexFactoryData.push_back(p);
	return p;
}

void MathEvaluator::clearComplexFactory() {
	ComplexVector::size_type i, iend;
	i = 0; iend = itsComplexFactoryData.size();
	for (; i != iend; ++i) {
		mpc_clear(itsComplexFactoryData[i]);
		delete itsComplexFactoryData[i];
	}
	itsComplexFactoryData.clear();
}

RealPtr MathEvaluator::newReal() {
	RealPtr p = new Real();
	mpfr_init2(p, NUMERIC_PRECISION);
	mpfr_set_ui(p, 0, MPFR_RNDN);
	itsRealFactoryData.push_back(p);
	return p;
}

void MathEvaluator::clearRealFactory() {
	RealVector::size_type i, iend;
	i = 0; iend = itsRealFactoryData.size();
	for (; i != iend; ++i) {
		mpfr_clear(itsRealFactoryData[i]);
		delete itsRealFactoryData[i];
	}
	itsRealFactoryData.clear();
}

void MathEvaluator::collectlexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err_type) {
	LexerErrorPair p;
	p.char_index = char_index;
	p.err_type = err_type;
	itsLexerErrorsCollection.push_back(p);
}

void MathEvaluator::
SIUnit(MR_MATH_SI_PREFIXES si_prefix, ComplexPtr dest) {
	assert(dest != 0);
	mpfr_set_ui(mpc_imagref(dest), 0, MPFR_RNDN);

	switch (si_prefix) {
		case MR_MATH_SI_PREFIX_YOTTA:
			mpfr_set_str(mpc_realref(dest), "1e24", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZETTA:
			mpfr_set_str(mpc_realref(dest), "1e21", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_EXA:
			mpfr_set_str(mpc_realref(dest), "1e18", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PETA:
			mpfr_set_str(mpc_realref(dest), "1e15", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_TERA:
			mpfr_set_str(mpc_realref(dest), "1e12", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_GIGA:
			mpfr_set_str(mpc_realref(dest), "1e9", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MEGA:
			mpfr_set_str(mpc_realref(dest), "1e6", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_KILO:
			mpfr_set_str(mpc_realref(dest), "1e3", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_HECTO:
			mpfr_set_str(mpc_realref(dest), "1e2", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_DECA:
			mpfr_set_str(mpc_realref(dest), "1e1", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_DECI:
			mpfr_set_str(mpc_realref(dest), "1e-1", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_CENTI:
			mpfr_set_str(mpc_realref(dest), "1e-2", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MILLI:
			mpfr_set_str(mpc_realref(dest), "1e-3", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MICRO:
			mpfr_set_str(mpc_realref(dest), "1e-6", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_NANO:
			mpfr_set_str(mpc_realref(dest), "1e-9", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PICO:
			mpfr_set_str(mpc_realref(dest), "1e-12", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_FEMTO:
			mpfr_set_str(mpc_realref(dest), "1e-15", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ATTO:
			mpfr_set_str(mpc_realref(dest), "1e-18", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZEPTO:
			mpfr_set_str(mpc_realref(dest), "1e-21", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_YOCTO:
			mpfr_set_str(mpc_realref(dest), "1e-24", 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_KIBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 10, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_MEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 20, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_GIBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 30, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_TEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 40, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_PEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 50, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_EXBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 60, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_ZEBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 70, MPFR_RNDN);
			break;
		case MR_MATH_SI_PREFIX_YOBI:
			mpfr_set_ui_2exp(mpc_realref(dest), 1, 80, MPFR_RNDN);
			break;
	}
}

ComplexPtr MathEvaluator::binaryOperator (MR_MATH_BINARY_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newComplex();
	switch (which) {
		case MR_PLUS:
			mpc_add(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MINUS:
			mpc_sub(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MULTI:
			mpc_mul(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_DIV:
			mpc_div(retv, lv, rv, MPC_RNDNN);
			break;
		case MR_MOD:
			mpfr_fmod(mpc_realref(retv), mpc_realref(lv), mpc_realref(rv), MPFR_RNDN);
			break;
		case MR_POW:
			mpc_pow(retv, lv, rv, MPC_RNDNN);
			break;
	}
	return retv;
}

ComplexPtr MathEvaluator::bitwiseOperator (MR_MATH_BINARY_BITWISE_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv) {
	ComplexPtr retv = newComplex();

	quint64 lv64, rv64;
	quint32 lv32, rv32;
	quint16 lv16, rv16;
	quint8 lv8, rv8;

	switch (itsSettings->calculationBitWidth()) {
		case 64:
			lv64 = Conversion::convert_u64b(mpc_realref(lv));
			rv64 = Conversion::convert_u64b(mpc_realref(rv));
			break;
		case 32:
			lv32 = Conversion::convert_u32b(mpc_realref(lv));
			rv32 = Conversion::convert_u32b(mpc_realref(rv));
			break;
		case 16:
			lv16 = Conversion::convert_u16b(mpc_realref(lv));
			rv16 = Conversion::convert_u16b(mpc_realref(rv));
			break;
		case 8:
			lv8 = Conversion::convert_u8b(mpc_realref(lv));
			rv8 = Conversion::convert_u8b(mpc_realref(rv));
			break;
	}

	switch (which) {
		// bitwise AND
		case  MR_BITWISE_AND:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 & rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 & rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 & rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 & rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise OR
		case  MR_BITWISE_OR:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 | rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 | rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 | rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 | rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise NAND
		case  MR_BITWISE_NAND:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 & rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 & rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 & rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 & rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise NOR
		case  MR_BITWISE_NOR:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 | rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 | rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 | rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 | rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise XOR
		case  MR_BITWISE_XOR:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 ^ rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 ^ rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 ^ rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 ^ rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise XNOR
		case  MR_BITWISE_XNOR:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), ~(lv64 ^ rv64));
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), ~(lv32 ^ rv32), MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), ~(lv16 ^ rv16), MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), ~(lv8 ^ rv8), MPFR_RNDN);
					break;
			}
			break;
		// bitwise shift left
		case  MR_BITWISE_SHL:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 << rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 << rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 << rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 << rv8, MPFR_RNDN);
					break;
			}
			break;
		// bitwise shift right
		case  MR_BITWISE_SHR:
			switch (itsSettings->calculationBitWidth()) {
				case 64:	
					Conversion::mpfr_set_quint64(mpc_realref(retv), lv64 >> rv64);
					break;
				case 32:
					mpfr_set_ui(mpc_realref(retv), lv32 >> rv32, MPFR_RNDN);
					break;
				case 16:
					mpfr_set_ui(mpc_realref(retv), lv16 >> rv16, MPFR_RNDN);
					break;
				case 8:
					mpfr_set_ui(mpc_realref(retv), lv8 >> rv8, MPFR_RNDN);
					break;
			}
			break;
	}

	return retv;
}

ComplexPtr MathEvaluator::
unaryOperator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val) {
	ComplexPtr retv = newComplex();

	if (which == MR_BITWISE_NOT) {
		switch (itsSettings->calculationBitWidth()) {
			case 64:
				quint64 tmpI64;
				tmpI64 = Conversion::convert_u64b(mpc_realref(val));
				tmpI64 = ~tmpI64;
				Conversion::mpfr_set_quint64(mpc_realref(retv), tmpI64);
				break;
			case 32:
				quint32 tmpI32;
				tmpI32 = Conversion::convert_u32b(mpc_realref(val));
				tmpI32 = ~tmpI32;
				mpfr_set_ui(mpc_realref(retv), tmpI32, MPFR_RNDN);
				break;
			case 16:
				quint16 tmpI16;
				tmpI16 = Conversion::convert_u16b(mpc_realref(val));
				tmpI16 = ~tmpI16;
				mpfr_set_ui(mpc_realref(retv), tmpI16, MPFR_RNDN);
				break;
			case 8:
				quint8 tmpI8;
				tmpI8 = Conversion::convert_u8b(mpc_realref(val));
				tmpI8 = ~tmpI8;
				mpfr_set_ui(mpc_realref(retv), tmpI8, MPFR_RNDN);
				break;
		}
	} else if (which == MR_UNARY_MINUS) {
		mpc_mul_si(retv, val, -1, MPC_RNDNN);
	}
	return retv;
}

ComplexPtr MathEvaluator::
unaryFunction (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val) {
	ComplexPtr retv = newComplex();

	switch (which) {
		case MR_FUN_SIN:
			mpc_sin(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_COS:
			mpc_cos(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_TAN:
			mpc_tan(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ASIN:
			mpc_asin(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ACOS:
			mpc_acos(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ATAN:
			mpc_atan(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_SINH:
			mpc_sinh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_COSH:
			mpc_cosh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_TANH:
			mpc_tanh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ASINH:
			mpc_asinh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ACOSH:
			mpc_acosh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ATANH:
			mpc_atanh(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_EXP:
			mpc_exp(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_LOG:
			mpc_log(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_LOG10:
			Complex logOf10;
			mpc_init2(logOf10, NUMERIC_PRECISION);
			mpc_set_ui(logOf10, 10, MPC_RNDNN);
			mpc_log(logOf10, logOf10, MPC_RNDNN);

			mpc_log(retv, val, MPC_RNDNN);
			mpc_div(retv, retv, logOf10, MPC_RNDNN);

			mpc_clear(logOf10);
			break;
		case MR_FUN_SQRT:
			mpc_sqrt(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_ABS:
			mpc_abs(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_RE:
			mpc_set_fr(retv, mpc_realref(val), MPC_RNDNN);
			break;
		case MR_FUN_IM:
			mpfr_set(mpc_imagref(retv), mpc_imagref(val), MPFR_RNDN);
			break;
		case MR_FUN_ARG:
			mpc_arg(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_CONJ:
			mpc_conj(retv, val, MPC_RNDNN);
			break;
		case MR_FUN_DEG:
			mpfr_set(mpc_realref(retv), mpc_realref(val), MPFR_RNDN);
			mpfr_const_pi(mpc_imagref(retv), MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_mul_ui(mpc_realref(retv), mpc_realref(retv), 180, MPFR_RNDN);
			mpfr_div(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 360, MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_fmod(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 0, MPFR_RNDN);
			break;
		case MR_FUN_RAD:
			mpfr_set(mpc_realref(retv), mpc_realref(val), MPFR_RNDN);
			mpfr_const_pi(mpc_imagref(retv), MPFR_RNDN); // Temporarily, so we don't need to create another Real
			mpfr_mul(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_div_ui(mpc_realref(retv), mpc_realref(retv), 180, MPFR_RNDN);
			mpfr_mul_ui(mpc_imagref(retv), mpc_imagref(retv), 2, MPFR_RNDN);
			mpfr_fmod(mpc_realref(retv), mpc_realref(retv), mpc_imagref(retv), MPFR_RNDN);
			mpfr_set_ui(mpc_imagref(retv), 0, MPFR_RNDN);
			break;
		case MR_FUN_NORM:
			mpc_norm(mpc_realref(retv), val, MPFR_RNDN);
			break;
		case MR_FUN_POLAR:
			RealPtr fn;
			fn = newReal();
			mpfr_cos(fn, mpc_imagref(val), MPFR_RNDN);
			mpfr_mul(mpc_realref(retv), mpc_realref(val), fn, MPFR_RNDN);
			mpfr_sin(fn, mpc_imagref(val), MPFR_RNDN);
			mpfr_mul(mpc_imagref(retv), mpc_realref(val), fn, MPFR_RNDN);
			break;
	}
	return retv;
}

ComplexPtr MathEvaluator::
binaryFunction (MR_MATH_BINARY_FUNCTIONS which, ComplexConstPtr arg1, ComplexConstPtr arg2) {
	ComplexPtr retv = newComplex();
	switch (which) {
		case MR_FUN2_ATAN2:
			mpfr_atan2(mpc_realref(retv), mpc_realref(arg1), mpc_realref(arg2), MPFR_RNDN);
			break;
	}
	return retv;
}

} // mathy_resurrected
