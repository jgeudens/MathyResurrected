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
#include <antlr3.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include "ComplexLexer.h"
#include "ComplexParser.h"
#include "ComplexEval.h"
#include "Settings.h"
#include "Exceptions.h"
#include <QLocale>

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


MathEvaluator::MathEvaluator(const Settings* app_settings) : 
 	itsIsValid(false), itsIsValidated(false), itsIsEvaluated(false),
	itsExprLen(0)
{
	changeEvaluatorSettings(app_settings);
	init_bridge_API(&itsBAPI);
	real = imag = 0;
	setAns(0, 0);
}

void MathEvaluator::changeEvaluatorSettings(const Settings* app_settings) {
	if (app_settings == 0) {
		throw invalid_argument("Null pointer to evaluator settings!");
	}
	itsSettings = app_settings;
	itsBAPI.bit_width = itsSettings->calculationBitWidth();
}

void MathEvaluator::setExpression(const QString& expression) {
	itsIsValidated = false;
	itsIsValid = false;
	itsIsEvaluated = false;
	itsExprString.reset();
	itsExprLen = 0;

	QString tmp_expr = expression;

	// Preprocessing expression...
	tmp_expr.replace(itsSettings->decimalPointAsChar(), internalDecimalPoint());
	tmp_expr.replace(itsSettings->functionArgSeparatorAsChar(), internalArgSeparator());

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
			if (abs(im_disp) < pow(10.0, itsSettings->zeroTresholdExp())) {
				im_disp = 0;
			}
			if (abs(re_disp) < pow(10.0, itsSettings->zeroTresholdExp())) {
				re_disp = 0;
			}

			// Formating output of imaginary part
			if ((boost::math::fpclassify)(im_disp) != FP_ZERO) {
				// Display as decimal
				if (baseTag == 'd') {
					if (im_disp > 0) {
						im_sign = " + ";
					} else { // if (imag < 0) {
						im_sign = " - ";
					}
					mrReal tmp = abs(im_disp);
					numberToString(tmp, im_str, baseTag);
				} else { // Display as any other base
					im_sign = " + ";
					numberToString(im_disp, im_str, baseTag);
				}
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
//	try {
// 		retv = numeric_cast<intT>(val);
// 		ok = true;
// 	}
// 	catch (bad_numeric_cast&) {
// 		ok = false;
// 	}
	retv = val; ok = true;
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
// 	if (val < 0) {
// 		bho_sign = "-";
// 	}
//	mrReal absVal = abs(val);
	mrReal absVal = val;
	switch (baseTag) {
		case 'b':
			switch (itsSettings->calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 2);
						if (itsSettings->showLeadingZeroesBin()) {
							retv = retv.rightJustified(64, '0');
						}
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 2);
						if (itsSettings->showLeadingZeroesBin()) {
							retv = retv.rightJustified(32, '0');
						}
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 2);
						if (itsSettings->showLeadingZeroesBin()) {
							retv = retv.rightJustified(16, '0');
						}
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 2);
						if (itsSettings->showLeadingZeroesBin()) {
							retv = retv.rightJustified(8, '0');
						}
					} else {
						retv = "8b int range error";
					}
					break;
			}
			if (itsSettings->showBasePrefix()) {
				retv.insert(0, "0b");
			}
			retv.insert(0, bho_sign);
			break;
		case 'h':
			switch (itsSettings->calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 16).toUpper();
						if (itsSettings->showLeadingZeroesHex()) {
							retv = retv.rightJustified(16, '0');
						}
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 16).toUpper();
						if (itsSettings->showLeadingZeroesHex()) {
							retv = retv.rightJustified(8, '0');
						}
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 16).toUpper();
						if (itsSettings->showLeadingZeroesHex()) {
							retv = retv.rightJustified(4, '0');
						}
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 16).toUpper();
						if (itsSettings->showLeadingZeroesHex()) {
							retv = retv.rightJustified(2, '0');
						}
					} else {
						retv = "8b int range error";
					}
					break;
			}
			if (itsSettings->showBasePrefix()) {
				retv.insert(0, "0x");
			}
			retv.insert(0, bho_sign);
			break;
		case 'o':
			switch (itsSettings->calculationBitWidth()) {
				case Settings::BW64:
					tmpI64 = safe_convert_u64b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI64, 8);
					} else {
						retv = "64b int range error";
					}
					break;
				case Settings::BW32:
					tmpI32 = safe_convert_u32b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI32, 8);
					} else {
						retv = "32b int range error";
					}
					break;
				case Settings::BW16:
					tmpI16 = safe_convert_u16b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI16, 8);
					} else {
						retv = "16b int range error";
					}
					break;
				case Settings::BW8:
					tmpI8 = safe_convert_u8b(absVal, ok_flag);
					if (ok_flag) {
						retv += QString::number(tmpI8, 8);
					} else {
						retv = "8b int range error";
					}
					break;
			}
			if (itsSettings->showBasePrefix()) {
				retv.insert(0, "0");
			}
			retv.insert(0, bho_sign);
			break;
		case 'd':
		default:
			if (itsSettings->outputFormat() == Settings::AUTOMATIC) { 
				retv = loc.toString(val, 'g', itsSettings->precision());
			} else if (itsSettings->outputFormat() == Settings::SCIENTIFFIC) {
				retv = loc.toString(val, 'e', itsSettings->precision());
			} else if (itsSettings->outputFormat() == Settings::FIXED) {
				retv = loc.toString(val, 'f', itsSettings->precision());		
			}

			// Post processing

			// First, "saving" decimal point from modification.
			// This is relatively safe because internally used 
			// character for decimal point representation is 
			// not likely to be used for that purpose in any 
			// existing locale. 
			retv.replace(loc.decimalPoint(), internalDecimalPoint());

			// Post processing group separator. 
			if (!itsSettings->outputDigitGrouping()) {
				retv.remove(loc.groupSeparator());
			} else {
				retv.replace(loc.groupSeparator(), itsSettings->digitGroupingCharacterAsChar());
			}

			// Post processing decimal point. 
			retv.replace(internalDecimalPoint(), itsSettings->decimalPointAsChar());

			break;
	}
}

} // mathy_resurrected