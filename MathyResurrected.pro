TARGET = mathyresurrected
TEMPLATE = lib
VERSION = 0.1.2

CONFIG += plugin \
	warn_on \
	exceptions \
	debug_and_release \
	build_all

unix {
	PREFIX = /usr
	target.path = $$PREFIX/src/launchy/plugins/
	icon.path = $$PREFIX/src/launchy/plugins/icons/
	icon.files = $$PWD/../icons/mathyresurrected.png
	INSTALLS += target icon
}

win32 {
	CONFIG -= embed_manifest_dll
	LIBS += shell32.lib
	
	QMAKE_DISTCLEAN += *.ncb *.user *.suo
}

DISTFILES += $$PWD/AUTHORS \
	$$PWD/COPYING \
	$$PWD/HISTORY \
	$$PWD/INSTALL \
	$$PWD/README.mathyresurrected.txt \
	$$PWD/TODO \
	$$PWD/src/antlr/ComplexEval.g \
	$$PWD/src/antlr/ComplexLexer.g \
	$$PWD/src/antlr/ComplexParser.g \
	$$PWD/src/antlr/README.txt \
	$$PWD/src/antlr/regenerate.bat \
	$$PWD/icons/mathyresurrected.ico \
	$$PWD/icons/mathyresurrected.png

# generated files
MOC_DIR = $$PWD/build/generated
UI_DIR = $$PWD/build/generated
INCLUDEPATH += $$PWD/build/generated

FORMS = $$PWD/ui/OptionsWidget.ui

# debug build options
CONFIG(debug, debug|release) {
	DESTDIR = $$PWD/bin/debug
	OBJECTS_DIR = $$PWD/build/debug	
}

# release build options
CONFIG(release, debug|release) { 
	DESTDIR = $$PWD/bin/release
	OBJECTS_DIR = $$PWD/build/release
}

LIBS += -lantlr3c

# Plugin main sources
SOURCES += $$PWD/src/MathyResurrectedOptionsDialog.cpp \
	$$PWD/src/MathyResurrectedPlugin.cpp \
	$$PWD/src/evaluator/MathEvaluator.cpp \
	$$PWD/src/evaluator/MathyResurrectedExceptions.cpp \
	$$PWD/src/evaluator/math_bridge_API.cpp
HEADERS += $$PWD/src/MathyResurrectedOptionsDialog.h \
	$$PWD/src/MathyResurrectedPlugin.h \
	$$PWD/src/evaluator/MathEvaluator.h \
	$$PWD/src/evaluator/MathyResurrectedExceptions.h \
	$$PWD/src/evaluator/math_bridge_API.h \
	$$PWD/src/evaluator/math_bridge_API_types.h
INCLUDEPATH += $$PWD/src \
	$$PWD/src/evaluator

# Plugin API sources
HEADERS += $$PWD/src/pluginAPI/plugin_interface.h \
	$$PWD/src/pluginAPI/catalog.h
SOURCES += $$PWD/src/pluginAPI/plugin_interface.cpp
INCLUDEPATH += $$PWD/src/pluginAPI

# ANTLR generated math lexer, parser and evaluator
SOURCES += $$PWD/src/antlr/ComplexEval.c \
	$$PWD/src/antlr/ComplexLexer.c \
	$$PWD/src/antlr/ComplexParser.c
HEADERS += $$PWD/src/antlr/ComplexEval.h \
	$$PWD/src/antlr/ComplexLexer.h \
	$$PWD/src/antlr/ComplexParser.h
INCLUDEPATH += $$PWD/src/antlr

