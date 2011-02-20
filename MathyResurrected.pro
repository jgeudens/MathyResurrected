
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += plugin test
test.depends = plugin

win32 {
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc
}

DISTFILES += AUTHORS COPYING HISTORY INSTALL README README.odt TODO \
	src/antlr/ComplexEval.g \
	src/antlr/ComplexLexer.g \
	src/antlr/ComplexParser.g \
	src/antlr/README.txt \
	src/antlr/regenerate.bat \
	icons/readme.txt \
	icons/mathyresurrected.png