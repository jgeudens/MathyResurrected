TARGET = test
TEMPLATE = app

QT = core gui

CONFIG += qt \
	warn_on \
	exceptions \
	debug_and_release \
	build_all

SOURCES += main.cpp TestAppMainWindow.cpp

HEADERS += TestAppMainWindow.h

include($${_PRO_FILE_PWD_}/../MathyResurrected.incl)

FORMS += $${_PRO_FILE_PWD_}/../ui/TestAppMainWindow.ui