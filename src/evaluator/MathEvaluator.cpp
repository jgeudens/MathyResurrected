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

#include "MathEvaluator.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include "ComplexLexer.h"
#include "ComplexParser.h"
#include "ComplexEval.h"
#include "Settings.h"
#include "Exceptions.h"
#include "math_bridge_globals.h"
#include "Conversion.h"

using namespace std;

namespace mathy_resurrected {

#ifdef _DEBUG
void MathEvaluator::printLexerErrors() const {
	unsigned int i = 0;
	unsigned int iend = BridgeAPIGlobals::getLexerErrors().size();

	for (; i != iend; ++i) {
		cout << "Char at: " << BridgeAPIGlobals::getLexerErrors()[i].char_index;
		cout << " Error: ";
		switch (BridgeAPIGlobals::getLexerErrors()[i].err_type) {
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
struct MathEvaluator::LexerParser {
	LexerParser(const antlr8BitString_t& expression, ANTLR3_UINT32 len);
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
MathEvaluator::LexerParser::LexerParser(const antlr8BitString_t& expression, ANTLR3_UINT32 len) {
	malloc_error = false;

	inputStream = //antlr3NewAsciiStringCopyStream(tmp, len, NULL);
		antlr3NewAsciiStringInPlaceStream(expression.get(), len, NULL);
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


MathEvaluator::MathEvaluator(const Settings* app_settings) : 
 	itsIsValid(false), itsIsValidated(false), itsIsEvaluated(false),
	itsExprLen(0)
{
	changeEvaluatorSettings(app_settings);
	real = imag = 0;
	storeAns();
}

void MathEvaluator::changeEvaluatorSettings(const Settings* app_settings) {
	if (app_settings == 0) {
		throw invalid_argument("Null pointer to evaluator settings!");
	}
	itsSettings = app_settings;
	BridgeAPIGlobals::setBitWidth(itsSettings->calculationBitWidth());
}

const Complex& MathEvaluator::ans() const { 
	return *BridgeAPIGlobals::getAns(); 
}

void MathEvaluator::setExpression(const QString& expression) {
	itsIsValidated = false;
	itsIsValid = false;
	itsIsEvaluated = false;
	itsExprString.reset();
	itsExprLen = 0;

	QString tmp_expr = expression;

	// Preprocessing expression...
	tmp_expr.replace(itsSettings->decimalPointAsChar(), Conversion::internalDecimalPoint());
	tmp_expr.replace(itsSettings->functionArgSeparatorAsChar(), Conversion::internalArgSeparator());

	QByteArray tmp = tmp_expr.toAscii();
	int iend = tmp.length();

	antlr8BitString_t p (new ANTLR3_UINT8[iend+1]);
	itsExprString = p;

	for (int i = 0; i < iend; ++i) {
		itsExprString[i] = tmp[i];
	}
	itsExprString[iend] = '\0';
	itsExprLen = iend;
}

bool MathEvaluator::validate() {
	
	if (!itsIsValidated) {
		LexerParser lpr (itsExprString, itsExprLen);

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

	BridgeAPIGlobals::clearComplexFactory();
	BridgeAPIGlobals::clearLexerErrors();
	return itsIsValid;
}

bool MathEvaluator::evaluate() {
	if (!itsIsEvaluated) {
		if (validate()) {

			itsErrStr.clear();

			LexerParser lpr (itsExprString, itsExprLen);

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
					this->real = retv_val->real;
					this->imag = retv_val->imag;
				}
				catch (NumericConversionError& e) {
					itsIsValid = false;
					itsErrStr = e.what();
				}
			}
		}
		itsIsEvaluated = true;
	}

	BridgeAPIGlobals::clearComplexFactory();
	BridgeAPIGlobals::clearLexerErrors();
	return itsIsValid;
}

void MathEvaluator::storeAns() {
	BridgeAPIGlobals::setAns(real, imag);
}

QString MathEvaluator::toString() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::DECIMAL, *itsSettings, *this);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

QString MathEvaluator::toStringBin() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::BINARY, *itsSettings, *this);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

QString MathEvaluator::toStringHex() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::HEXADECIMAL, *itsSettings, *this);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

QString MathEvaluator::toStringOct() const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			return Conversion::toString(Conversion::OCTAL, *itsSettings, *this);
		} else {
			return "Not evaluated!!!";
		}
	} else {
		return itsErrStr;
	}
}

} // mathy_resurrected