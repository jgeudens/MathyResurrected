/* 
* Copyright (C) 2009
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

#include <antlr3.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <exception>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include "ComplexLexer.h"
#include "ComplexParser.h"
#include "ComplexEval.h"
#include "MathyResurrectedOptionsDialog.h"
#include "MathEvaluator.h"

using namespace std;
using namespace boost;

namespace mathy_resurrected {

MathEvaluator::lexer_errors_collection_t MathEvaluator::lexerErrorsCollection;
std::vector< boost::shared_ptr< mrComplex_t > > MathEvaluator::mr_ComplexFactoryData;

mrComplex_ptr MathEvaluator::getNewBridgeComplex() {
	 mrComplex_ptr p = new mrComplex_t;
	 p->real = 0; p->imag = 0;
	 boost::shared_ptr< mrComplex_t > sp(p);
	 mr_ComplexFactoryData.push_back(sp);
	 return p;
}

void MathEvaluator::addNewLexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err) {
	pair <unsigned int, MR_LEXER_ERROR_TYPES>p;
	p.first = char_index;
	p.second = err;
	lexerErrorsCollection.push_back(p);
}

#ifdef _DEBUG
void MathEvaluator::printLexerErrors() const {
	MathEvaluator::lexer_errors_collection_t::const_iterator i, iend;
	i = lexerErrorsCollection.begin();
	iend = lexerErrorsCollection.end();

	for (; i != iend; ++i) {
		cout << "Char at: " << (*i).first;
		cout << " Error: ";
		switch ((*i).second) {
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
	MathEvaluator::lexerErrorsCollection.clear();
	MathEvaluator::mr_ComplexFactoryData.clear();
}

MathEvaluator::MathEvaluator(QSettings* app_settings) : 
 	itsIsValid(false), itsIsValidated(false), itsIsEvaluated(false),
	itsExprLen(0)
{
	real = imag = 0;
	changeEvaluatorSettings(app_settings);
}

void MathEvaluator::changeEvaluatorSettings(QSettings* app_settings) {
	if (app_settings == NULL) {
		itsArgSeparator = defaultArgSeparator();
		itsOutputFormat = defaultOutputFormat();
		itsPrecision = defaultOutputPrecision();
	} else {
		itsArgSeparator = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameArgSeparator(), 
			defaultArgSeparator()).toChar();
			
		itsOutputFormat = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameOutputFormat(),
			defaultOutputFormat()).toChar();
		
		itsPrecision = app_settings->value(
			MathyResurrectedOptionsDialog::keyNamePrecision(),
			defaultOutputPrecision()).toInt();
	}

	if (itsArgSeparator == systemDecimalPoint()) {
		throw std::runtime_error("Function argument separator can't be same as system decimal separator!");
	}

	// Update result string if output format has changed. 
	toString();
}

/*! This should return same character that was used in grammar */
inline QChar MathEvaluator::internalDecimalPoint() const { 
	return QChar('.'); 
}
/*! This should return same character that was used in grammar */
inline QChar MathEvaluator::internalArgSeparator() const { 
	return QChar('#'); 
}

void MathEvaluator::setExpression(const QString& expression) {
	itsIsValidated = false;
	itsIsValid = false;
	itsIsEvaluated = false;
	itsExprString.reset();
	itsExprLen = 0;

	QString tmp_expr = expression;

	QChar intern = internalDecimalPoint();
	QChar sysDecP = systemDecimalPoint(); 
	if (intern != sysDecP) {
		tmp_expr.replace(sysDecP, intern);
	}

	intern = internalArgSeparator();
	if (intern != itsArgSeparator) {
		tmp_expr.replace(itsArgSeparator, intern);
	}

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
			/*! Currently just counting errors. In the future we could 
			could use collection of lexer errors provided by bridge API
			to analyze things before invoking parser. */
#ifdef _DEBUG
			printLexerErrors();
#endif // _DEBUG
			if (lpr.parser->pParser->rec->state->errorCount > 0) {
				itsIsValid = false;
				itsResult = "Malformed expression";
			} else {
				itsIsValid = true;
			}		
		}
		itsIsValidated = true;
	}
	return itsIsValid;
}

bool MathEvaluator::evaluate() {
	if (!itsIsEvaluated) {
		if (validate()) {

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
				mrComplex_ptr retv_val;

				try {
					retv_val = lpr.treeParser->prog(lpr.treeParser);
					this->real = retv_val->real;
					this->imag = retv_val->imag;
				}
				catch (NumericConversionError& e) {
					itsIsValid = false;
					itsResult = e.what();
				}
			}
		}
		itsIsEvaluated = true;
	}
	return itsIsValid;
}

const QString& MathEvaluator::toString() {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			QString sign;
			QString re_str, im_str;
			bool add_i = false;

			if ((boost::math::fpclassify)(imag) != FP_ZERO) {
				if (imag > 0) {
					sign = " + ";
				} else { // if (imag < 0) {
					sign = " - ";
				}

				mrNumeric_t tmp = abs(imag);
				numberToString(tmp, im_str);
				add_i = true;
			}
			numberToString(real, re_str);
			itsResult = re_str;
			if (add_i) {
				itsResult +=  sign + im_str + "i";
			}
		} else {
			itsResult = "Not evaluated!!!";
		}
	} // else {
	// result has been set to some error message during evaluation 
	// so don't touch it.

	return itsResult;
}

void MathEvaluator::numberToString(mrNumeric_t val, QString& retv) const {
	QLocale loc = QLocale::system();

	if (itsOutputFormat == 'd') { 
		retv = loc.toString(val, 'g', itsPrecision);
	} else if (itsOutputFormat == 's') {
		retv = loc.toString(val, 'e', itsPrecision);
	} else if (itsOutputFormat == 'f') {
		retv = loc.toString(val, 'f', itsPrecision);		
	}
}

} // mathy_resurrected