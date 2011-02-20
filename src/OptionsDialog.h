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
#include "ui_OptionsWidget.h"

namespace mathy_resurrected {

class Settings;

class OptionsDialog : public QFrame, private Ui::MathyResurrectedOptions {

	Q_OBJECT

public:
	/**
	@param [in] settings - Settings object that is used as container
	for dialog settings. Dialog doesn't own this object, it only displays 
	it and manipulates it according to user actions. */
	OptionsDialog(QWidget* parent = 0, Settings* settings = 0);
	virtual ~OptionsDialog();

public Q_SLOTS: 
	void setSettingsObject(Settings* settings);

private Q_SLOTS:
	void on_radioButtonDecSepSystem_clicked();
	void on_radioButtonDecSepComa_clicked();
	void on_radioButtonDecSepDot_clicked();
	void on_radioButtonArgSeparatorColon_clicked();
	void on_radioButtonArgSeparatorSemiColon_clicked();
	void on_radioButtonArgSeparatorComa_clicked();
	void on_checkBoxInputMatching_clicked(bool flag);
	void on_radioButtonOutputDefault_clicked();
	void on_radioButtonOutputScientiffic_clicked();
	void on_radioButtonOutputFixed_clicked();
	void on_checkBoxShowGrouping_clicked(bool flag);
	void on_radioButtonThSepSys_clicked();
	void on_radioButtonThSepCom_clicked();
	void on_radioButtonThSepDot_clicked();
	void on_spinBoxOutputPrecision_valueChanged(int prec);
	void on_checkBoxZeroTreshold_clicked(bool flag);
	void on_spinBoxZeroTreshold_valueChanged(int treshold);
	void on_checkBoxUseEnterKey_clicked(bool flag);
	void on_checkBoxBinOut_clicked(bool flag);
	void on_checkBoxOctOut_clicked(bool flag);
	void on_checkBoxDecOut_clicked(bool flag);
	void on_checkBoxHexOut_clicked(bool flag);
	void on_radioButtonBW8_clicked();
	void on_radioButtonBW16_clicked();
	void on_radioButtonBW32_clicked();
	void on_radioButtonBW64_clicked();
	void on_checkBoxShowBasePrefix_clicked(bool flag);
	void on_pushButtonSetDefaults_clicked();
	void on_checkBoxShowLeadingZerosHex_clicked(bool flag);
	void on_checkBoxShowLeadingZerosBin_clicked(bool flag);

private:
	Settings* itsSettings; // Non-owned pointer
	void setupUiBySettings();
	void setNumberBaseOptionsEnabledState();
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_GUI_OPTIONS
