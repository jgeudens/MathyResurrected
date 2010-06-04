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

void MathyResurrectedOptionsDialog::connectAll() {
	connect(radioButton_ArgSeparatorColon, 
		SIGNAL(clicked(bool)), this, SLOT(setFunArgSeparatorColon(void)));
	connect(radioButton_ArgSeparatorSemiColon, 
		SIGNAL(clicked(bool)), this, SLOT(setFunArgSeparatorSemicolon(void)));
	connect(radioButton_ArgSeparatorComa, 
		SIGNAL(clicked(bool)), this, SLOT(setFunArgSeparatorComa(void)));

	connect(checkBox_InputMatching, 
		SIGNAL(toggled(bool)), this, SLOT(setSimpleInputMatching(bool)));

	connect(checkBox_ShowGrouping, 
		SIGNAL(toggled(bool)), this, SLOT(setShowDigitGrouping(bool)));
	connect(checkBox_UseEnterKey, 
		SIGNAL(toggled(bool)), this, SLOT(setUseEnterKey(bool)));
	
	connect(radioButton_outputDefault, 
		SIGNAL(clicked(bool)), this, SLOT(setOutputFormatDefault(void)));
	connect(radioButton_outputScientiffic, 
		SIGNAL(clicked(bool)), this, SLOT(setOutputFormatScientiffic(void)));
	connect(radioButton_OutputFixed, 
		SIGNAL(clicked(bool)), this, SLOT(setOutputFormatFixed(void)));

	connect(spinBox_OutputPrecision, 
		SIGNAL(valueChanged(int)), this, SLOT(setPrecision(int)));

	connect(checkBox_ZeroTreshold, 
		SIGNAL(toggled(bool)), this, SLOT(setShouldUseZeroTreshold(bool)));
	connect(spinBox_zeroTreshold, 
		SIGNAL(valueChanged(int)), this, SLOT(setZeroTresholdExp(int)));

	connect(pushButton_setDefaults, 
		SIGNAL(clicked(bool)), this, SLOT(setAllDefaults(void)));
}

void MathyResurrectedOptionsDialog::setAllDefaults()  {
	itsArgSeparator = MathEvaluator::defaultArgSeparator();
	itsOutputFormat = MathEvaluator::defaultOutputFormat();
	itsPrecision = MathEvaluator::defaultOutputPrecision();
	
	itsSimpleInputFlag = defaultSimpleInputMatching();
	itsShowDigitGrouping = MathEvaluator::defaultShowDigitGrouping();
	itsUseEnterKey = defaultUseEnterKey();
	itsZeroTresholdExp = MathEvaluator::defaultZeroTresholdExp();
	itsZeroTresholdFlag = MathEvaluator::defaultShouldUseZeroTreshold();
	
	setupUiByAppSettings();
}

void MathyResurrectedOptionsDialog::setupUiByAppSettings() {
	if (MathEvaluator::systemDecimalPoint() == ',') {
		radioButton_ArgSeparatorComa->setDisabled(true);
		if (itsArgSeparator == ',') {
			itsArgSeparator = MathEvaluator::defaultArgSeparator();
			writeSettings();
		}
	} else {
		radioButton_ArgSeparatorComa->setEnabled(true);
	}

	if (itsArgSeparator == ':') {
		radioButton_ArgSeparatorColon->setChecked(true);
	} else if (itsArgSeparator == ';') {
		radioButton_ArgSeparatorSemiColon->setChecked(true);
	} else if (itsArgSeparator == ',') {
		radioButton_ArgSeparatorComa->setChecked(true);
	}

	checkBox_InputMatching->setChecked(itsSimpleInputFlag);
	checkBox_ShowGrouping->setChecked(itsShowDigitGrouping);
	checkBox_UseEnterKey->setChecked(itsUseEnterKey);
	
	if (itsOutputFormat == 'd') {
		radioButton_outputDefault->setChecked(true);
	} else if (itsOutputFormat == 'f') {
		radioButton_OutputFixed->setChecked(true);
	} else if (itsOutputFormat == 's') {
		radioButton_outputScientiffic->setChecked(true);
	}

	spinBox_OutputPrecision->setValue(itsPrecision);

	checkBox_ZeroTreshold->setChecked(itsZeroTresholdFlag);
	spinBox_zeroTreshold->setValue(itsZeroTresholdExp);
}

MathyResurrectedOptionsDialog::MathyResurrectedOptionsDialog(QWidget* parent) : 
	QFrame(parent) 
{
	setupUi(this);

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

	setupUiByAppSettings();
	connectAll();
}

MathyResurrectedOptionsDialog::~MathyResurrectedOptionsDialog() { 
	this->hide(); 
}

void MathyResurrectedOptionsDialog::writeSettings() {
	QSettings* app_settings = *gmathyresurrectedInstance->settings;

	app_settings->setValue(keyNameArgSeparator(), itsArgSeparator);
	app_settings->setValue(keyNameOutputFormat(), itsOutputFormat);
	app_settings->setValue(keyNamePrecision(), itsPrecision);
	app_settings->setValue(keyNameSimpleInputMatching(), itsSimpleInputFlag);
	app_settings->setValue(keyNameUseEnterKey(), itsUseEnterKey);
	app_settings->setValue(keyNameShowDigitGrouping(), itsShowDigitGrouping);
	app_settings->setValue(keyNameZeroTresholdExp(), itsZeroTresholdExp);
	app_settings->setValue(keyNameShouldUseZeroTreshold(), itsZeroTresholdFlag);
}

} // namespace mathy_resurrected
