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

#include "OptionsDialog.h"
#include "Settings.h"

using namespace std;

namespace mathy_resurrected {

void OptionsDialog::setSettingsObject(Settings* settings) {
	itsSettings = settings;
	setupUiBySettings();
}

void OptionsDialog::on_radioButtonDecSepSystem_clicked() { 
	itsSettings->setDecimalPoint(Settings::DEC_POINT_SYSTEM);
	setupUiBySettings();	
}
void OptionsDialog::on_radioButtonDecSepComa_clicked() { 
	itsSettings->setDecimalPoint(Settings::DEC_POINT_COMA);
	setupUiBySettings();	
}
void OptionsDialog::on_radioButtonDecSepDot_clicked() { 
	itsSettings->setDecimalPoint(Settings::DEC_POINT_DOT);
	setupUiBySettings();	
}

void OptionsDialog::on_radioButtonArgSeparatorComa_clicked() {
	itsSettings->setFunctionArgSeparator(Settings::ARG_SEPARATOR_COMA);
	setupUiBySettings();
}
void OptionsDialog::on_radioButtonArgSeparatorColon_clicked() { 
	itsSettings->setFunctionArgSeparator(Settings::ARG_SEPARATOR_COLON);
	setupUiBySettings();
}
void OptionsDialog::on_radioButtonArgSeparatorSemiColon_clicked(){ 
	itsSettings->setFunctionArgSeparator(Settings::ARG_SEPARATOR_SEMICOLON);
	setupUiBySettings();
}

void OptionsDialog::on_checkBoxInputMatching_clicked(bool flag) { 
	itsSettings->setUseSimpleInputMatching(flag);
}

void OptionsDialog::on_radioButtonOutputDefault_clicked() { 
	itsSettings->setOutputFormat(Settings::AUTOMATIC);
}
void OptionsDialog::on_radioButtonOutputScientiffic_clicked() { 
	itsSettings->setOutputFormat(Settings::SCIENTIFFIC);
}
void OptionsDialog::on_radioButtonOutputFixed_clicked() { 
	itsSettings->setOutputFormat(Settings::FIXED);
}

void OptionsDialog::on_checkBoxShowGrouping_clicked(bool flag) {
	itsSettings->setOutputDigitGrouping(flag);
}

void OptionsDialog::on_radioButtonThSepSys_clicked() {
	itsSettings->setDigitGroupingCharacter(Settings::DIGIT_GROUPING_SYSTEM);
}

void OptionsDialog::on_radioButtonThSepCom_clicked() {
	itsSettings->setDigitGroupingCharacter(Settings::DIGIT_GROUPING_COMA);
}

void OptionsDialog::on_radioButtonThSepDot_clicked()  {
	itsSettings->setDigitGroupingCharacter(Settings::DIGIT_GROUPING_DOT);
}

void OptionsDialog::on_spinBoxOutputPrecision_valueChanged(int prec) { 
	itsSettings->setPrecision(prec);
}

void OptionsDialog::on_checkBoxZeroTreshold_clicked(bool flag) { 
	itsSettings->setShowSmallNumbersAsZero(flag);
}

void OptionsDialog::on_spinBoxZeroTreshold_valueChanged(int treshold) { 
	itsSettings->setZeroTresholdExp(treshold);
}

void OptionsDialog::on_checkBoxUseEnterKey_clicked(bool flag) { 
	itsSettings->setUseEnterToCopy(flag);
}

void OptionsDialog::on_checkBoxDecOut_clicked(bool flag) { 
	itsSettings->setShowDecOutput(flag);
}

void OptionsDialog::setNumberBaseOptionsEnabledState() {
	bool showOtherBases = itsSettings == 0 ? true :
		itsSettings->showBinOutput() ||
		itsSettings->showHexOutput() ||
		itsSettings->showOctOutput();
	groupBoxBW->setEnabled(showOtherBases);
	checkBoxShowBasePrefix->setEnabled(showOtherBases);
	checkBoxShowLeadingZerosOct->setEnabled(showOtherBases);
	checkBoxShowLeadingZerosHex->setEnabled(showOtherBases);
	checkBoxShowLeadingZerosBin->setEnabled(showOtherBases);
}

void OptionsDialog::on_checkBoxHexOut_clicked(bool flag) { 
	itsSettings->setShowHexOutput(flag);
	setNumberBaseOptionsEnabledState();
}

void OptionsDialog::on_checkBoxBinOut_clicked(bool flag) { 
	itsSettings->setShowBinOutput(flag);
	setNumberBaseOptionsEnabledState();
}

void OptionsDialog::on_checkBoxOctOut_clicked(bool flag) { 
	itsSettings->setShowOctOutput(flag);
	setNumberBaseOptionsEnabledState();
}

void OptionsDialog::on_radioButtonBW8_clicked() { 
	itsSettings->setCalculationBitWidth(Settings::BW8);
}

void OptionsDialog::on_radioButtonBW16_clicked() { 
	itsSettings->setCalculationBitWidth(Settings::BW16);
}

void OptionsDialog::on_radioButtonBW32_clicked() { 
	itsSettings->setCalculationBitWidth(Settings::BW32);
}

void OptionsDialog::on_radioButtonBW64_clicked() { 
	itsSettings->setCalculationBitWidth(Settings::BW64);
}

void OptionsDialog::on_checkBoxShowBasePrefix_clicked(bool flag) { 
	itsSettings->setShowBasePrefix(flag);
}

void OptionsDialog::on_pushButtonSetDefaults_clicked()  {
	itsSettings->setDefaults();
	setupUiBySettings();
}

void OptionsDialog::on_checkBoxShowLeadingZerosHex_clicked(bool flag) { 
	itsSettings->setShowLeadingZeroesHex(flag);
}

void OptionsDialog::on_checkBoxShowLeadingZerosBin_clicked(bool flag) { 
	itsSettings->setShowLeadingZeroesBin(flag);
}

OptionsDialog::OptionsDialog(QWidget* parent, Settings* settings) : 
	QFrame(parent), itsSettings(settings)
{
	setupUi(this);
	setupUiBySettings();
}

OptionsDialog::~OptionsDialog() { 
	this->hide(); 
}

void OptionsDialog::setupUiBySettings() {
	if (itsSettings != 0) {
		setEnabled(true);
		switch (itsSettings->decimalPoint()) {
			case Settings::DEC_POINT_COMA:
				radioButtonDecSepComa->setChecked(true);
				radioButtonArgSeparatorComa->setEnabled(false);
				break;
			case Settings::DEC_POINT_DOT:
				radioButtonDecSepDot->setChecked(true);
				radioButtonArgSeparatorComa->setEnabled(true);
				break;
			case Settings::DEC_POINT_SYSTEM:
			default:
				radioButtonDecSepSystem->setChecked(true);
				if (Settings::systemDecimalPoint() == ',') {
					radioButtonArgSeparatorComa->setEnabled(false);
				} else {
					radioButtonArgSeparatorComa->setEnabled(true);
				}
				break;
		}

		switch (itsSettings->functionArgSeparator()) {
			case Settings::ARG_SEPARATOR_SEMICOLON:
				radioButtonArgSeparatorSemiColon->setChecked(true);
				break;
			case Settings::ARG_SEPARATOR_COMA:
				// Note that this case will never happen if decimal point 
				// in settings is ','; Settings object ensures that.
				radioButtonArgSeparatorComa->setChecked(true);
				break;
			case Settings::ARG_SEPARATOR_COLON:
			default:
				radioButtonArgSeparatorColon->setChecked(true);
		}

		checkBoxInputMatching->setChecked(itsSettings->useSimpleInputMatching());

		switch (itsSettings->outputFormat()) {
			case Settings::AUTOMATIC:
				radioButtonOutputDefault->setChecked(true);
				break;
			case Settings::SCIENTIFFIC:
				radioButtonOutputScientiffic->setChecked(true);
				break;
			case Settings::FIXED:
			default:
				radioButtonOutputFixed->setChecked(true);
		}

		checkBoxShowGrouping->setChecked(itsSettings->outputDigitGrouping());

		switch (itsSettings->digitGroupingCharacter()) {
			case Settings::DIGIT_GROUPING_SYSTEM:
				radioButtonThSepSys->setChecked(true);
				break;
			case Settings::DIGIT_GROUPING_COMA:
				radioButtonThSepCom->setChecked(true);
				break;
			case Settings::DIGIT_GROUPING_DOT:
			default:
				radioButtonThSepDot->setChecked(true);
		}

		spinBoxOutputPrecision->setValue(itsSettings->precision());

		checkBoxZeroTreshold->setChecked(itsSettings->showSmallNumbersAsZero());
		spinBoxZeroTreshold->setValue(itsSettings->zeroTresholdExp());
		checkBoxUseEnterKey->setChecked(itsSettings->useEnterToCopy());

		checkBoxBinOut->setChecked(itsSettings->showBinOutput());
		checkBoxDecOut->setChecked(itsSettings->showDecOutput());
		checkBoxHexOut->setChecked(itsSettings->showHexOutput());
		checkBoxOctOut->setChecked(itsSettings->showOctOutput());

		checkBoxShowBasePrefix->setChecked(itsSettings->showBasePrefix());

		checkBoxShowLeadingZerosHex->setChecked(itsSettings->showLeadingZeroesHex());
		checkBoxShowLeadingZerosOct->setChecked(itsSettings->showLeadingZeroesOct());
		checkBoxShowLeadingZerosBin->setChecked(itsSettings->showLeadingZeroesBin());

		setNumberBaseOptionsEnabledState();

		switch (itsSettings->calculationBitWidth()) {
			case Settings::BW64:
				radioButtonBW64->setChecked(true);
				break;
			case Settings::BW32:
				radioButtonBW32->setChecked(true);
				break;
			case Settings::BW16:
				radioButtonBW16->setChecked(true);
				break;
			case Settings::BW8:
			default:
				radioButtonBW8->setChecked(true);
				break;
		}
	} else {
		setDisabled(true);
	}
}

} // namespace mathy_resurrected
