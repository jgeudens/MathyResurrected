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

#include <antlr3.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <exception>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>
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
mrComplex_t MathEvaluator::itsAns;

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

QString MathEvaluator::defaultDecimalPointTag() {
	return MathyResurrectedOptionsDialog::systemDecPointTag(); 
}

QString MathEvaluator::defaultGroupingCharTag()  {
	return MathyResurrectedOptionsDialog::systemGroupingCharTag(); 
}

MathEvaluator::MathEvaluator(QSettings* app_settings) : 
 	itsIsValid(false), itsIsValidated(false), itsIsEvaluated(false),
	itsExprLen(0)
{
	real = imag = 0;
	itsAns.real = itsAns.imag = 0;
	changeEvaluatorSettings(app_settings);
}

void MathEvaluator::changeEvaluatorSettings(QSettings* app_settings) {
	if (app_settings == NULL) {
		itsArgSeparator = defaultArgSeparator();
		itsOutputFormat = defaultOutputFormat();
		itsPrecision = defaultOutputPrecision();
		itsShowGroupChar = defaultShowDigitGrouping();
		itsZeroTreshold = pow (10.0, defaultZeroTresholdExp());
		itsDecimalPoint = MathyResurrectedOptionsDialog::decPointTag2Char(defaultDecimalPointTag());
		itsGroupimgCharacter = MathyResurrectedOptionsDialog::digitGroupTag2Char(defaultGroupingCharTag());
	} else {
		itsArgSeparator = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameArgSeparator(), 
			defaultArgSeparator()).toChar();

		itsDecimalPoint = MathyResurrectedOptionsDialog::decPointTag2Char(
			app_settings->value(MathyResurrectedOptionsDialog::keyNameDecimalPoint(), "").toString()
			);

		itsGroupimgCharacter = MathyResurrectedOptionsDialog::digitGroupTag2Char(
			app_settings->value(MathyResurrectedOptionsDialog::keyNameGroupingChar(), "").toString()
			);
			
		itsOutputFormat = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameOutputFormat(),
			defaultOutputFormat()).toChar();
		
		itsPrecision = app_settings->value(
			MathyResurrectedOptionsDialog::keyNamePrecision(),
			defaultOutputPrecision()).toInt();

		itsShowGroupChar = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameShowDigitGrouping(), 
			defaultShowDigitGrouping()).toBool();

		bool shouldUse = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameShouldUseZeroTreshold(), 
			defaultShouldUseZeroTreshold()).toBool();

		if (shouldUse) {
			itsZeroTreshold = app_settings->value(
				MathyResurrectedOptionsDialog::keyNameZeroTresholdExp(), 
				defaultZeroTresholdExp()).toInt();
			itsZeroTreshold = pow (10.0, itsZeroTreshold);
		} else {
			itsZeroTreshold = 0;
		}
	}

	if (itsArgSeparator == itsDecimalPoint) {
		itsArgSeparator = defaultArgSeparator();
	}

	// Update result string if output format has changed. 
	toString();
}

void MathEvaluator::setExpression(const QString& expression) {
	itsIsValidated = false;
	itsIsValid = false;
	itsIsEvaluated = false;
	itsExprString.reset();
	itsExprLen = 0;

	QString tmp_expr = expression;

	// Preprocessing expression...
	tmp_expr.replace(itsDecimalPoint, internalDecimalPoint());
	tmp_expr.replace(itsArgSeparator, internalArgSeparator());

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
			// could use collection of lexer errors provided by bridge API
			// to analyze things before invoking parser.
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

void MathEvaluator::storeAns() {
	itsAns.real = real; itsAns.imag = imag;
}

const QString& MathEvaluator::toString() {
	toString('d', itsResult);
	return itsResult;
}

QString MathEvaluator::toStringBin() {
	QString retv;
	toString('b', retv);
	return retv;
}

QString MathEvaluator::toStringHex() {
	QString retv;
	toString('h', retv);
	return retv;
}

QString MathEvaluator::toStringOct() {
	QString retv;
	toString('o', retv);
	return retv;
}

void MathEvaluator::toString(char baseTag, QString& dest) {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			QString sign;
			QString re_str, im_str;
			bool add_i = false;

			// If number is close enough to zero, we make it zero 
			// explicitly (but for display purposes only)
			mrNumeric_t im_disp = imag, re_disp = real;
			if (abs(im_disp) < abs(itsZeroTreshold)) {
				im_disp = 0;
			}
			if (abs(re_disp) < abs(itsZeroTreshold)) {
				re_disp = 0;
			}

			if ((boost::math::fpclassify)(im_disp) != FP_ZERO) {
				if (im_disp > 0) {
					sign = " + ";
				} else { // if (imag < 0) {
					sign = " - ";
				}

				mrNumeric_t tmp = abs(im_disp);
				numberToString(tmp, im_str, baseTag);
				add_i = true;
			}
			numberToString(re_disp, re_str, baseTag);
			dest = re_str;
			if (add_i) {
				dest +=  sign + im_str + "i";
			}
		} else {
			dest = "Not evaluated!!!";
		}
	} // else {
	// result has been set to some error message during evaluation 
	// so don't touch it.
}

void MathEvaluator::numberToString(mrNumeric_t val, QString& retv, char baseTag) const {
	QLocale loc = QLocale::c();

	unsigned long tmp = numeric_cast<unsigned long>(val);
	switch (baseTag) {
		case 'b':
			retv = QString::number(tmp, 2);
			break;
		case 'h':
			retv = QString::number(tmp, 16).toUpper();
			break;
		case 'o':
			retv = QString::number(tmp, 8);
			break;
		case 'd':
		default:
			if (itsOutputFormat == 'd') { 
				retv = loc.toString(val, 'g', itsPrecision);
			} else if (itsOutputFormat == 's') {
				retv = loc.toString(val, 'e', itsPrecision);
			} else if (itsOutputFormat == 'f') {
				retv = loc.toString(val, 'f', itsPrecision);		
			}

			// Post processing

			// First, "saving" decimal point from modification.
			// This is relatively safe because internally used 
			// character for decimal point representation is 
			// not likely to be used for that purpose in any 
			// existing locale. 
			retv.replace(loc.decimalPoint(), internalDecimalPoint());

			// Post processing group separator. 
			if (!itsShowGroupChar) {
				retv.remove(loc.groupSeparator());
			} else {
				retv.replace(loc.groupSeparator(), itsGroupimgCharacter);
			}

			// Postprocessing decimal point. 
			retv.replace(internalDecimalPoint(), itsDecimalPoint);

			break;
	}
}

} // mathy_resurrected