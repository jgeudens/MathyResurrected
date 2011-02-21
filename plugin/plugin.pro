TARGET = mathyresurrected
TEMPLATE = lib
VERSION = 0.2.0

unix {
	PREFIX = /usr
	target.path = $$PREFIX/src/launchy/plugins/
	icon.path = $$PREFIX/src/launchy/plugins/icons/
	icon.files = $${_PRO_FILE_PWD_}/../icons/mathyresurrected.png
	INSTALLS += target icon
}

win32 {
	CONFIG -= embed_manifest_dll
}

CONFIG += plugin \
	warn_on \
	exceptions \
	debug_and_release \
	build_all

# no_keywords because ANTLR uses 'emit' in it's headers. 
CONFIG += no_keywords

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
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc *.pdb
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
