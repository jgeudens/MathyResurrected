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

#include <exception>
#include "MathEvaluator.h"
#include "MathyResurrectedOptionsDialog.h"
#include "MathyResurrectedPlugin.h"

namespace mathy_resurrected {

QChar MathyResurrectedOptionsDialog::decPointTag2Char(const QString& tag) {
	QChar retv;

	if (tag == "sys") {
		retv = MathEvaluator::systemDecimalPoint();
	} else if (tag == "dot") {
		retv = QChar('.');
	} else if (tag == "com") {
		retv = QChar(',');
	} else {
		retv = MathEvaluator::systemDecimalPoint();
	}
	return retv;
}

QChar MathyResurrectedOptionsDialog::digitGroupTag2Char (const QString& tag) {
	QChar retv;

	if (tag == "sys") {
		retv = MathEvaluator::systemThousandSep();
	} else if (tag == "dot") {
		retv = QChar('.');
	} else if (tag == "com") {
		retv = QChar(',');
	} else {
		retv = MathEvaluator::systemThousandSep();
	}
	return retv;
}

void MathyResurrectedOptionsDialog::on_radioButtonArgSeparatorComa_clicked() {
	if (decPointTag2Char(itsDecPointTag) == ',') {
		on_radioButtonArgSeparatorColon_clicked();
	} else {
		itsArgSeparator = ','; 
	}
}

void MathyResurrectedOptionsDialog::on_radioButtonDecSepSystem_clicked() { 
	itsDecPointTag = "sys";
	if (MathEvaluator::systemDecimalPoint() == itsArgSeparator) {
		on_radioButtonArgSeparatorColon_clicked();
		radioButtonArgSeparatorColon->setChecked(true);
	}
	if (MathEvaluator::systemDecimalPoint() == ',') {
		radioButtonArgSeparatorComa->setEnabled(false);
	}
}

void MathyResurrectedOptionsDialog::on_radioButtonDecSepComa_clicked() { 
	itsDecPointTag = "com";
	if (itsArgSeparator == ',') {
		on_radioButtonArgSeparatorColon_clicked();
		radioButtonArgSeparatorColon->setChecked(true);
	}
	radioButtonArgSeparatorComa->setEnabled(false);
}

void MathyResurrectedOptionsDialog::on_radioButtonDecSepDot_clicked() { 
	itsDecPointTag = "dot";
	radioButtonArgSeparatorComa->setEnabled(true);
}

void MathyResurrectedOptionsDialog::on_checkBoxDecOut_clicked(bool flag) { 
	itsShowDec = flag; 
}

void MathyResurrectedOptionsDialog::on_checkBoxHexOut_clicked(bool flag) { 
	itsShowHex = flag; 
	groupBoxBW->setEnabled(itsShowBin || itsShowHex || itsShowOct);
}

void MathyResurrectedOptionsDialog::on_checkBoxOctOut_clicked(bool flag) { 
	itsShowOct = flag; 
	groupBoxBW->setEnabled(itsShowBin || itsShowHex || itsShowOct);
}

void MathyResurrectedOptionsDialog::on_checkBoxBinOut_clicked(bool flag) { 
	itsShowBin = flag; 
	groupBoxBW->setEnabled(itsShowBin || itsShowHex || itsShowOct);
}

void MathyResurrectedOptionsDialog::on_pushButtonSetDefaults_clicked()  {
	itsArgSeparator = MathEvaluator::defaultArgSeparator();
	itsOutputFormat = MathEvaluator::defaultOutputFormat();
	itsPrecision = MathEvaluator::defaultOutputPrecision();
	
	itsSimpleInputFlag = defaultSimpleInputMatching();
	itsShowDigitGrouping = MathEvaluator::defaultShowDigitGrouping();
	itsUseEnterKey = defaultUseEnterKey();
	itsZeroTresholdExp = MathEvaluator::defaultZeroTresholdExp();
	itsZeroTresholdFlag = MathEvaluator::defaultShouldUseZeroTreshold();
	itsDecPointTag = MathEvaluator::defaultDecimalPointTag();
	itsThousandsSepTag = MathEvaluator::defaultGroupingCharTag();

	itsShowDec = defaultOutputShowDec();
	itsShowBin = defaultOutputShowBin();
	itsShowHex = defaultOutputShowHex();
	itsShowOct = defaultOutputShowOct();
	itsShowBasePrefix = defaultShowBasePrefix();

	itsBWidth = MathEvaluator::defaultBitWidth();
	
	setupUiByAppSettings();
}

void MathyResurrectedOptionsDialog::setupUiByAppSettings() {
	if (decPointTag2Char(itsDecPointTag) == ',') {
		radioButtonArgSeparatorComa->setDisabled(true);
		if (itsArgSeparator == ',') {
			itsArgSeparator = MathEvaluator::defaultArgSeparator();
		}
	} else {
		radioButtonArgSeparatorComa->setEnabled(true);
	}

	if (itsThousandsSepTag == "sys") {
		radioButtonThSepSys->setChecked(true);
	} else if (itsThousandsSepTag == "com") {
		radioButtonThSepCom->setChecked(true);
	} else if (itsThousandsSepTag == "dot") {
		radioButtonThSepDot->setChecked(true);
	}

	if (itsDecPointTag == "sys") {
		radioButtonDecSepSystem->setChecked(true);
	} else if (itsDecPointTag == "com") {
		radioButtonDecSepComa->setChecked(true);
	} else if (itsDecPointTag == "dot") {
		radioButtonDecSepDot->setChecked(true);
	}

	if (itsArgSeparator == ':') {
		radioButtonArgSeparatorColon->setChecked(true);
	} else if (itsArgSeparator == ';') {
		radioButtonArgSeparatorSemiColon->setChecked(true);
	} else if (itsArgSeparator == ',') {
		radioButtonArgSeparatorComa->setChecked(true);
	}

	checkBoxInputMatching->setChecked(itsSimpleInputFlag);
	checkBoxShowGrouping->setChecked(itsShowDigitGrouping);
	checkBoxUseEnterKey->setChecked(itsUseEnterKey);
	
	if (itsOutputFormat == 'd') {
		radioButtonoutputDefault->setChecked(true);
	} else if (itsOutputFormat == 'f') {
		radioButtonOutputFixed->setChecked(true);
	} else if (itsOutputFormat == 's') {
		radioButtonoutputScientiffic->setChecked(true);
	}

	spinBoxOutputPrecision->setValue(itsPrecision);

	checkBoxZeroTreshold->setChecked(itsZeroTresholdFlag);
	spinBoxZeroTreshold->setValue(itsZeroTresholdExp);

	checkBoxBinOut->setChecked(itsShowBin);
	checkBoxDecOut->setChecked(itsShowDec);
	checkBoxHexOut->setChecked(itsShowHex);
	checkBoxOctOut->setChecked(itsShowOct);
	checkBoxShowBasePrefix->setChecked(itsShowBasePrefix);

	if (itsBWidth == 8) {
		radioButtonBW8->setChecked(true);
	} else if (itsBWidth == 16) {
		radioButtonBW16->setChecked(true);
	} else if (itsBWidth == 32) {
		radioButtonBW32->setChecked(true);
	} else if (itsBWidth == 64) {
		radioButtonBW64->setChecked(true);
	} 

	groupBoxBW->setEnabled(itsShowBin || itsShowHex || itsShowOct);
}

MathyResurrectedOptionsDialog::MathyResurrectedOptionsDialog(QWidget* parent) : 
	QFrame(parent) 
{
	QSettings* app_settings = *gmathyresurrectedInstance->settings;

	itsArgSeparator = app_settings->value(
		keyNameArgSeparator(), MathEvaluator::defaultArgSeparator()).toChar();
	itsOutputFormat = app_settings->value(
		keyNameOutputFormat(), MathEvaluator::defaultOutputFormat()).toChar();
	itsPrecision = app_settings->value(
		keyNamePrecision(), MathEvaluator::defaultOutputPrecision()).toInt();	
	itsSimpleInputFlag = app_settings->value(
		keyNameSimpleInputMatching(), defaultSimpleInputMatching()).toBool();

	itsUseEnterKey = app_settings->value(
		keyNameUseEnterKey(), defaultUseEnterKey()).toBool();
	itsShowDigitGrouping = app_settings->value(
		keyNameShowDigitGrouping(), MathEvaluator::defaultShowDigitGrouping()
		).toBool();
	itsZeroTresholdExp = app_settings->value(
		keyNameZeroTresholdExp(), MathEvaluator::defaultZeroTresholdExp()
		).toInt();
	itsZeroTresholdFlag = app_settings->value(
		keyNameShouldUseZeroTreshold(), MathEvaluator::defaultShouldUseZeroTreshold()
		).toBool();
	itsDecPointTag = app_settings->value(
		keyNameDecimalPoint(), MathEvaluator::defaultDecimalPointTag()
		).toString();
	itsThousandsSepTag = app_settings->value(
		keyNameGroupingChar(), MathEvaluator::defaultGroupingCharTag()
		).toString();

	itsShowDec = app_settings->value(
		keyNameOutputShowDec(), defaultOutputShowDec()).toBool();
	itsShowBin = app_settings->value(
		keyNameOutputShowBin(), defaultOutputShowBin()).toBool();
	itsShowHex = app_settings->value(
		keyNameOutputShowHex(), defaultOutputShowHex()).toBool();
	itsShowOct = app_settings->value(
		keyNameOutputShowOct(), defaultOutputShowOct()).toBool();
	itsShowBasePrefix = app_settings->value(
		keyNameShowBasePrefix(), defaultShowBasePrefix()).toBool();

	itsBWidth = app_settings->value(
		keyNameBitWidth(), MathEvaluator::defaultBitWidth()).toInt();

	setupUiByAppSettings();
}

MathyResurrectedOptionsDialog::~MathyResurrectedOptionsDialog() { 
	this->hide(); 
}

void MathyResurrectedOptionsDialog::writeSettings() {
	QSettings* app_settings = *gmathyresurrectedInstance->settings;

	app_settings->beginGroup("MathyResurrected");
	app_settings->remove("");
	app_settings->endGroup();

	app_settings->setValue(keyNameArgSeparator(), itsArgSeparator);
	app_settings->setValue(keyNameOutputFormat(), itsOutputFormat);
	app_settings->setValue(keyNamePrecision(), itsPrecision);
	app_settings->setValue(keyNameSimpleInputMatching(), itsSimpleInputFlag);
	app_settings->setValue(keyNameUseEnterKey(), itsUseEnterKey);
	app_settings->setValue(keyNameShowDigitGrouping(), itsShowDigitGrouping);
	app_settings->setValue(keyNameZeroTresholdExp(), itsZeroTresholdExp);
	app_settings->setValue(keyNameShouldUseZeroTreshold(), itsZeroTresholdFlag);
	app_settings->setValue(keyNameDecimalPoint(), itsDecPointTag);
	app_settings->setValue(keyNameGroupingChar(), itsThousandsSepTag);
	app_settings->setValue(keyNameOutputShowDec(), itsShowDec);
	app_settings->setValue(keyNameOutputShowBin(), itsShowBin);
	app_settings->setValue(keyNameOutputShowHex(), itsShowHex);
	app_settings->setValue(keyNameOutputShowOct(), itsShowOct);
	app_settings->setValue(keyNameShowBasePrefix(), itsShowBasePrefix);
	app_settings->setValue(keyNameBitWidth(), itsBWidth);
}

} // namespace mathy_resurrected
