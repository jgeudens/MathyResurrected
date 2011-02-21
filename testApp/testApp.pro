TARGET = testApp
TEMPLATE = app

QT = core gui

CONFIG += qt \
	warn_on \
	exceptions \
	debug_and_release \
	build_all

SOURCES += main.cpp TestAppMainWindow.cpp

HEADERS += TestAppMainWindow.h

FORMS += $${_PRO_FILE_PWD_}/../ui/TestAppMainWindow.ui

INCLUDEPATH += $${_PRO_FILE_PWD_}/../interface

CONFIG(release, debug|release) { # general release build options
	DESTDIR = $${_PRO_FILE_PWD_}/../bin/release
	OBJECTS_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/release
	RCC_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/release
	MOC_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/release
	UI_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/release
	INCLUDEPATH += $${_PRO_FILE_PWD_}/../build/$${TARGET}/release
} else {                         # general debug build options
	DESTDIR = $${_PRO_FILE_PWD_}/../bin/debug
	OBJECTS_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/debug
	RCC_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/debug
	MOC_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/debug
	UI_DIR = $${_PRO_FILE_PWD_}/../build/$${TARGET}/debug
	INCLUDEPATH += $${_PRO_FILE_PWD_}/../build/$${TARGET}/debug
}

win32 {
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc *.pdb
}