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
* along with MathyResurrected. If not, see <http://www.gnu.org/licenses/>. */

#ifndef MATHY_RESURRECTED_EVALUATOR
#define MATHY_RESURRECTED_EVALUATOR

#include <QString>
#include <QObject>
#include <vector>

#include "math_bridge_API_types.h"

namespace mathy_resurrected {

class Settings;

/*! Main class for mathematical expression evaluation. Can be used
to validate expression string or to fully evaluate it. Internally 
uses ANTLR generated lexer / parser for its job. */
class MathEvaluator : public QObject {

	Q_OBJECT

public:
	MathEvaluator(const Settings* app_settings, QObject* parent = 0);
	virtual ~MathEvaluator();

	const Settings& settings() const;

	const Real& Re() const;
	const Real& Im() const;

	const QString toString() const;
	const QString toStringBin() const;
	const QString toStringHex() const;
	const QString toStringOct() const;

	static void pi(ComplexPtr dest);
	static void e(ComplexPtr dest);
	void ans(ComplexPtr dest);

	ComplexPtr newComplex();
	RealPtr newReal();
	void collectlexerError(unsigned int char_index, MR_LEXER_ERROR_TYPES err_type);

	static const int NUMERIC_PRECISION;

	void SIUnit(MR_MATH_SI_PREFIXES si_prefix, ComplexPtr dest);
	ComplexPtr binaryOperator (MR_MATH_BINARY_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv);
	ComplexPtr bitwiseOperator (MR_MATH_BINARY_BITWISE_OPERATORS which, ComplexConstPtr lv, ComplexConstPtr rv);
	ComplexPtr unaryOperator (MR_MATH_UNARY_OPERATORS which, ComplexConstPtr val);
	ComplexPtr unaryFunction (MR_MATH_UNARY_FUNCTIONS which, ComplexConstPtr val);
	ComplexPtr binaryFunction (MR_MATH_BINARY_FUNCTIONS which, ComplexConstPtr arg1, ComplexConstPtr arg2);

public slots:
	void setExpression(const QString& expression);
	bool validate ();
	bool evaluate ();
	void storeAns();

private:
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
	Complex itsValue; /**< Evaluation result */
	Complex itsAns; /**< Result stored by last call to storeAns(). */

	class LexerParser;
	friend class LexerParser;

	struct LexerErrorPair{
		unsigned int char_index;
		MR_LEXER_ERROR_TYPES err_type;
	};
	typedef std::vector <LexerErrorPair> LexerErrorsCollection;
	typedef std::vector<ComplexPtr> ComplexVector;
	typedef std::vector<RealPtr> RealVector;
	ComplexVector itsComplexFactoryData; /*!< Data storage for factory produced objects. */
	RealVector itsRealFactoryData; /*!< Data storage for factory produced objects. */
	LexerErrorsCollection itsLexerErrorsCollection; /*!< Lexer errors collected here during lexing phase. */
	void clearComplexFactory();
	void clearRealFactory();

#ifdef _DEBUG
public:
	void printLexerErrors() const;
#endif // _DEBUG
};

} // mathy_resurrected

#endif // MATHY_RESURRECTED_EVALUATOR