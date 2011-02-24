TARGET = mathyresurrected
TEMPLATE = lib
VERSION = 0.2.0

# Install target on UNIX
unix:!macx {
    PREFIX = /usr
    target.path = $$PREFIX/lib/launchy/plugins/
    icon.path = $$PREFIX/lib/launchy/plugins/icons/
    icon.files = mathyresurrected.png
    INSTALLS += target \
        icon
}

# Install target on MacOS. Not that this is copy-paste of Launchy's
# calcy plugin. I have no means to test if it actually work.
macx {
  if(!debug_and_release|build_pass):CONFIG(debug, debug|release):DESTDIR = ../../debug/Launchy.app/Contents/MacOS/plugins
  if(!debug_and_release|build_pass):CONFIG(release, debug|release):DESTDIR = ../../release/Launchy.app/Contents/MacOS/plugins

    CONFIG(debug, debug|release):icons.path = ../../debug/Launchy.app/Contents/MacOS/plugins/icons/
    CONFIG(release, debug|release):icons.path = ../../release/Launchy.app/Contents/MacOS/plugins/icons/
    icons.files = mathyresurrected.png
    INSTALLS += icons

  INCLUDEPATH += /opt/local/include/
}

win32 {
	CONFIG -= embed_manifest_dll
}

QT = core gui

CONFIG += qt plugin \
	warn_on \
	exceptions \
	debug_and_release

# no_keywords because ANTLR uses 'emit' in it's C runtime headers.
CONFIG += no_keywords

# Plugin main sources
SOURCES += OptionsDialog.cpp \
	Settings.cpp \
	MathyResurrectedPlugin.cpp \
	evaluator/MathEvaluator.cpp \
	evaluator/Exceptions.cpp \
	evaluator/Conversion.cpp
HEADERS += OptionsDialog.h \
	Settings.h \
	MathyResurrectedPlugin.h \
	evaluator/MathEvaluator.h \
	evaluator/Exceptions.h \
	evaluator/Conversion.h \
	evaluator/MathTypes.h
INCLUDEPATH += . evaluator

# Plugin API sources
HEADERS += $${_PRO_FILE_PWD_}/../interface/plugin_interface.h \
	$${_PRO_FILE_PWD_}/../interface/catalog.h
SOURCES += $${_PRO_FILE_PWD_}/../interface/plugin_interface.cpp
INCLUDEPATH += $${_PRO_FILE_PWD_}/../interface

# ANTLR generated math lexer, parser and evaluator
SOURCES += antlr/ComplexEval.cpp \
	antlr/ComplexLexer.cpp \
	antlr/ComplexParser.cpp
HEADERS += antlr/ComplexEval.h \
	antlr/ComplexLexer.h \
	antlr/ComplexParser.h
INCLUDEPATH += antlr

DISTFILES += antlr/ComplexEval.g \
	antlr/ComplexLexer.g \
	antlr/ComplexParser.g \
	antlr/README.txt \
	antlr/regenerate.bat

FORMS = $${_PRO_FILE_PWD_}/../ui/OptionsWidget.ui

LIBS += -lantlr3c

win32 {
	LIBS += shell32.lib
}

# Adding linking options for GNU BigNum library and related libraries
# TODO: Find out if these libraries are portable to MacOS and how to link them there

win32 {
	LIBS += -lmpir
}

unix {
	LIBS += -lgmp
}

LIBS += -lmpfr -lmpc

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