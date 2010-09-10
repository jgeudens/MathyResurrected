
TEMPLATE = subdirs
CONFIG += ordered debug_and_release

SUBDIRS += plugin test
test.depends = plugin

win32 {
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc
}

DISTFILES += AUTHORS COPYING HISTORY INSTALL README.mathyresurrected.txt TODO \
	src/antlr/ComplexEval.g \
	src/antlr/ComplexLexer.g \
	src/antlr/ComplexParser.g \
	src/antlr/README.txt \
	src/antlr/regenerate.bat \
	icons/mathyresurrected.ico \
	icons/mathyresurrected.png