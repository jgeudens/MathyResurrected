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
#include "math_bridge_globals.h"
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
	itsFlags.itsUseSimpleInputMatching = defaultUseSimpleInputMatching();
	itsOutputFormat = defaultOutputFormat();
	itsFlags.itsOutputDigitGrouping = defaultOutputDigitGrouping();
	itsDigitGroupingCharacter = defaultDigitGroupingCharacter();
	itsPrecision = defaultPrecision();
	itsFlags.itsShowSmallNumbersAsZero = defaultShowSmallNumbersAsZero();
	itsZeroTresholdExp = defaultZeroTresholdExp();
	itsFlags.itsUseEnterToCopy = defaultUseEnterToCopy();
	itsFlags.itsShowDecOutput = defaultShowDecOutput();
	itsFlags.itsShowBinOutput = defaultShowBinOutput();
	itsFlags.itsShowHexOutput = defaultShowHexOutput();
	itsFlags.itsShowOctOutput = defaultShowOctOutput();
	itsFlags.itsShowBasePrefix = defaultShowBasePrefix();
	itsFlags.itsShowLeadingZeroesBin = defaultShowLeadingZeroesBin();
	itsFlags.itsShowLeadingZeroesHex = defaultShowLeadingZeroesHex();
	itsFlags.itsShowLeadingZeroesOct = defaultShowLeadingZeroesOct();
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

		dest->setValue(keyNameUseSimpleInputMatching(), itsFlags.itsUseSimpleInputMatching);
		dest->setValue(keyNameOutputDigitGrouping(), itsFlags.itsOutputDigitGrouping);
		dest->setValue(keyNamePrecision(), itsPrecision);
		dest->setValue(keyNameShowSmallNumbersAsZero(), itsFlags.itsShowSmallNumbersAsZero);
		dest->setValue(keyNameZeroTresholdExp(), itsZeroTresholdExp);
		dest->setValue(keyNameUseEnterToCopy(), itsFlags.itsUseEnterToCopy);
		dest->setValue(keyNameShowDecOutput(), itsFlags.itsShowDecOutput);
		dest->setValue(keyNameShowBinOutput(), itsFlags.itsShowBinOutput);
		dest->setValue(keyNameShowHexOutput(), itsFlags.itsShowHexOutput);
		dest->setValue(keyNameShowOctOutput(), itsFlags.itsShowOctOutput);
		dest->setValue(keyNameShowBasePrefix(), itsFlags.itsShowBasePrefix);
		dest->setValue(keyNameShowLeadingZeroesBin(), itsFlags.itsShowLeadingZeroesBin);
		dest->setValue(keyNameShowLeadingZeroesHex(), itsFlags.itsShowLeadingZeroesHex);
		dest->setValue(keyNameShowLeadingZeroesOct(), itsFlags.itsShowLeadingZeroesOct);
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

		itsFlags.itsUseSimpleInputMatching = settings->value(
			keyNameUseSimpleInputMatching(), defaultUseSimpleInputMatching()).toBool();
		itsFlags.itsOutputDigitGrouping = settings->value(
			keyNameOutputDigitGrouping(), defaultOutputDigitGrouping()).toBool();
		itsPrecision = settings->value(
			keyNamePrecision(), defaultPrecision()).toInt();
		itsFlags.itsShowSmallNumbersAsZero = settings->value(
			keyNameShowSmallNumbersAsZero(), defaultShowSmallNumbersAsZero()).toBool();
		itsZeroTresholdExp = settings->value(
			keyNameZeroTresholdExp(), defaultZeroTresholdExp()).toInt();
		itsFlags.itsUseEnterToCopy = settings->value(
			keyNameUseEnterToCopy(), defaultUseEnterToCopy()).toBool();
		itsFlags.itsShowDecOutput = settings->value(
			keyNameShowDecOutput(), defaultShowDecOutput()).toBool();
		itsFlags.itsShowBinOutput = settings->value(
			keyNameShowBinOutput(), defaultShowBinOutput()).toBool();
		itsFlags.itsShowHexOutput = settings->value(
			keyNameShowHexOutput(), defaultShowHexOutput()).toBool();
		itsFlags.itsShowOctOutput = settings->value(
			keyNameShowOctOutput(), defaultShowOctOutput()).toBool();
		itsFlags.itsShowBasePrefix = settings->value(
			keyNameShowBasePrefix(), defaultShowBasePrefix()).toBool();
		itsFlags.itsShowLeadingZeroesBin = settings->value(
			keyNameShowLeadingZeroesBin(), defaultShowLeadingZeroesBin()).toBool();
		itsFlags.itsShowLeadingZeroesOct = settings->value(
			keyNameShowLeadingZeroesOct(), defaultShowLeadingZeroesOct()).toBool();
		itsFlags.itsShowLeadingZeroesHex = settings->value(
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
	itsFlags.itsUseSimpleInputMatching = newVal;
}
void Settings::setOutputFormat(OutputFormatType newVal) {
	itsOutputFormat = newVal;
}
void Settings::setOutputDigitGrouping(bool newVal) {
	itsFlags.itsOutputDigitGrouping = newVal;
}
void Settings::setDigitGroupingCharacter(DigitGroupingType newVal) {
	itsDigitGroupingCharacter = newVal;
}
void Settings::setPrecision(int newVal) {
	itsPrecision = newVal;
}
void Settings::setShowSmallNumbersAsZero(bool newVal) {
	itsFlags.itsShowSmallNumbersAsZero = newVal;
}
void Settings::setZeroTresholdExp(int newVal) {
	itsZeroTresholdExp = newVal; 
}
void Settings::setUseEnterToCopy(bool newVal) {
	itsFlags.itsUseEnterToCopy = newVal;
}
void Settings::setShowDecOutput(bool newVal) {
	itsFlags.itsShowDecOutput = newVal;
}
void Settings::setShowBinOutput(bool newVal) {
	itsFlags.itsShowBinOutput = newVal;
}
void Settings::setShowHexOutput(bool newVal) {
	itsFlags.itsShowHexOutput= newVal;
}
void Settings::setShowOctOutput(bool newVal) {
	itsFlags.itsShowOctOutput = newVal;
}
void Settings::setShowBasePrefix(bool newVal) {
	itsFlags.itsShowBasePrefix = newVal;
}
void Settings::setShowLeadingZeroesBin(bool newVal) {
	itsFlags.itsShowLeadingZeroesBin = newVal;
}
void Settings::setShowLeadingZeroesHex(bool newVal) {
	itsFlags.itsShowLeadingZeroesHex = newVal;
}
void Settings::setShowLeadingZeroesOct(bool newVal) {
	itsFlags.itsShowLeadingZeroesOct = newVal;
}
void Settings::setCalculationBitWidth(CalculationBitWidth newVal) {
	itsCalculationBitWidth = newVal;
	BridgeAPIGlobals::setBitWidth(newVal);
}

} // namespace mathy_resurrected
