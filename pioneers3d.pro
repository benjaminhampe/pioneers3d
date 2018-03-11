TARGET = Pioneers3D
TEMPLATE = app
CONFIG += console c++14
QT += core gui widgets

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

include ( lib/lib-irrlicht-1.8.4/lib-irrlicht-1.8.4-mingw530.pri )
include ( lib/lib-tinyxml2/lib-tinyxml2.pri )

INCLUDEPATH += $$PWD/src
HEADERS	+= \
	src/pioneers3d/data/BoardData.hpp \
	src/pioneers3d/data/GameData.hpp \
	src/pioneers3d/data/PlayerData.hpp \
	src/pioneers3d/data/TextureType.hpp \
	src/pioneers3d/data/TileData.hpp \
	src/pioneers3d/data/TileType.hpp \
	src/pioneers3d/image/createImage.hpp \
	src/pioneers3d/image/createImageErz.hpp \
	src/pioneers3d/image/createImageHolz.hpp \
	src/pioneers3d/image/createImageLehm.hpp \
	src/pioneers3d/image/createImageSchaf.hpp \
	src/pioneers3d/image/createImageWasser.hpp \
	src/pioneers3d/image/createImageWeizen.hpp \
	src/pioneers3d/image/createTextureFromImage.hpp \
	src/pioneers3d/image/createTileImage.hpp \
	src/pioneers3d/image/createTileTexture.hpp \
	src/pioneers3d/scene/BoardSceneNode.hpp \
	src/pioneers3d/scene/Camera.hpp \
	src/pioneers3d/scene/createCircleMeshBufferXY.hpp \
	src/pioneers3d/scene/createCircleMeshBufferXZ.hpp \
	src/pioneers3d/scene/createHexagonMeshBufferXZ.hpp \
	src/pioneers3d/scene/createMesh.hpp \
	src/pioneers3d/scene/createMeshBuffer.hpp \
	src/pioneers3d/Types.hpp \
	src/pioneers3d/Pioneers3DApplication.hpp
SOURCES += \
	src/pioneers3d/data/BoardData.cpp \
	src/pioneers3d/data/GameData.cpp \
	src/pioneers3d/data/PlayerData.cpp \
	src/pioneers3d/data/TextureType.cpp \
	src/pioneers3d/data/TileData.cpp \
	src/pioneers3d/data/TileType.cpp \
	src/pioneers3d/image/createImage.cpp \
	src/pioneers3d/image/createImageErz.cpp \
	src/pioneers3d/image/createImageHolz.cpp \
	src/pioneers3d/image/createImageLehm.cpp \
	src/pioneers3d/image/createImageSchaf.cpp \
	src/pioneers3d/image/createImageWasser.cpp \
	src/pioneers3d/image/createImageWeizen.cpp \
	src/pioneers3d/image/createTextureFromImage.cpp \
	src/pioneers3d/image/createTileImage.cpp \
	src/pioneers3d/image/createTileTexture.cpp \
	src/pioneers3d/scene/BoardSceneNode.cpp \
	src/pioneers3d/scene/Camera.cpp \
	src/pioneers3d/scene/createCircleMeshBufferXY.cpp \
	src/pioneers3d/scene/createCircleMeshBufferXZ.cpp \
	src/pioneers3d/scene/createHexagonMeshBufferXZ.cpp \
	src/pioneers3d/scene/createMesh.cpp \
	src/pioneers3d/scene/createMeshBuffer.cpp \
	src/pioneers3d/Types.cpp \
	src/pioneers3d/Pioneers3DApplication.cpp \
	src/main.cpp \
	src/pioneers3d/main_Pioneers3D.cpp
