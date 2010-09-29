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

#ifndef MATHY_RESURRECTED_SETTINGS
#define MATHY_RESURRECTED_SETTINGS

#include <QObject>

class QSettings;

namespace mathy_resurrected {

/** Objects that stores all settings for plugin and evaluator.
Can be used to read/write settings from/to QSettings. */
class Settings : public QObject {

	Q_OBJECT

public:
	Settings(QObject* parent = 0);
	virtual ~Settings();

	enum OutputFormatType { 
		AUTOMATIC, SCIENTIFFIC, FIXED 
	};
	enum DecimalPointType { 
		DEC_POINT_COMA, DEC_POINT_DOT, DEC_POINT_SYSTEM 
	};
	enum DigitGroupingType { 
		DIGIT_GROUPING_COMA, DIGIT_GROUPING_DOT, DIGIT_GROUPING_SYSTEM 
	};
	enum ArgumentSeparatorType { 
		ARG_SEPARATOR_COLON, ARG_SEPARATOR_SEMICOLON, ARG_SEPARATOR_COMA 
	};
	// This is bit width for calculations involving bases other than 
	// decimal. Decimal calculations are always preformed using 
	// BridgeAPIGlobals::NUMERIC_PRECISION
	enum CalculationBitWidth {
		BW8 = 8, BW16 = 16, BW32 = 32, BW64 = 64
	};

	static DecimalPointType defaultDecimalPoint() { return DEC_POINT_SYSTEM; }
	static ArgumentSeparatorType defaultFunctionArgSeparator() { return ARG_SEPARATOR_COLON; } // Must never be '.' or ','
	static bool defaultUseSimpleInputMatching() { return false; }
	static OutputFormatType defaultOutputFormat() { return AUTOMATIC; }
	static bool defaultOutputDigitGrouping() { return true; }
	static DigitGroupingType defaultDigitGroupingCharacter() { return DIGIT_GROUPING_SYSTEM; }
	static int defaultPrecision() { return 2; }
	static bool defaultShowSmallNumbersAsZero() { return true; }
	static int defaultZeroTresholdExp() { return -15; }
	static bool defaultUseEnterToCopy() { return true; }
	static bool defaultShowDecOutput() { return true; }
	static bool defaultShowBinOutput() { return false; }
	static bool defaultShowHexOutput() { return true; }
	static bool defaultShowOctOutput() { return false; }
	static bool defaultShowBasePrefix() { return true; }
	static bool defaultShowLeadingZeroesBin() { return true; }
	static bool defaultShowLeadingZeroesHex() { return true; }
	static bool defaultShowLeadingZeroesOct() { return true; }
	static CalculationBitWidth defaultCalculationBitWidth() { return BW16; }

	static QChar systemDecimalPoint();
	static QChar systemDigitGrouping();

	QChar functionArgSeparatorAsChar() const;
	QChar decimalPointAsChar() const;
	QChar digitGroupingCharacterAsChar() const;

	DecimalPointType decimalPoint() const { return itsDecimalPoint; }
	ArgumentSeparatorType functionArgSeparator() const { return itsFunctionArgSeparator; }
	bool useSimpleInputMatching() const { return itsFlags.itsUseSimpleInputMatching; }
	OutputFormatType outputFormat() const { return itsOutputFormat; }
	bool outputDigitGrouping() const { return itsFlags.itsOutputDigitGrouping; }
	DigitGroupingType digitGroupingCharacter() const { return itsDigitGroupingCharacter; }
	int precision() const { return itsPrecision; }
	bool showSmallNumbersAsZero() const { return itsFlags.itsShowSmallNumbersAsZero; }
	int zeroTresholdExp() const { return itsZeroTresholdExp; }
	bool useEnterToCopy() const { return itsFlags.itsUseEnterToCopy; }
	bool showDecOutput() const { return itsFlags.itsShowDecOutput; }
	bool showBinOutput() const { return itsFlags.itsShowBinOutput; }
	bool showHexOutput() const { return itsFlags.itsShowHexOutput; }
	bool showOctOutput() const { return itsFlags.itsShowOctOutput; }
	bool showBasePrefix() const { return itsFlags.itsShowBasePrefix; }
	bool showLeadingZeroesBin() const { return itsFlags.itsShowLeadingZeroesBin; }
	bool showLeadingZeroesHex() const { return itsFlags.itsShowLeadingZeroesHex; }
	bool showLeadingZeroesOct() const { return itsFlags.itsShowLeadingZeroesOct; }
	CalculationBitWidth calculationBitWidth() const { return itsCalculationBitWidth; }

public Q_SLOTS:
	void setDecimalPoint(DecimalPointType newVal);
	void setFunctionArgSeparator(ArgumentSeparatorType newVal);
	void setUseSimpleInputMatching(bool newVal);
	void setOutputFormat(OutputFormatType newVal);
	void setOutputDigitGrouping(bool newVal);
	void setDigitGroupingCharacter(DigitGroupingType newVal);
	void setPrecision(int newVal);
	void setShowSmallNumbersAsZero(bool newVal);
	void setZeroTresholdExp(int newVal);
	void setUseEnterToCopy(bool newVal);
	void setShowDecOutput(bool newVal);
	void setShowBinOutput(bool newVal);
	void setShowHexOutput(bool newVal);
	void setShowOctOutput(bool newVal);
	void setShowBasePrefix(bool newVal);
	void setShowLeadingZeroesBin(bool newVal);
	void setShowLeadingZeroesHex(bool newVal);
	void setShowLeadingZeroesOct(bool newVal);
	void setCalculationBitWidth(CalculationBitWidth newVal);

