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

#include <QtGui>
#include <QUrl>
#include <QFile>
#include <QRegExp>
#include <QTextCodec>
#include <QClipboard>

#ifdef Q_WS_WIN
#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#endif

#include "MathyResurrectedPlugin.h"

using namespace mathy_resurrected;

MathyResurrectedPlugin* gmathyresurrectedInstance = NULL;

MathyResurrectedPlugin::MathyResurrectedPlugin() {
	HASH_MATHYRESURRECTED = qHash(QString("MathyResurrected"));
	itsName = "MathyResurrected";
	MathEvaluator* p = new MathEvaluator();
	itsCalculator.reset(p);
}

void MathyResurrectedPlugin::getID(uint* id) {
	*id = HASH_MATHYRESURRECTED;
}

void MathyResurrectedPlugin::getName(QString* str) {
	*str = itsName;
}

void MathyResurrectedPlugin::init() {
	if (gmathyresurrectedInstance == NULL)
		gmathyresurrectedInstance = this;

	QSettings* sett = *(this->settings);

 	itsCalculator->changeEvaluatorSettings(sett);

	itsSimpleMatching = sett->value(
			MathyResurrectedOptionsDialog::keyNameSimpleInputMatching(),
			MathyResurrectedOptionsDialog::defaultSimpleInputMatching()
		).toBool();
	itsUseEnterKey = sett->value(
			MathyResurrectedOptionsDialog::keyNameUseEnterKey(), 
			MathyResurrectedOptionsDialog::defaultUseEnterKey()
		).toBool();

	itsShowAllBases = sett->value(
		MathyResurrectedOptionsDialog::keyNameOutputShowAllBases(), 
		MathyResurrectedOptionsDialog::defaultOutputAllBases()
		).toBool();
	itsOutputBaseTag = sett->value(
		MathyResurrectedOptionsDialog::keyNameOutputBaseTag(), 
		MathyResurrectedOptionsDialog::defaultOutputBaseTag()
		).toString();

	itsGUI.reset();
}

void MathyResurrectedPlugin::getLabels(QList<InputData>* id) {
	if (id->count() > 1) return;

	const QString & text = id->last().getText();

	bool shouldLabl;
	if (itsSimpleMatching) {
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

		if (itsShowAllBases) {
			if (itsOutputBaseTag == "dec") {
				put_item_by_tag("dec", results);
				put_item_by_tag("hex", results);
				put_item_by_tag("bin", results);
				put_item_by_tag("oct", results);
			} else if (itsOutputBaseTag == "oct") {
				put_item_by_tag("oct", results);
				put_item_by_tag("dec", results);
				put_item_by_tag("hex", results);
				put_item_by_tag("bin", results);
			} else if (itsOutputBaseTag == "bin") {
				put_item_by_tag("bin", results);
				put_item_by_tag("oct", results);
				put_item_by_tag("dec", results);
				put_item_by_tag("hex", results);
			} else if (itsOutputBaseTag == "hex") {
				put_item_by_tag("hex", results);
				put_item_by_tag("bin", results);
				put_item_by_tag("oct", results);
				put_item_by_tag("dec", results);
			}
		} else {
			put_item_by_tag(itsOutputBaseTag, results);
		}
	}
}

void MathyResurrectedPlugin::put_item_by_tag(const QString& baseTag, QList<CatItem>* results) {
	QString result;

	if (baseTag == "dec") {
		result = itsCalculator->toString();
	} else if (baseTag == "bin") {
		result = itsCalculator->toStringBin();
	} else if (baseTag == "hex") {
		result = itsCalculator->toStringHex();
	} else if (baseTag == "oct") {
		result = itsCalculator->toStringOct();
	}

	results->push_front(CatItem(result + ".math", 
		result, HASH_MATHYRESURRECTED, getIcon()));
}

void MathyResurrectedPlugin::doDialog(QWidget* parent, QWidget** newDlg) {
	if (itsGUI != NULL) return;
	MathyResurrectedOptionsDialog* p = new MathyResurrectedOptionsDialog(parent);
	itsGUI.reset(p);
	*newDlg = itsGUI.get();
}

void MathyResurrectedPlugin::endDialog(bool accept) {
	if (accept) {
		itsGUI->writeSettings();
		init();
	}
	itsGUI.reset();
}

QString MathyResurrectedPlugin::getIcon() {
	return libPath + "/icons/mathyresurrected.ico";
}

void MathyResurrectedPlugin::setPath(QString * path) {
	libPath = *path;
}

void MathyResurrectedPlugin::launchItem(QList<InputData>* inputData, CatItem* item) {
	if (itsUseEnterKey) {
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
