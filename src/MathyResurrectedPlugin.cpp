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

#include "MathyResurrectedPlugin.h"
#include <QtCore>
#include <QClipboard>
#include "Settings.h"
#include "OptionsDialog.h"
#include "MathEvaluator.h"

using namespace mathy_resurrected;

MathyResurrectedPlugin::MathyResurrectedPlugin() {
	HASH_MATHYRESURRECTED = qHash(QString("MathyResurrected"));
	itsName = "MathyResurrected";
	itsSettings = new Settings(this);
	itsCalculator = new MathEvaluator(itsSettings, this);
	itsGUI = 0;
}

MathyResurrectedPlugin::~MathyResurrectedPlugin() {
}

void MathyResurrectedPlugin::getID(uint* id) {
	*id = HASH_MATHYRESURRECTED;
}

void MathyResurrectedPlugin::getName(QString* str) {
	*str = itsName;
}

void MathyResurrectedPlugin::init() {
	// Read QSettings into our mathyresurrected::Settings
	itsSettings->readSettings(*(this->settings));
	itsGUI->deleteLater();
	itsGUI = 0;
}

void MathyResurrectedPlugin::getLabels(QList<InputData>* id) {
	if (id->count() > 1) return;

	const QString & text = id->last().getText();

	bool shouldLabl;
	if (itsSettings->useSimpleInputMatching()) {
		QString tmp_expr = text;
		if (tmp_expr.startsWith('=')) {
			tmp_expr.remove(0, 1);
			itsCalculator->setExpression(tmp_expr);
			// simple matching: no validation is done before evaluation.
			shouldLabl = true;
		}
	} else {
		itsCalculator->setExpression(text);
		shouldLabl = itsCalculator->validate();
	}

	if (shouldLabl) {
		id->last().setLabel(HASH_MATHYRESURRECTED);
	}
}

void MathyResurrectedPlugin::getResults(QList<InputData>* id, QList<CatItem>* results) {
	if (id->last().hasLabel(HASH_MATHYRESURRECTED)) {
		itsCalculator->evaluate();

		QString result;

		if (itsSettings->showDecOutput()) {
			result = itsCalculator->toString();
			results->push_back(CatItem(result + ".math.dec", 
				result, HASH_MATHYRESURRECTED, getIcon()));
		}

		if (itsSettings->showOctOutput()) {
			result = itsCalculator->toStringOct();
			results->push_back(CatItem(result + ".math.oct", 
				result, HASH_MATHYRESURRECTED, getIcon()));
		}

		if (itsSettings->showBinOutput()) {
			result = itsCalculator->toStringBin();
			results->push_back(CatItem(result + ".math.bin", 
				result, HASH_MATHYRESURRECTED, getIcon()));
		}

		if (itsSettings->showHexOutput()) {
			result = itsCalculator->toStringHex();
			results->push_back(CatItem(result + ".math.hex", 
				result, HASH_MATHYRESURRECTED, getIcon()));
		}
	}
}

void MathyResurrectedPlugin::doDialog(QWidget* parent, QWidget** newDlg) {
	if (itsGUI == 0) {
		itsGUI = new OptionsDialog(parent, itsSettings);
		*newDlg = itsGUI;
	}
}

void MathyResurrectedPlugin::endDialog(bool accept) {
	if (accept) {
		itsSettings->writeSettings(*(this->settings));
		init();
	} else {
		itsGUI->deleteLater();
		itsGUI = 0;
	}
}

QString MathyResurrectedPlugin::getIcon() {
	return libPath + "/icons/mathyresurrected.png";
}

void MathyResurrectedPlugin::setPath(QString * path) {
	libPath = *path;
}

void MathyResurrectedPlugin::launchItem(QList<InputData>* /*inputData*/, CatItem* item) {
	if (itsSettings->useEnterToCopy()) {
		QClipboard *clipboard = QApplication::clipboard();
		clipboard->setText(item->shortName);
	}
	itsCalculator->storeAns();
}	

int MathyResurrectedPlugin::msg(int msgId, void* wParam, void* lParam) {
	bool handled = false;
	switch (msgId) 	{		
		case MSG_INIT:
			init();
			handled = true;
			break;
		case MSG_GET_LABELS:
			getLabels((QList<InputData>*) wParam);
			handled = true;
			break;
		case MSG_GET_ID:
			getID((uint*) wParam);
			handled = true;
			break;
		case MSG_GET_NAME:
			getName((QString*) wParam);
			handled = true;
			break;
		case MSG_GET_RESULTS:
			getResults((QList<InputData>*) wParam, (QList<CatItem>*) lParam);
			handled = true;
			break;
		case MSG_LAUNCH_ITEM:
			launchItem((QList<InputData>*) wParam, (CatItem*) lParam);
			handled = true;
		break;
		case MSG_HAS_DIALOG:
			// Set to true if you provide a gui
			handled = true;
			break;
		case MSG_DO_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			doDialog((QWidget*) wParam, (QWidget**) lParam);
			break;
		case MSG_END_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			endDialog((bool) wParam);
			break;
		case MSG_PATH:
			setPath((QString *) wParam);
			break;

		default:
			break;
	}
		
	return handled;
}

Q_EXPORT_PLUGIN2(mathyresurrected, MathyResurrectedPlugin) 
