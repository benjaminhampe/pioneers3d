TARGET = Pioneers3D
TEMPLATE = app
CONFIG += console c++14
QT += core gui widgets
DEFINES += USE_IRRLICHT
DEFINES += USE_WINDOWS

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

include ( lib/res/res.pri )
include ( lib/lib-awesome/lib-awesome.pri )
include ( lib/lib-tinyxml2/lib-tinyxml2.pri )
include ( lib/lib-irrlicht-1.8.4/lib-irrlicht-1.8.4-mingw530.pri )
include ( lib/lib-glm/lib-glm.pri )

# Sources:
INCLUDEPATH += $$PWD/src

HEADERS	+= \
	src/common/Camera.hpp \
	src/common/createCircleMeshBuffer.hpp \
	src/common/createHexagonMeshBuffer.hpp \
	src/common/createImage.hpp \
	src/common/createMesh.hpp \
	src/common/createMeshBuffer.hpp \
	src/common/createTexture.hpp \
	src/common/loadImage.hpp \
	src/common/Types.hpp \
	src/common/Utils.hpp \
	src/common/TextureManager.hpp \
	src/common/AutoMeshBuffer.hpp \
	src/common/AutoSceneNode.hpp \
	src/common/createDevice.hpp \
    src/pioneers3d/common/BoardData.hpp \
    src/pioneers3d/common/PlayerData.hpp \
    src/pioneers3d/common/StandardGame.hpp \
    src/pioneers3d/common/TextureData.hpp \
    src/pioneers3d/common/TileData.hpp \
    src/pioneers3d/common/Types.hpp \
    src/pioneers3d/scene/BoardSceneNode.hpp \
    src/pioneers3d/scene/TileSceneNode.hpp \
    src/pioneers3d/main_Pioneers3D.hpp \
    src/pioneers3d/common/eTileType.hpp \
    src/pioneers3d/common/eGameType.hpp \
    src/pioneers3d/common/eTextureType.hpp

SOURCES += \
	src/main.cpp \
	src/common/Camera.cpp \
	src/common/createCircleMeshBuffer.cpp \
	src/common/createHexagonMeshBuffer.cpp \
	src/common/createImage.cpp \
	src/common/createMesh.cpp \
	src/common/createMeshBuffer.cpp \
	src/common/createTexture.cpp \
	src/common/loadImage.cpp \
	src/common/Types.cpp \
	src/common/Utils.cpp \
	src/common/TextureManager.cpp \
	src/common/AutoMeshBuffer.cpp \
	src/common/AutoSceneNode.cpp \
	src/common/createDevice.cpp \
    src/pioneers3d/common/BoardData.cpp \
    src/pioneers3d/common/PlayerData.cpp \
    src/pioneers3d/common/StandardGame.cpp \
    src/pioneers3d/common/TextureData.cpp \
    src/pioneers3d/common/TileData.cpp \
    src/pioneers3d/common/Types.cpp \
    src/pioneers3d/scene/BoardSceneNode.cpp \
    src/pioneers3d/scene/TileSceneNode.cpp \
    src/pioneers3d/main_Pioneers3D.cpp
