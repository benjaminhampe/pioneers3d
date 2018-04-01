DEFINES += _IRR_STATIC_LIB_
INCLUDEPATH += $$PWD

DEFINES += USE_IRRLICHT=1

macx {
	INCLUDEPATH += /usr/local/include/irrlicht
	LIBS += -L${/usr/local/lib -lIrrlicht -framework Cocoa
}
else:win32 {
	INCLUDEPATH += $$PWD/include
	INCLUDEPATH += $$PWD/include/irrlicht
	HEADERS += $$PWD/include/irrlicht/*.h
	LIBS += -L$$PWD/lib/Win32-gcc
	CONFIG(debug, debug|release) {
				LIBS += -lIrrlichtd
	}
	CONFIG(release, debug|release) {
				LIBS += -lIrrlicht
	}

	LIBS += -lkernel32
	LIBS += -lgdi32
	LIBS += -ladvapi32
	LIBS += -luser32
	LIBS += -lshell32
	LIBS += -luuid
	LIBS += -lSetupAPI
	LIBS += -lole32
	LIBS += -loleaut32
	LIBS += -lComCtl32
	LIBS += -lopengl32
	LIBS += -lglu32
	LIBS += -lwinmm
}

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10
QMAKE_MAC_SDK = macosx10.11

HEADERS += \
	$$PWD/irrBackend.hpp

SOURCES += \
	$$PWD/irrBackend.cpp
