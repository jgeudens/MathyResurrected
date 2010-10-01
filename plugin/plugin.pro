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

include($${_PRO_FILE_PWD_}/../MathyResurrected.incl)
