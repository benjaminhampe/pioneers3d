TARGET = bexp
TEMPLATE = app
CONFIG += console c++14
QT += core gui widgets

### Release version
CONFIG(release, debug|release) {
   OBJECTS_DIR = $$PWD/obj/$$TARGET/release
   MOC_DIR = $$PWD/obj/$$TARGET/release/moc
   RCC_DIR = $$PWD/obj/$$TARGET/release/qrc
   UI_DIR = $$PWD/obj/$$TARGET/release/ui
   DESTDIR = $$PWD/../../bin
   TARGET = $${TARGET}_Win32
   # TARGET = $${TARGET}_Linux32
}

### Debug version
CONFIG(debug, debug|release) {
   OBJECTS_DIR = $$PWD/obj/$$TARGET/debug
   MOC_DIR = $$PWD/obj/$$TARGET/debug/moc
   RCC_DIR = $$PWD/obj/$$TARGET/debug/qrc
   UI_DIR = $$PWD/obj/$$TARGET/debug/ui
   DESTDIR = $$PWD/../../bin
   TARGET = $${TARGET}_debug_Win32
   # TARGET = $${TARGET}_Linux32_debug
   DEFINES += _DEBUG
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
		BexpMainWindow.cpp \
	Bexplorer.cpp \
	BXPSidePanel.cpp \
	bexpUtils.cpp \
	StaticClassLogger.cpp \
    BexpDriveList.cpp \
    BexpFileList.cpp

HEADERS  += BexpMainWindow.hpp \
	Bexplorer.hpp \
	BXPSidePanel.hpp \
	bexpUtils.hpp \
	StaticClassLogger.hpp \
    BexpDriveList.hpp \
    BexpFileList.hpp
