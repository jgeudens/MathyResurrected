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

#ifdef _DEBUG
void MathEvaluator::printLexerErrors() const {
	unsigned int i = 0;
	unsigned int iend = itsBAPI.lexerErrorsCollection.size();

	for (; i != iend; ++i) {
		cout << "Char at: " << itsBAPI.lexerErrorsCollection[i].char_index;
		cout << " Error: ";
		switch (itsBAPI.lexerErrorsCollection[i].err_type) {
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
	init_bridge_API(&itsBAPI);
	real = imag = 0;
	setAns(0, 0);
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
		itsGroupingCharacter = MathyResurrectedOptionsDialog::digitGroupTag2Char(defaultGroupingCharTag());
		itsIntWidth = defaultBitWidth();
	} else {
		itsArgSeparator = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameArgSeparator(), 
			defaultArgSeparator()).toChar();

		itsDecimalPoint = MathyResurrectedOptionsDialog::decPointTag2Char(
			app_settings->value(MathyResurrectedOptionsDialog::keyNameDecimalPoint(), "").toString()
			);

		itsGroupingCharacter = MathyResurrectedOptionsDialog::digitGroupTag2Char(
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

		itsShowBasePrefix = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameShowBasePrefix(), 
			MathyResurrectedOptionsDialog::defaultShowBasePrefix()).toBool();

		itsIntWidth = app_settings->value(
			MathyResurrectedOptionsDialog::keyNameBitWidth(),
			defaultBitWidth()).toUInt();
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

	itsBAPI.complexFactoryData.clear();
	itsBAPI.lexerErrorsCollection.clear();
	return itsIsValid;
}

bool MathEvaluator::evaluate() {
	if (!itsIsEvaluated) {
		if (validate()) {

			itsErrStr = "";

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
					itsErrStr = e.what();
				}
			}
		}
		itsIsEvaluated = true;
	}

	itsBAPI.complexFactoryData.clear();
	itsBAPI.lexerErrorsCollection.clear();
	return itsIsValid;
}

void MathEvaluator::storeAns() {
	itsBAPI.ans.real = real; itsBAPI.ans.imag = imag;
}

QString MathEvaluator::toString() const {
	QString retv;
	toString('d', retv);
	return retv;
}

QString MathEvaluator::toStringBin() const {
	QString retv;
	toString('b', retv);
	return retv;
}

QString MathEvaluator::toStringHex() const {
	QString retv;
	toString('h', retv);
	return retv;
}

QString MathEvaluator::toStringOct() const {
	QString retv;
	toString('o', retv);
	return retv;
}

void MathEvaluator::toString(char baseTag, QString& dest) const {
	if (itsIsValid) {
		if (itsIsEvaluated) {
			QString im_sign;
			QString re_str, im_str;
			bool add_i = false;

			// If number is close enough to zero, we make it zero 
			// explicitly (but for display purposes only)
			mrReal im_disp = imag, re_disp = real;
			if (abs(im_disp) < abs(itsZeroTreshold)) {
				im_disp = 0;
			}
			if (abs(re_disp) < abs(itsZeroTreshold)) {
				re_disp = 0;
			}

			if ((boost::math::fpclassify)(im_disp) != FP_ZERO) {
				if (im_disp > 0) {
					im_sign = " + ";
				} else { // if (imag < 0) {
					im_sign = " - ";
				}

				mrReal tmp = abs(im_disp);
				numberToString(tmp, im_str, baseTag);
				add_i = true;
			}
			numberToString(re_disp, re_str, baseTag);
			dest = re_str;
			if (add_i) {
				dest +=  im_sign + im_str + "i";
			}
		} else {
			dest = "Not evaluated!!!";
		}
	} else {
		dest = itsErrStr;
	}
}

qint8 MathEvaluator::safe_convert_8b(mrReal val, bool& ok) {
	return safe_convert<qint8>(val, ok);
}

qint16 MathEvaluator::safe_convert_16b(mrReal val, bool& ok) {
	return safe_convert<qint8>(val, ok);
}

qint32 MathEvaluator::safe_convert_32b(mrReal val, bool& ok) {
	return safe_convert<qint32>(val, ok);
}

qint64 MathEvaluator::safe_convert_64b(mrReal val, bool& ok) {
	return safe_convert<qint64>(val, ok);
}

quint8 MathEvaluator::safe_convert_u8b(mrReal val, bool& ok) {
	return safe_convert<quint8>(val, ok);
}

quint16 MathEvaluator::safe_convert_u16b(mrReal val, bool& ok) {
	return safe_convert<quint16>(val, ok);
}

quint32 MathEvaluator::safe_convert_u32b(mrReal val, bool& ok) {
	return safe_convert<quint32>(val, ok);
}

quint64 MathEvaluator::safe_convert_u64b(mrReal val, bool& ok) {
	return safe_convert<quint64>(val, ok);
}

template <class intT>
intT MathEvaluator::safe_convert(mrReal val, bool& ok) {
	intT retv;
	try {
		retv = numeric_cast<intT>(val);
		ok = true;
	}
	catch (bad_numeric_cast&) {
		ok = false;
	}
	return retv;
}

void MathEvaluator::numberToString(mrReal val, QString& retv, char baseTag) const {
	QLocale loc = QLocale::c();
	bool ok_flag;
	quint64 tmpI64;
	quint32 tmpI32;
	quint16 tmpI16;
	quint8 tmpI8;
	QString bho_sign, bho_prefix;
	if (val < 0) {
		bho_sign = "-";
	}
	mrReal absVal = abs(val);
	switch (baseTag) {
		case 'b':
			retv += bho_sign;
			if (itsShowBasePrefix) {
				retv += "0b";
			}
			switch (itsIntWidth) {
				case 64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 2);
					} else {
						retv = "64b int range error";
					}
					break;
				case 32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 2);
					} else {
						retv = "32b int range error";
					}
					break;
				case 16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 2);
					} else {
						retv = "16b int range error";
					}
					break;
				case 8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 2);
					} else {
						retv = "8b int range error";
					}
				default:
					break;
			}			
			break;
		case 'h':
			retv += bho_sign;
			if (itsShowBasePrefix) {
				retv += "0x";
			}
			switch (itsIntWidth) {
				case 64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 16).toUpper();
					} else {
						retv = "64b int range error";
					}
					break;
				case 32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 16).toUpper();
					} else {
						retv = "32b int range error";
					}
					break;
				case 16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 16).toUpper();
					} else {
						retv = "16b int range error";
					}
					break;
				case 8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 16).toUpper();
					} else {
						retv = "8b int range error";
					}
				default:
					break;
			}
			break;
		case 'o':
			retv += bho_sign;
			if (itsShowBasePrefix) {
				retv += "0";
			}
			switch (itsIntWidth) {
				case 64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 8);
					} else {
						retv = "64b int range error";
					}
					break;
				case 32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 8);
					} else {
						retv = "32b int range error";
					}
					break;
				case 16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 8);
					} else {
						retv = "16b int range error";
					}
					break;
				case 8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 8);
					} else {
						retv = "8b int range error";
					}
				default:
					break;
			}
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
				retv.replace(loc.groupSeparator(), itsGroupingCharacter);
			}

			// Postprocessing decimal point. 
			retv.replace(internalDecimalPoint(), itsDecimalPoint);

			break;
	}
}

} // mathy_resurrected