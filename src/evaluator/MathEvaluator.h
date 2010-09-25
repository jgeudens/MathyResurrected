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
#include <QObject>
#include "math_bridge_API_types.h"

namespace mathy_resurrected {

class Settings;

/*! Main class for mathematical expression evaluation. Can be used
to validate expression string or to fully evaluate it. Internally 
uses ANTLR generated lexer / parser for its job. 
@note
Current implementation relies on globally accessible factories and 
variables for communication between this class and ANTLR generated 
evaluator. Because of that, only single instance of MathEvaluator
should exist at any time in program. If this is not ensured, evaluation
will result in unspecified behavior. */
class MathEvaluator : public QObject {

	Q_OBJECT

public:
	MathEvaluator(const Settings* app_settings, QObject* parent = 0);
	virtual ~MathEvaluator();

	const Real& Re() const;
	const Real& Im() const;

	const QString toString() const;
	const QString toStringBin() const;
	const QString toStringHex() const;
	const QString toStringOct() const;

#ifdef _DEBUG
	void printLexerErrors() const;
#endif // _DEBUG

public slots:
	void changeEvaluatorSettings(const Settings* settings);

	/*! Sets expression to be evaluated. */
	void setExpression (const QString& expression);
	/*! Validates expression. Doesn't evaluate it. */
	bool validate ();
	/*! Validates expression if it hasn't been validated and 
	evaluates it. Returns true if expression is valid. Results
	can be read using Re() and Im() methods. */
	bool evaluate ();
	/** Stores current state of calculation for future use by "ans" 
	variable in expression. */
	void storeAns();

private:
	// Evaluation state variables
	bool itsIsValidated;	/*!< true if expression has been validated */
	bool itsIsValid;		/*!< true if expression is valid */
	bool itsIsEvaluated;	/*!< true if expression has been evaluated */
	QString itsErrStr;		/*!< Error string */

	const Settings* itsSettings; /**< Evaluator settings. Non-owned pointer to const object. */

	/** - Locale or application specific decimal point should be replaced with 
		  internalDecimalPoint() before handing this string to lexer/parser
		- Locale or application specific function argument separator should be 
		  replaced with internalArgSeparator() before handing this string to 
		  lexer/parser */
	QString itsExprString; 
	Complex itsValue;

	class LexerParser;
	friend class LexerParser;
};

} // mathy_resurrected

#endif // MATHY_RESURRECTED_EVALUATOR