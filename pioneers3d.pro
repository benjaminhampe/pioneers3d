TARGET = Pioneers3D
TEMPLATE = app
DEFINES += USE_WINDOWS
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
# QMAKE_CXXFLAGS += -Werror-no-return-type
QMAKE_CXXFLAGS += -Wno-comment
# QT += core gui widgets

### Release version
CONFIG(release, debug|release) {
#   OBJECTS_DIR = $$PWD/obj/$$TARGET/release
#   MOC_DIR = $$PWD/obj/$$TARGET/release/moc
#   RCC_DIR = $$PWD/obj/$$TARGET/release/qrc
#   UI_DIR = $$PWD/obj/$$TARGET/release/ui
   DESTDIR = $$PWD/bin/win32-gcc
   TARGET = $${TARGET}
}

### Debug version
CONFIG(debug, debug|release) {
#   OBJECTS_DIR = $$PWD/obj/$$TARGET/debug
#   MOC_DIR = $$PWD/obj/$$TARGET/debug/moc
#   RCC_DIR = $$PWD/obj/$$TARGET/debug/qrc
#   UI_DIR = $$PWD/obj/$$TARGET/debug/ui
   DESTDIR = $$PWD/bin/win32-gcc
   TARGET = $${TARGET}_debug
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

include ( src/pioneers3d/app/app.pri )
include ( lib/lib-awesome/lib-awesome.pri )
include ( lib/lib-tinyxml2/lib-tinyxml2.pri )
include ( lib/lib-freetype-2.9-static/lib-freetype-2.9-static.pri )
include ( lib/lib-irrlicht-1.8.4-static/lib-irrlicht-1.8.4-static.pri )
include ( lib/lib-glm/lib-glm.pri )

include ( src/common/AlphaSonic.pri )

SOURCES += \
src/pioneers3d/main_Pioneers3D.cpp \
src/pioneers3d/StandardGame.cpp \
src/pioneers3d/data/Action.cpp \
src/pioneers3d/data/Board.cpp \
src/pioneers3d/data/Chat.cpp \
src/pioneers3d/data/Font.cpp \
src/pioneers3d/data/Object.cpp \
src/pioneers3d/data/Player.cpp \
src/pioneers3d/data/Texture.cpp \
src/pioneers3d/data/Types.cpp \
src/pioneers3d/data/UI.cpp \
src/pioneers3d/data/CylinderCamera.cpp

HEADERS += \
src/pioneers3d/CompileConfig.hpp \
src/pioneers3d/StandardGame.hpp \
src/pioneers3d/data/Action.hpp \
src/pioneers3d/data/All.hpp \
src/pioneers3d/data/Board.hpp \
src/pioneers3d/data/Chat.hpp \
src/pioneers3d/data/eAction.hpp \
src/pioneers3d/data/eGameState.hpp \
src/pioneers3d/data/eGameType.hpp \
src/pioneers3d/data/eTexture.hpp \
src/pioneers3d/data/eTileType.hpp \
src/pioneers3d/data/Font.hpp \
src/pioneers3d/data/Object.hpp \
src/pioneers3d/data/Player.hpp \
src/pioneers3d/data/Texture.hpp \
src/pioneers3d/data/Types.hpp \
src/pioneers3d/data/UI.hpp \
src/pioneers3d/data/CylinderCamera.hpp
