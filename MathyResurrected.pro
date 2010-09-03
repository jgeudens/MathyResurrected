TARGET = mathyresurrected
TEMPLATE = lib
VERSION = 0.1.6

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
	
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc
}

DISTFILES += AUTHORS \
	COPYING \
	HISTORY \
	INSTALL \
	README.mathyresurrected.txt \
	TODO \
	src/antlr/ComplexEval.g \
	src/antlr/ComplexLexer.g \
	src/antlr/ComplexParser.g \
	src/antlr/README.txt \
	src/antlr/regenerate.bat \
	icons/mathyresurrected.ico \
	icons/mathyresurrected.png

FORMS = ui/OptionsWidget.ui

CONFIG(release, debug|release) { # general release build options
	DESTDIR = $${_PRO_FILE_PWD_}/bin/release
	OBJECTS_DIR = $${_PRO_FILE_PWD_}/build/release
	RCC_DIR = $${_PRO_FILE_PWD_}/build/release
	MOC_DIR = $${_PRO_FILE_PWD_}/build/release
	UI_DIR = $${_PRO_FILE_PWD_}/build/release
	INCLUDEPATH += $${_PRO_FILE_PWD_}/build/release
} else {                         # general debug build options
	DESTDIR = $${_PRO_FILE_PWD_}/bin/debug
	OBJECTS_DIR = $${_PRO_FILE_PWD_}/build/debug
	RCC_DIR = $${_PRO_FILE_PWD_}/build/debug
	MOC_DIR = $${_PRO_FILE_PWD_}/build/debug
	UI_DIR = $${_PRO_FILE_PWD_}/build/debug
	INCLUDEPATH += $${_PRO_FILE_PWD_}/build/debug
}

LIBS += -lantlr3c

# Plugin main sources
SOURCES += src/OptionsDialog.cpp \
	src/Settings.cpp \
	src/MathyResurrectedPlugin.cpp \
	src/evaluator/MathEvaluator.cpp \
	src/evaluator/Exceptions.cpp \
	src/evaluator/math_bridge_globals.cpp \
	src/evaluator/math_bridge_API.cpp
HEADERS += src/OptionsDialog.h \
	src/Settings.h \
	src/MathyResurrectedPlugin.h \
	src/evaluator/MathEvaluator.h \
	src/evaluator/Exceptions.h \
	src/evaluator/math_bridge_globals.h \
	src/evaluator/math_bridge_API.h \
	src/evaluator/math_bridge_API_types.h
INCLUDEPATH += src \
	src/evaluator

# Plugin API sources
HEADERS += src/pluginAPI/plugin_interface.h \
	src/pluginAPI/catalog.h
SOURCES += src/pluginAPI/plugin_interface.cpp
INCLUDEPATH += src/pluginAPI

# ANTLR generated math lexer, parser and evaluator
SOURCES += src/antlr/ComplexEval.c \
	src/antlr/ComplexLexer.c \
	src/antlr/ComplexParser.c
HEADERS += src/antlr/ComplexEval.h \
	src/antlr/ComplexLexer.h \
	src/antlr/ComplexParser.h
INCLUDEPATH += src/antlr

