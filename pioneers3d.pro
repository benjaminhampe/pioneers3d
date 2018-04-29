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
	src/common/sinCosTable.hpp \
	src/common/AutoMeshBufferUtils.hpp \
	src/common/createRoundRect.hpp \
	src/common/Camera.hpp \
	src/common/createDevice.hpp \
	src/common/ImageUtils.hpp \
	src/common/StringUtils.hpp \
	src/common/Types.hpp \
	src/common/BaseEventReceiver.hpp \
	src/common/OffscreenRenderer.hpp \
	src/common/Logger.hpp \
	src/common/FontUtils.hpp \
	src/pioneers3d/scene/BoardSceneNode.hpp \
	src/pioneers3d/scene/TileSceneNode.hpp \
	src/pioneers3d/eGameState.hpp \
	src/pioneers3d/eGameType.hpp \
	src/pioneers3d/eTexture.hpp \
	src/pioneers3d/eTileType.hpp \
	src/pioneers3d/Types.hpp \
	src/pioneers3d/Game.hpp \
	src/pioneers3d/Game_Camera.hpp \
	src/pioneers3d/Game_EventReceiver.hpp \
	src/pioneers3d/Game_Raeuber.hpp \
	src/pioneers3d/Game_Logger.hpp \
	src/pioneers3d/Game_Bank.hpp \
	src/pioneers3d/Game_Action.hpp \
	src/pioneers3d/Game_Tile.hpp \
	src/pioneers3d/Game_Waypoint.hpp \
	src/pioneers3d/Game_Texture.hpp \
	src/pioneers3d/Game_Player.hpp \
	src/pioneers3d/Game_UI.hpp \
	src/pioneers3d/Game_Font.hpp \
	src/pioneers3d/eAction.hpp \
	src/common/BaseWindow.hpp \
	src/pioneers3d/Game_Chat.hpp \
	src/pioneers3d/Game_Objects.hpp \
    src/common/RuntimeLogger.hpp

SOURCES += \
	src/common/AutoMeshBuffer.cpp \
	src/common/AutoMeshBufferUtils.cpp \
	src/common/createRoundRect.cpp \
	src/common/Camera.cpp \
	src/common/createDevice.cpp \
	src/common/ImageUtils.cpp \
	src/common/StringUtils.cpp \
	src/common/BaseEventReceiver.cpp \
	src/common/OffscreenRenderer.cpp \
	src/common/Logger.cpp \
	src/common/FontUtils.cpp \
	src/pioneers3d/scene/BoardSceneNode.cpp \
	src/pioneers3d/scene/TileSceneNode.cpp \
	src/pioneers3d/main_Pioneers3D.cpp \
	src/pioneers3d/Types.cpp \
	src/pioneers3d/Game.cpp \
	src/pioneers3d/Game_EventReceiver.cpp \
	src/pioneers3d/Game_Camera.cpp \
	src/pioneers3d/Game_Raeuber.cpp \
	src/pioneers3d/Game_Logger.cpp \
	src/pioneers3d/Game_Bank.cpp \
	src/pioneers3d/Game_Action.cpp \
	src/pioneers3d/Game_Player.cpp \
	src/pioneers3d/Game_Texture.cpp \
	src/pioneers3d/Game_Waypoint.cpp \
	src/pioneers3d/Game_Tile.cpp \
	src/pioneers3d/Game_Font.cpp \
	src/pioneers3d/Game_UI.cpp \
	src/common/BaseWindow.cpp \
	src/pioneers3d/Game_Chat.cpp \
	src/pioneers3d/Game_Objects.cpp \
    src/common/RuntimeLogger.cpp
