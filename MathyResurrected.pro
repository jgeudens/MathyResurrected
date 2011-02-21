
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += plugin testApp
testApp.depends = plugin

win32 {
	QMAKE_DISTCLEAN += *.ncb *.user *.suo *.sln *.vcproj *.rc *.pdb
}

DISTFILES += AUTHORS COPYING HISTORY INSTALL README README.odt TODO \
	icons/readme.txt \
	icons/mathyresurrected.png