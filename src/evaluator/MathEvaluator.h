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

#ifndef MATHY_RESURRECTED_EVALUATOR
#define MATHY_RESURRECTED_EVALUATOR

#include <QString>
#include <QSettings>
#include <QLocale>
#include <vector>
#include <utility>
#include <boost/smart_ptr/shared_array.hpp>
#include "MathyResurrectedExceptions.h"
#include "math_bridge_API_types.h"
#include "math_bridge_globals.h"

namespace mathy_resurrected {

/*! Main class for mathematical expression evaluation. Can be used
to validate expression string or to fully evaluate it. Internally 
uses ANTLR generated lexer / parser for its job. 
@note
Current implementation relies on globally accessible factories and 
variables for communication between this class and ANTLR generated 
evaluator. Because of that, it only single instance of MathEvaluator
should exist at any time in program. If this is not ensured, evaluation
will result in unspecified behavior. */
class MathEvaluator : private mrComplex_t {
public:
	MathEvaluator(QSettings* app_settings = 0);

	// Input / output settings
	void changeEvaluatorSettings(QSettings* app_settings = 0);
	static QChar systemDecimalPoint() { return QLocale::system().decimalPoint(); }
	static QChar systemThousandSep() { return QLocale::system().groupSeparator(); }
	static QChar defaultArgSeparator() { return QChar(':'); } // Must never be '.' or ','
	static QString defaultDecimalPointTag();
	static QString defaultGroupingCharTag();
	static QChar defaultOutputFormat() { return QChar('d'); }
	static int defaultOutputPrecision() { return 2; }
	static bool defaultShowDigitGrouping() { return true; }
	static int defaultZeroTresholdExp() { return -15; }
	static bool defaultShouldUseZeroTreshold() { return true; }

	/*! Sets expression to be evaluated. */
	void setExpression (const QString& expression);
	/*! Validates expression. Doesn't evaluate it. */
	bool validate ();
	/*! Validates expression if it hasn't been validated and 
	evaluates it. @returns true if expression is valid. Results
	can be read using Re() and Im() methods. */
	bool evaluate ();
	/** Stores current state of calculation for future use by "ans" 
	variable in expression. */
	void storeAns();
	const mrComplex_t& ans() const { return itsBAPI.ans; }

	/*! Returns result of evaluation. If expression hasn't been evaluated, 
	or is invalid, return value is unspecified. */
	mrReal Re() const { return real; }
	/*! Returns result of evaluation. If expression hasn't been evaluated, 
	or is invalid, return value is unspecified. */
	mrReal Im() const { return imag; }

	QString toString() const;
	QString toStringBin() const;
	QString toStringHex() const;
	QString toStringOct() const;

	static qlonglong safe_convert(mrReal val, bool& ok, QString& error_mess);

#ifdef _DEBUG
	void printLexerErrors() const;
#endif // _DEBUG

	/*! This should return same character that was used in grammar */
	static QChar internalDecimalPoint() { return QChar('@'); }

private:
	// Evaluation state variables
	bool itsIsValidated;	/*!< true if expression has been validated */
	bool itsIsValid;		/*!< true if expression is valid */
	bool itsIsEvaluated;	/*!< true if expression has been evaluated */
	QString itsErrStr;		/*!< Error string */
	BridgeAPIGlobals itsBAPI;

	// Input expression variables
	/*! Type to hold expression that will be passed to lexer and parser. */
	typedef boost::shared_array < unsigned char > antlr8BitString_t;
	/*! Expression as string. 
		- Should be ASCII encoded. 
		- Locale or application specific decimal point should be replaced with 
		  internalDecimalPoint() before handing this string to lexer/parser
		- Locale or application specific function argument separator should be 
		  replaced with internalArgSeparator() before handing this string to 
		  lexer/parser */
	antlr8BitString_t itsExprString;
	/*! Length of expression string in sizeof(char). */
	unsigned int itsExprLen;

	// Input / output settings
	QChar itsArgSeparator;
	QChar itsDecimalPoint;
	QChar itsOutputFormat;
	int itsPrecision;
	bool itsShowGroupChar;
	double itsZeroTreshold;
	QChar itsGroupingCharacter;
	bool itsShowBasePrefix;
	/*! This should return same character that was used in grammar */
	static QChar internalArgSeparator() { return QChar('#'); }

	void numberToString(mrReal val, QString& retv, char baseTag) const;
	void toString(char baseTag, QString& dest) const;
	
	struct LexerParser;
	friend struct LexerParser;
};

} // mathy_resurrected

#endif // MATHY_RESURRECTED_EVALUATOR