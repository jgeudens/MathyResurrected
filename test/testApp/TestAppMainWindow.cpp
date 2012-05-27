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
#include <QPluginLoader>
#include <QDir>
#include <QStringListIterator>
#include "plugin_interface.h"

namespace mathy_resurrected {

TestAppMainWindow::TestAppMainWindow(QWidget* parent) : 
	QMainWindow(parent), 
	m_pluginInstance(0), m_pluginGui(0) {
	setupUi(this);

	// Ensuring that artificial app settings are available to plugin 
	m_appSettings = new QSettings (
		qApp->applicationDirPath() + "/testApp.conf", 
		QSettings::IniFormat);
	
	// Loading plugin. Assumes that dll is in same dir as app exe
	// and that no other plugins exist in that directory.
	QDir pluginsDir(qApp->applicationDirPath());
	QStringListIterator fileName(pluginsDir.entryList(QDir::Files));
	while (fileName.hasNext() && m_pluginInstance == 0) {
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName.next()));
		QObject *plugin = pluginLoader.instance();
		if (plugin) {
			m_pluginInstance = qobject_cast<PluginInterface *>(plugin);
		}
	}

	// Initializing loaded plugin and it's gui
	m_placeholderLayout = new QVBoxLayout(groupBoxPlaceholder);
	if (m_pluginInstance != 0) {
		m_pluginInstance->settings = &m_appSettings;
		m_pluginInstance->msg(MSG_INIT);
		setupPluginGUI();
	}
}

TestAppMainWindow::~TestAppMainWindow() {
	m_pluginInstance->msg(MSG_END_DIALOG);
}

void TestAppMainWindow::setupPluginGUI() {
	m_pluginInstance->msg(MSG_DO_DIALOG, groupBoxPlaceholder, &m_pluginGui);
	m_placeholderLayout->addWidget(m_pluginGui);
}

void TestAppMainWindow::on_pushButtonApply_clicked() {
	// Dirty hack: 
	// deleting plugin GUI and then creating it again only to force 
	// saving of plugin settings.
	if (m_pluginGui != 0) {
		m_placeholderLayout->removeWidget(m_pluginGui);
	}
	m_pluginInstance->msg(MSG_END_DIALOG, (void*)true);
	setupPluginGUI();
}

void TestAppMainWindow::on_lineEditExpression_editingFinished() {
	plainTextEditResults->setPlainText("");

	InputData dta;
	dta.setText(lineEditExpression->text());

	QList<InputData> inList;
	QList<CatItem> outList;

	inList << dta;
	m_pluginInstance->msg(MSG_GET_LABELS, &inList);
	m_pluginInstance->msg(MSG_GET_RESULTS, &inList, &outList);

	Q_FOREACH (CatItem result, outList) {
		plainTextEditResults->appendPlainText(result.shortName);
	}
}

} // namespace mathy_resurrected
