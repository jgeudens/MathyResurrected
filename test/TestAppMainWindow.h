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

#ifndef MATHY_RESURRECTED_TEST_APP_WINDOW
#define MATHY_RESURRECTED_TEST_APP_WINDOW

#include <QMainWindow>
#include "ui_TestAppMainWindow.h"

namespace mathy_resurrected {

class MathEvaluator;
class Settings;

class TestAppMainWindow : public QMainWindow, private Ui::TestAppMainWindow {

	Q_OBJECT

public:
	TestAppMainWindow(QWidget* parent = 0);
	virtual ~TestAppMainWindow();

private slots:
	void on_lineEditExpression_editingFinished();

private:
	MathEvaluator *itsCalculator;
	Settings *itsSettings;
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_TEST_APP_WINDOW
