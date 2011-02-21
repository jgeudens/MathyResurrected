#include <QApplication>
#include "TestAppMainWindow.h"

using namespace mathy_resurrected;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	TestAppMainWindow mwin;
	mwin.show();
	return app.exec();
}