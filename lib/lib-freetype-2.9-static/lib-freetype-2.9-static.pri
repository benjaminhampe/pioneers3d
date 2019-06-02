DEFINES += USE_FREETYPE=1

unix:!macx {
   INCLUDEPATH += /usr/include/freetype2
   LIBS += -lfreetype
}
unix:!macx {
   INCLUDEPATH += /usr/include/freetype2
   LIBS += -lfreetype
}
win32 {
   INCLUDEPATH += $$PWD
   INCLUDEPATH += $$PWD/include/freetype2
   LIBS += -L$$PWD/lib
   LIBS += -lfreetype

}

# CONFIG(debug, debug|release) {
# }
# CONFIG(release, debug|release) {
# }

INCLUDEPATH += $$PWD

HEADERS += \
   $$PWD/libFreeType.hpp \
   $$PWD/FT_Utils.hpp

SOURCES += \
   $$PWD/FT_Utils.cpp
