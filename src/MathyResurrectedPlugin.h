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

#ifndef MATHY_REUSRECTED_MAIN_HEADER_INCLUDED
#define MATHY_REUSRECTED_MAIN_HEADER_INCLUDED

#include <QString>
#include "plugin_interface.h"

namespace mathy_resurrected {
	class Settings;
	class MathEvaluator;
	class OptionsDialog;
}

class MathyResurrectedPlugin : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

public:
	MathyResurrectedPlugin();
	virtual ~MathyResurrectedPlugin();

	virtual int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 

private:
	uint HASH_MATHYRESURRECTED;
	mathy_resurrected::MathEvaluator *itsCalculator;
	mathy_resurrected::OptionsDialog *itsGUI;
	mathy_resurrected::Settings *itsSettings;
	QString itsName;
	QString libPath;

	void getLabels(QList<InputData>*);
	void getID(uint*);
	void getName(QString*);
	void getResults(QList<InputData>* id, QList<CatItem>* results);
	void launchItem(QList<InputData>* inputData, CatItem* item);
	void doDialog(QWidget* parent, QWidget**);
	void endDialog(bool accept);
	void init();
	QString getIcon();
};

#endif // MATHY_REUSRECTED_MAIN_HEADER_INCLUDED