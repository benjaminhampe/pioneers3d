INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include/freetype2
DEFINES += USE_FREETYPE=1
LIBS += -L$$PWD/lib
CONFIG(debug, debug|release) {
	LIBS += -lfreetype
}
CONFIG(release, debug|release) {
	LIBS += -lfreetype
}

HEADERS += \
	$$PWD/libFreeType.hpp \
	$$PWD/FT_Utils.hpp

SOURCES += \
	$$PWD/FT_Utils.cpp
