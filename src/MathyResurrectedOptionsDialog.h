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
#include <QSettings>
#include <QLocale>
#include "ui_OptionsWidget.h"

namespace mathy_resurrected {

class MathyResurrectedOptionsDialog : public QFrame, private Ui::MathyResurrectedOptions {

	Q_OBJECT

private slots:
	void setFunArgSeparatorColon() { itsArgSeparator = ':'; }
	void setFunArgSeparatorSemicolon() { itsArgSeparator = ';'; }
	void setFunArgSeparatorComa() { itsArgSeparator = ','; }
	void setSimpleInputMatching(bool flag) { itsSimpleInputFlag = flag; }
	void setOutputFormatDefault() { itsOutputFormat = 'd'; }
	void setOutputFormatScientiffic() { itsOutputFormat = 's'; }
	void setOutputFormatFixed() { itsOutputFormat = 'f'; }
	void setPrecision(int prec) { itsPrecision = prec;}
	void setShowDigitGrouping(bool flag) { itsShowDigitGrouping = flag;}
	void setUseEnterKey(bool flag) { itsUseEnterKey = flag;}
	void setZeroTresholdExp(int treshold) { itsZeroTresholdExp = treshold; }
	void setShouldUseZeroTreshold(bool flag) { itsZeroTresholdFlag = flag; }
	void setAllDefaults();

public:
	MathyResurrectedOptionsDialog(QWidget* parent = 0);
	~MathyResurrectedOptionsDialog();

	static QString keyNameArgSeparator() { return QString("MathyResurrected/ArgSeparator"); }
	static QString keyNameSimpleInputMatching() { return QString("MathyResurrected/SimpleInputMatching"); }
	static QString keyNameOutputFormat() { return QString("MathyResurrected/OutputFormat"); }
	static QString keyNamePrecision() { return QString("MathyResurrected/Precision"); }
	static QString keyNameUseEnterKey() { return QString("MathyResurrected/CopyToClipboardWithEnterKey"); }
	static QString keyNameShowDigitGrouping() { return QString("MathyResurrected/ShowDigitGroupChar"); }
	static QString keyNameShouldUseZeroTreshold() { return QString("MathyResurrected/ShouldUseZeroZresjold"); }
	static QString keyNameZeroTresholdExp() { return QString("MathyResurrected/ZeroTresholdExponent"); }
	
	void writeSettings();

	static bool defaultUseEnterKey() { return true; }
	static bool defaultSimpleInputMatching() { return false; }

private:
	QChar itsArgSeparator;
	QChar itsOutputFormat;
	int itsPrecision;
	bool itsSimpleInputFlag;
	bool itsShowDigitGrouping;
	bool itsUseEnterKey;
	bool itsZeroTresholdFlag;
	int itsZeroTresholdExp;
	
	void connectAll();
	void setupUiByAppSettings();
};

} // namespace mathy_resurrected

#endif // MATHY_RESURRECTED_GUI_OPTIONS