	void setDefaults();
	void writeSettings(QSettings* dest) const;
	void readSettings(const QSettings* settings);

private:
	DecimalPointType itsDecimalPoint;
	ArgumentSeparatorType itsFunctionArgSeparator;
	OutputFormatType itsOutputFormat;
	DigitGroupingType itsDigitGroupingCharacter;
	int itsPrecision;
	int itsZeroTresholdExp;
	CalculationBitWidth itsCalculationBitWidth;

	struct Flags {
		bool itsUseSimpleInputMatching : 1;
		bool itsOutputDigitGrouping : 1;
		bool itsShowSmallNumbersAsZero : 1;
		bool itsUseEnterToCopy : 1;
		bool itsShowDecOutput : 1;
		bool itsShowBinOutput : 1;
		bool itsShowHexOutput : 1;
		bool itsShowOctOutput : 1;
		bool itsShowBasePrefix : 1;
		bool itsShowLeadingZeroesBin : 1;
		bool itsShowLeadingZeroesHex : 1;
		bool itsShowLeadingZeroesOct : 1;
	};
	Flags itsFlags;

	static QString keyNameDecimalPoint() {return QString("MathyResurrected/DecimalPoint"); }
	static QString keyNameFunctionArgSeparator() {return QString("MathyResurrected/ArgSeparator"); }
	static QString keyNameUseSimpleInputMatching() {return QString("MathyResurrected/SimpleInputMatching"); }
	static QString keyNameOutputFormat() {return QString("MathyResurrected/OutputFormat"); }
	static QString keyNameOutputDigitGrouping() {return QString("MathyResurrected/ShowDigitGroupChar"); }
	static QString keyNameDigitGroupingCharacter() {return QString("MathyResurrected/ThousandSeparator"); }
	static QString keyNamePrecision() {return QString("MathyResurrected/Precision"); }
	static QString keyNameShowSmallNumbersAsZero() {return QString("MathyResurrected/ShouldUseZeroTreshold"); }
	static QString keyNameZeroTresholdExp() {return QString("MathyResurrected/ZeroTresholdExponent"); }
	static QString keyNameUseEnterToCopy() {return QString("MathyResurrected/CopyToClipboardWithEnterKey"); }
	static QString keyNameShowDecOutput() {return QString("MathyResurrected/OutputDecimal"); }
	static QString keyNameShowBinOutput() {return QString("MathyResurrected/OutputBinary"); }
	static QString keyNameShowHexOutput() {return QString("MathyResurrected/OutputHexadecimal"); }
	static QString keyNameShowOctOutput() {return QString("MathyResurrected/OutputOctal"); }
	static QString keyNameShowBasePrefix() {return QString("MathyResurrected/OutputBaseShowPrefix"); }
	static QString keyNameShowLeadingZeroesBin() {return QString("MathyResurrected/ShowLeadingZeroesBin"); }
	static QString keyNameShowLeadingZeroesHex() {return QString("MathyResurrected/ShowLeadingZeroesHex"); }
	static QString keyNameShowLeadingZeroesOct() {return QString("MathyResurrected/ShowLeadingZeroesOct"); }
	static QString keyNameCalculationBitWidth() {return QString("MathyResurrected/BitWidth"); }
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_SETTINGS
