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

#ifndef MATHY_RESURRECTED_GUI_OPTIONS
#define MATHY_RESURRECTED_GUI_OPTIONS

#include <QFrame>
#include <QSettings>
#include <QLocale>
#include "ui_OptionsWidget.h"

namespace mathy_resurrected {

class MathyResurrectedOptionsDialog : public QFrame, private Ui::MathyResurrectedOptions {

	Q_OBJECT

private slots:
	void on_radioButtonDecSepSystem_clicked();
	void on_radioButtonDecSepComa_clicked();
	void on_radioButtonDecSepDot_clicked();
	void on_radioButtonArgSeparatorColon_clicked() { itsArgSeparator = ':'; }
	void on_radioButtonArgSeparatorSemiColon_clicked() { itsArgSeparator = ';'; }
	void on_radioButtonArgSeparatorComa_clicked();
	void on_checkBoxInputMatching_clicked(bool flag) { itsSimpleInputFlag = flag; }
	void on_radioButtonOutputDefault_clicked() { itsOutputFormat = 'd'; }
	void on_radioButtonOutputScientiffic_clicked() { itsOutputFormat = 's'; }
	void on_radioButtonOutputFixed_clicked() { itsOutputFormat = 'f'; }
	void on_checkBoxShowGrouping_clicked(bool flag) { itsShowDigitGrouping = flag;}
	void on_radioButtonThSepSys_clicked() { itsThousandsSepTag = "sys"; }
	void on_radioButtonThSepCom_clicked() { itsThousandsSepTag = "com"; }
	void on_radioButtonThSepDot_clicked() { itsThousandsSepTag = "dot"; }
	void on_spinBoxOutputPrecision_valueChanged(int prec) { itsPrecision = prec;}
	void on_checkBoxZeroTreshold_clicked(bool flag) { itsZeroTresholdFlag = flag; }
	void on_spinBoxZeroTreshold_valueChanged(int treshold) { itsZeroTresholdExp = treshold; }
	void on_checkBoxUseEnterKey_clicked(bool flag) { itsUseEnterKey = flag;}
	void on_checkBoxBinOut_clicked(bool flag);
	void on_checkBoxOctOut_clicked(bool flag);
	void on_checkBoxDecOut_clicked(bool flag);
	void on_checkBoxHexOut_clicked(bool flag);
	void on_radioButtonBW8_clicked() { itsBWidth = 8; } 
	void on_radioButtonBW16_clicked() { itsBWidth = 16; } 
	void on_radioButtonBW32_clicked() { itsBWidth = 32; } 
	void on_radioButtonBW64_clicked() { itsBWidth = 64; } 
	void on_checkBoxShowBasePrefix_clicked(bool flag) { itsShowBasePrefix = flag; }
	void on_pushButtonSetDefaults_clicked();
	void on_checkBoxShowLeadingZerosHex_clicked(bool flag) { itsShowLeadZeroesHex = flag; }
	void on_checkBoxShowLeadingZerosBin_clicked(bool flag) { itsShowLeadZeroesBin = flag; }

public:
	MathyResurrectedOptionsDialog(QWidget* parent = 0);
	~MathyResurrectedOptionsDialog();

	static QString keyNameArgSeparator() { return QString("MathyResurrected/ArgSeparator"); }
	static QString keyNameSimpleInputMatching() { return QString("MathyResurrected/SimpleInputMatching"); }
	static QString keyNameOutputFormat() { return QString("MathyResurrected/OutputFormat"); }
	static QString keyNamePrecision() { return QString("MathyResurrected/Precision"); }
	static QString keyNameUseEnterKey() { return QString("MathyResurrected/CopyToClipboardWithEnterKey"); }
	static QString keyNameShowDigitGrouping() { return QString("MathyResurrected/ShowDigitGroupChar"); }
	static QString keyNameShouldUseZeroTreshold() { return QString("MathyResurrected/ShouldUseZeroTreshold"); }
	static QString keyNameZeroTresholdExp() { return QString("MathyResurrected/ZeroTresholdExponent"); }
	static QString keyNameDecimalPoint() { return QString("MathyResurrected/DecimalPoint"); }
	static QString keyNameGroupingChar() { return QString("MathyResurrected/ThousandSeparator"); }
	static QString keyNameOutputShowDec() { return QString("MathyResurrected/OutputDecimal"); }
	static QString keyNameOutputShowBin() { return QString("MathyResurrected/OutputHexadecimal"); }
	static QString keyNameOutputShowHex() { return QString("MathyResurrected/OutputOctal"); }
	static QString keyNameOutputShowOct() { return QString("MathyResurrected/OutputBinary"); }
	static QString keyNameShowBasePrefix() { return QString("MathyResurrected/OutputBaseShowPrefix"); }
	static QString keyNameBitWidth() { return QString("MathyResurrected/BitWidth"); }
	static QString keyNameShowLeadingZeroesHex() { return QString("MathyResurrected/ShowLeadingZeroesHex"); }
	static QString keyNameShowLeadingZeroesBin() { return QString("MathyResurrected/ShowLeadingZeroesBin"); }
	
	void writeSettings();

	static bool defaultUseEnterKey() { return true; }
	static bool defaultSimpleInputMatching() { return false; }
	static QChar decPointTag2Char(const QString& tag);
	static QChar digitGroupTag2Char (const QString& tag);
	static QString systemDecPointTag() { return QString("sys"); }
	static QString systemGroupingCharTag() { return QString("sys"); }
	static bool defaultOutputShowDec() { return true; }
	static bool defaultOutputShowBin() { return false; }
	static bool defaultOutputShowHex() { return false; }
	static bool defaultOutputShowOct() { return false; }
	static bool defaultShowBasePrefix() { return true; }

private:
	QChar itsArgSeparator;
	QChar itsOutputFormat;
	int itsPrecision;
	bool itsSimpleInputFlag;
	bool itsShowDigitGrouping;
	bool itsUseEnterKey;
	bool itsZeroTresholdFlag;
	int itsZeroTresholdExp;
	QString itsDecPointTag;
	QString itsThousandsSepTag;
	bool itsShowDec;
	bool itsShowBin;
	bool itsShowHex;
	bool itsShowOct;
	bool itsShowBasePrefix;
	unsigned char itsBWidth;
	bool itsShowLeadZeroesHex;
	bool itsShowLeadZeroesBin;
	
	void setupUiByAppSettings();
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_GUI_OPTIONS
