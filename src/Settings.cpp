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

#include "Settings.h"
#include <QLocale>
#include <QSettings>

namespace mathy_resurrected {

Settings::Settings(QObject* parent/* = 0*/) : 
	QObject(parent) 
{
	setDefaults();
}

Settings::~Settings() {}

QChar Settings::systemDecimalPoint() { return QLocale::system().decimalPoint(); }
QChar Settings::systemDigitGrouping() { return QLocale::system().groupSeparator(); }

QChar Settings::functionArgSeparatorAsChar() const {
	QChar retv;
	switch (itsFunctionArgSeparator) {
		case ARG_SEPARATOR_COLON:
			retv = ':';
			break;
		case ARG_SEPARATOR_SEMICOLON:
			retv = ';';
			break;
		case ARG_SEPARATOR_COMA:
		default:
			retv = ',';
			break;
	}
	return retv;
}

QChar Settings::decimalPointAsChar() const {
	QChar retv;
	switch (itsDecimalPoint) {
		case DEC_POINT_COMA:
			retv = ',';
			break;
		case DEC_POINT_DOT:
			retv = '.';
			break;
		case DEC_POINT_SYSTEM:
		default:
			retv = systemDecimalPoint();
			break;
	}
	return retv;
}

QChar Settings::digitGroupingCharacterAsChar() const {
	QChar retv;
	switch (itsDigitGroupingCharacter) {
		case DIGIT_GROUPING_SYSTEM:
			retv = systemDigitGrouping();
			break;
		case DIGIT_GROUPING_DOT:
			retv = '.';
			break;
		case DIGIT_GROUPING_COMA:
		default:
			retv = systemDecimalPoint();
			break;
	}
	return retv;
}

void Settings::setDefaults() {
	itsDecimalPoint = defaultDecimalPoint();
	itsFunctionArgSeparator = defaultFunctionArgSeparator();
	itsUseSimpleInputMatching = defaultUseSimpleInputMatching();
	itsOutputFormat = defaultOutputFormat();
	itsOutputDigitGrouping = defaultOutputDigitGrouping();
	itsDigitGroupingCharacter = defaultDigitGroupingCharacter();
	itsPrecision = defaultPrecision();
	itsShowSmallNumbersAsZero = defaultShowSmallNumbersAsZero();
	itsZeroTresholdExp = defaultZeroTresholdExp();
	itsUseEnterToCopy = defaultUseEnterToCopy();
	itsShowDecOutput = defaultShowDecOutput();
	itsShowBinOutput = defaultShowBinOutput();
	itsShowHexOutput = defaultShowHexOutput();
	itsShowOctOutput = defaultShowOctOutput();
	itsShowBasePrefix = defaultShowBasePrefix();
	itsShowLeadingZeroesBin = defaultShowLeadingZeroesBin();
	itsShowLeadingZeroesHex = defaultShowLeadingZeroesHex();
	itsCalculationBitWidth = defaultCalculationBitWidth();
}

void Settings::writeSettings(QSettings* dest) const {
	if (dest != 0) {
		dest->beginGroup("MathyResurrected");
		dest->remove("");
		dest->endGroup();

		switch (itsFunctionArgSeparator) {
			case ARG_SEPARATOR_COLON:
				dest->setValue(keyNameFunctionArgSeparator(), QChar(':'));
				break;
			case ARG_SEPARATOR_SEMICOLON:
				dest->setValue(keyNameFunctionArgSeparator(), QChar(';'));
				break;
			case ARG_SEPARATOR_COMA:
			default:
				dest->setValue(keyNameFunctionArgSeparator(), QChar(','));
				break;
		}

		switch (itsDecimalPoint) {
			case DEC_POINT_COMA:
				dest->setValue(keyNameDecimalPoint(), QChar(','));
				break;
			case DEC_POINT_DOT:
				dest->setValue(keyNameDecimalPoint(), QChar('.'));
				break;
			case DEC_POINT_SYSTEM:
			default:
				dest->setValue(keyNameDecimalPoint(), QChar('s'));
				break;
		}

		switch (itsDigitGroupingCharacter) {
			case DIGIT_GROUPING_SYSTEM:
				dest->setValue(keyNameDigitGroupingCharacter(), QChar('s'));
				break;
			case DIGIT_GROUPING_DOT:
				dest->setValue(keyNameDigitGroupingCharacter(), QChar('.'));
				break;
			case DIGIT_GROUPING_COMA:
			default:
				dest->setValue(keyNameDigitGroupingCharacter(), QChar(','));
				break;
		}

		switch (itsOutputFormat) {
			case AUTOMATIC:
				dest->setValue(keyNameOutputFormat(), QChar('a'));
				break;
			case FIXED:
				dest->setValue(keyNameOutputFormat(), QChar('f'));
				break;
			case SCIENTIFFIC:
			default:
				dest->setValue(keyNameOutputFormat(), QChar('s'));
				break;
		}

		dest->setValue(keyNameUseSimpleInputMatching(), itsUseSimpleInputMatching);
		dest->setValue(keyNameOutputDigitGrouping(), itsOutputDigitGrouping);
		dest->setValue(keyNamePrecision(), itsPrecision);
		dest->setValue(keyNameShowSmallNumbersAsZero(), itsShowSmallNumbersAsZero);
		dest->setValue(keyNameZeroTresholdExp(), itsZeroTresholdExp);
		dest->setValue(keyNameUseEnterToCopy(), itsUseEnterToCopy);
		dest->setValue(keyNameShowDecOutput(), itsShowDecOutput);
		dest->setValue(keyNameShowBinOutput(), itsShowBinOutput);
		dest->setValue(keyNameShowHexOutput(), itsShowHexOutput);
		dest->setValue(keyNameShowOctOutput(), itsShowOctOutput);
		dest->setValue(keyNameShowBasePrefix(), itsShowBasePrefix);
		dest->setValue(keyNameShowLeadingZeroesBin(), itsShowLeadingZeroesBin);
		dest->setValue(keyNameShowLeadingZeroesHex(), itsShowLeadingZeroesHex);
		dest->setValue(keyNameCalculationBitWidth(), itsCalculationBitWidth);
	}
}

void Settings::readSettings(const QSettings* settings) {
	if (settings != 0) {
		
		int tmpI = settings->value(keyNameCalculationBitWidth(), ':').toInt();
		switch (tmpI) {
			case 8:
				itsCalculationBitWidth = BW8;
				break;
			case 16:
				itsCalculationBitWidth = BW16;
				break;
			case 32:
				itsCalculationBitWidth = BW32;
				break;
			case 64:
			default:
				itsCalculationBitWidth = BW64;
				break;
		}

		QChar tmp;
		tmp = settings->value(keyNameFunctionArgSeparator(), ':').toChar();
		switch (tmp.toAscii()) {
			case ':':
				setFunctionArgSeparator(ARG_SEPARATOR_COLON);
				break;
			case ';':
				setFunctionArgSeparator(ARG_SEPARATOR_SEMICOLON);
				break;
			case ',':
			default:
				setFunctionArgSeparator(ARG_SEPARATOR_COMA);
				break;
		}

		tmp = settings->value(keyNameDecimalPoint(), 's').toChar();
		switch (tmp.toAscii()) {
			case ',':
				setDecimalPoint(DEC_POINT_COMA);
				break;
			case '.':
				setDecimalPoint(DEC_POINT_DOT);
				break;
			case 's':
			default:
				setDecimalPoint(DEC_POINT_SYSTEM);
				break;
		}

		tmp = settings->value(keyNameDigitGroupingCharacter(), 's').toChar();
		switch (tmp.toAscii()) {
			case 's':
				itsDigitGroupingCharacter = DIGIT_GROUPING_SYSTEM;
				break;
			case '.':
				itsDigitGroupingCharacter = DIGIT_GROUPING_DOT;
				break;
			case ',':
			default:
				itsDigitGroupingCharacter = DIGIT_GROUPING_COMA;
				break;
		}

		tmp = settings->value(keyNameOutputFormat(), 'a').toChar();
		switch (tmp.toAscii()) {
			case 'a':
				itsOutputFormat = AUTOMATIC;
				break;
			case 's':
				itsOutputFormat = SCIENTIFFIC;
				break;
			case 'f':
			default:
				itsOutputFormat = FIXED;
				break;
		}

		itsUseSimpleInputMatching = settings->value(
			keyNameUseSimpleInputMatching(), defaultUseSimpleInputMatching()).toBool();
		itsOutputDigitGrouping = settings->value(
			keyNameOutputDigitGrouping(), defaultOutputDigitGrouping()).toBool();
		itsPrecision = settings->value(
			keyNamePrecision(), defaultPrecision()).toInt();
		itsShowSmallNumbersAsZero = settings->value(
			keyNameShowSmallNumbersAsZero(), defaultShowSmallNumbersAsZero()).toBool();
		itsZeroTresholdExp = settings->value(
			keyNameZeroTresholdExp(), defaultZeroTresholdExp()).toInt();
		itsUseEnterToCopy = settings->value(
			keyNameUseEnterToCopy(), defaultUseEnterToCopy()).toBool();
		itsShowDecOutput = settings->value(
			keyNameShowDecOutput(), defaultShowDecOutput()).toBool();
		itsShowBinOutput = settings->value(
			keyNameShowBinOutput(), defaultShowBinOutput()).toBool();
		itsShowHexOutput = settings->value(
			keyNameShowHexOutput(), defaultShowHexOutput()).toBool();
		itsShowOctOutput = settings->value(
			keyNameShowOctOutput(), defaultShowOctOutput()).toBool();
		itsShowBasePrefix = settings->value(
			keyNameShowBasePrefix(), defaultShowBasePrefix()).toBool();
		itsShowLeadingZeroesBin = settings->value(
			keyNameShowLeadingZeroesBin(), defaultShowLeadingZeroesBin()).toBool();
		itsShowLeadingZeroesHex = settings->value(
			keyNameShowLeadingZeroesHex(), defaultShowLeadingZeroesHex()).toBool();
	}
}

void Settings::setDecimalPoint(DecimalPointType newVal) {
	itsDecimalPoint = newVal;
	if (functionArgSeparatorAsChar() == decimalPointAsChar()) {
		itsFunctionArgSeparator = ARG_SEPARATOR_COLON;
	}
}
void Settings::setFunctionArgSeparator(ArgumentSeparatorType newVal) {
	itsFunctionArgSeparator = newVal;
	if (functionArgSeparatorAsChar() == decimalPointAsChar()) {
		itsFunctionArgSeparator = ARG_SEPARATOR_COLON;
	}
}
void Settings::setUseSimpleInputMatching(bool newVal) {
	itsUseSimpleInputMatching = newVal;
}
void Settings::setOutputFormat(OutputFormatType newVal) {
	itsOutputFormat = newVal;
}
void Settings::setOutputDigitGrouping(bool newVal) {
	itsOutputDigitGrouping = newVal;
}
void Settings::setDigitGroupingCharacter(DigitGroupingType newVal) {
	itsDigitGroupingCharacter = newVal;
}
void Settings::setPrecision(int newVal) {
	itsPrecision = newVal;
}
void Settings::setShowSmallNumbersAsZero(bool newVal) {
	itsShowSmallNumbersAsZero = newVal;
}
void Settings::setZeroTresholdExp(int newVal) {
	itsZeroTresholdExp = newVal; 
}
void Settings::setUseEnterToCopy(bool newVal) {
	itsUseEnterToCopy = newVal;
}
void Settings::setShowDecOutput(bool newVal) {
	itsShowDecOutput = newVal;
}
void Settings::setShowBinOutput(bool newVal) {
	itsShowBinOutput = newVal;
}
void Settings::setShowHexOutput(bool newVal) {
	itsShowHexOutput= newVal;
}
void Settings::setShowOctOutput(bool newVal) {
	itsShowOctOutput = newVal;
}
void Settings::setShowBasePrefix(bool newVal) {
	itsShowBasePrefix = newVal;
}
void Settings::setShowLeadingZeroesBin(bool newVal) {
	itsShowLeadingZeroesBin = newVal;
}
void Settings::setShowLeadingZeroesHex(bool newVal) {
	itsShowLeadingZeroesHex = newVal;
}
void Settings::setCalculationBitWidth(CalculationBitWidth newVal) {
	itsCalculationBitWidth = newVal;
}

} // namespace mathy_resurrected
