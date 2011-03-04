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
#include <QSettings>
#include "ui_TestAppMainWindow.h"

class PluginInterface;

namespace mathy_resurrected {

/** Quick any dirty test suite implementation. 
This is little app used for debugging purposes. Written mainly to 
avoid need to install each new build of mathyresurrected plugin into
Launchy directory to be able to test it. */
class TestAppMainWindow : public QMainWindow, private Ui::TestAppMainWindow {

	Q_OBJECT

public:
	TestAppMainWindow(QWidget* parent = 0);
	virtual ~TestAppMainWindow();

private Q_SLOTS:
	void on_lineEditExpression_editingFinished();
	void on_pushButtonApply_clicked();

private:
	PluginInterface* m_pluginInstance;
	QSettings* m_appSettings;
	QWidget* m_pluginGui;
	QVBoxLayout* m_placeholderLayout;

	void setupPluginGUI();
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_TEST_APP_WINDOW
