#include <QApplication>
#include "MathEvaluator.h"
#include "Settings.h"
#include "TestAppMainWindow.h"

using namespace mathy_resurrected;

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	TestAppMainWindow mwin;
	mwin.show();
	return app.exec();

// 	QString tmp;
// 	Settings sett;
// 	sett.setOutputFormat(Settings::FIXED);
// 	sett.setPrecision(2);
// 	MathEvaluator calc(&sett);
// 
// 	for (int i = 0; i < 10000; ++i) {
// 		calc.setExpression("234+2i");
// 		calc.evaluate();
// 		//	tmp = calc.toString();
// 
// 		tmp = calc.toString();
// 		tmp = calc.toStringHex();
// 		tmp = calc.toStringBin();
// 		tmp = calc.toStringOct();
// 		progressBar->setValue(i+1);
// 	}
}