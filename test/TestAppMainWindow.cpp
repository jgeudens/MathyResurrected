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

#include "TestAppMainWindow.h"
#include "MathEvaluator.h"
#include "Settings.h"
#include "math_bridge_globals.h"

namespace mathy_resurrected {

TestAppMainWindow::TestAppMainWindow(QWidget* parent) : 
	QMainWindow(parent) {
	setupUi(this);
	itsSettings = new Settings(this);
	itsSettings->setCalculationBitWidth(Settings::BW8);
	BridgeAPIGlobals::setBitWidth(8);

	itsSettings->setShowBinOutput(true);
	itsSettings->setShowDecOutput(true);
	itsSettings->setShowHexOutput(true);
	itsSettings->setShowOctOutput(true);
	
	itsSettings->setShowLeadingZeroesBin(true);
	itsSettings->setShowLeadingZeroesHex(true);
	itsSettings->setShowLeadingZeroesOct(true);
	itsSettings->setShowBasePrefix(true);

	itsSettings->setOutputFormat(Settings::FIXED);

	frameSettings->setSettingsObject(itsSettings);
	itsCalculator = new MathEvaluator(itsSettings, this);
}

TestAppMainWindow::~TestAppMainWindow() {
	setupUi(this);
}

void TestAppMainWindow::on_lineEditExpression_editingFinished() {
	itsCalculator->setExpression(lineEditExpression->text());
	if (itsCalculator->evaluate()) {
		if (itsSettings->showBinOutput()) {
			lineEditResultBin->setText(itsCalculator->toStringBin());
		} else {
			lineEditResultBin->clear();
		}

		if (itsSettings->showDecOutput()) {
			lineEditResultDec->setText(itsCalculator->toString());
		} else {
			lineEditResultDec->clear();
		}

		if (itsSettings->showHexOutput()) {
			lineEditResultHex->setText(itsCalculator->toStringHex());
		} else {
			lineEditResultHex->clear();
		}

		if (itsSettings->showOctOutput()) {
			lineEditResultOct->setText(itsCalculator->toStringOct());
		} else {
			lineEditResultOct->clear();
		}
	} else {
		lineEditResultDec->clear();
		lineEditResultBin->clear();
		lineEditResultHex->clear();
		lineEditResultOct->clear();
	}
}

} // namespace mathy_resurrected
