TARGET = Pioneers3D
TEMPLATE = app
DEFINES += USE_WINDOWS
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-comment
# QT += core gui widgets

### Release version
CONFIG(release, debug|release) {
   OBJECTS_DIR = $$PWD/obj/$$TARGET/release
   MOC_DIR = $$PWD/obj/$$TARGET/release/moc
   RCC_DIR = $$PWD/obj/$$TARGET/release/qrc
   UI_DIR = $$PWD/obj/$$TARGET/release/ui
   DESTDIR = $$PWD/bin/win32-gcc
   TARGET = $${TARGET}
}

### Debug version
CONFIG(debug, debug|release) {
   OBJECTS_DIR = $$PWD/obj/$$TARGET/debug
   MOC_DIR = $$PWD/obj/$$TARGET/debug/moc
   RCC_DIR = $$PWD/obj/$$TARGET/debug/qrc
   UI_DIR = $$PWD/obj/$$TARGET/debug/ui
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

# Sources:
INCLUDEPATH += $$PWD/src

HEADERS	+= \
	src/common/AlphaSonic.hpp \
	src/common/AutoMeshBuffer.hpp \
	src/common/AutoSceneNode.hpp \
	src/common/Camera.hpp \
	src/common/createBox.hpp \
	src/common/createCircle.hpp \
	src/common/createCylinder.hpp \
	src/common/createDevice.hpp \
	src/common/createHexagon.hpp \
	src/common/createRect.hpp \
	src/common/createRoundRect.hpp \
	src/common/createTriangle.hpp \
	src/common/ImageUtils.hpp \
	src/common/sinCosTable.hpp \
	src/common/StringUtils.hpp \
	src/common/Types.hpp \
	src/common/BaseEventReceiver.hpp \
	src/common/OffscreenRenderer.hpp \
	src/common/Logger.hpp \
	src/pioneers3d/scene/BoardSceneNode.hpp \
	src/pioneers3d/scene/TileSceneNode.hpp \
	src/pioneers3d/eGameState.hpp \
	src/pioneers3d/eGameType.hpp \
	src/pioneers3d/eTexture.hpp \
	src/pioneers3d/eTileType.hpp \
	src/pioneers3d/Types.hpp \
	src/pioneers3d/Game.hpp \
	src/pioneers3d/Game_Textures.hpp \
	src/pioneers3d/Game_Waypoints.hpp \
	src/pioneers3d/Game_Camera.hpp \
	src/pioneers3d/Game_Tiles.hpp \
	src/pioneers3d/Game_Players.hpp \
	src/pioneers3d/EventReceiver.hpp \
	src/pioneers3d/gui/MainMenu.hpp \
	src/pioneers3d/gui/UI_Player.hpp \
	src/pioneers3d/gui/UI_Game.hpp \
	src/pioneers3d/gui/UI_Trade.hpp \
	src/pioneers3d/gui/UI_Dice.hpp \
	src/pioneers3d/gui/UI_Camera.hpp \
	src/pioneers3d/Game_Raeuber.hpp \
	src/pioneers3d/gui/UI_Chat.hpp \
	src/pioneers3d/Game_Logger.hpp \
	src/pioneers3d/gui/UI_Bank.hpp \
	src/pioneers3d/gui/UI_Card.hpp

SOURCES += \
	src/common/AutoMeshBuffer.cpp \
	src/common/AutoSceneNode.cpp \
	src/common/Camera.cpp \
	src/common/createBox.cpp \
	src/common/createCircle.cpp \
	src/common/createCylinder.cpp \
	src/common/createDevice.cpp \
	src/common/createHexagon.cpp \
	src/common/createRect.cpp \
	src/common/createRoundRect.cpp \
	src/common/createTriangle.cpp \
	src/common/ImageUtils.cpp \
	src/common/StringUtils.cpp \
	src/common/BaseEventReceiver.cpp \
	src/common/OffscreenRenderer.cpp \
	src/common/Logger.cpp \
	src/pioneers3d/scene/BoardSceneNode.cpp \
	src/pioneers3d/scene/TileSceneNode.cpp \
	src/pioneers3d/EventReceiver.cpp \
	src/pioneers3d/Game.cpp \
	src/pioneers3d/main_Pioneers3D.cpp \
	src/pioneers3d/Types.cpp \
	src/pioneers3d/Game_Textures.cpp \
	src/pioneers3d/Game_Waypoints.cpp \
	src/pioneers3d/Game_Camera.cpp \
	src/pioneers3d/Game_Tiles.cpp \
	src/pioneers3d/Game_Players.cpp \
	src/pioneers3d/gui/MainMenu.cpp \
	src/pioneers3d/gui/UI_Player.cpp \
	src/pioneers3d/gui/UI_Game.cpp \
	src/pioneers3d/gui/UI_Trade.cpp \
	src/pioneers3d/gui/UI_Dice.cpp \
	src/pioneers3d/gui/UI_Camera.cpp \
	src/pioneers3d/Game_Raeuber.cpp \
	src/pioneers3d/gui/UI_Chat.cpp \
	src/pioneers3d/Game_Logger.cpp \
	src/pioneers3d/gui/UI_Bank.cpp \
	src/pioneers3d/gui/UI_Card.cpp
