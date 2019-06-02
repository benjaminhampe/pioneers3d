INCLUDEPATH += $$PWD

HEADERS +=   \
   $$PWD/de/hampe/common/PerfTimer.hpp \
   $$PWD/de/hampe/common/StringUtil.hpp \
   $$PWD/de/hampe/common/Types.hpp \
   $$PWD/de/hampe/common/image/Color.hpp \
   $$PWD/de/hampe/common/image/ColorFormat.hpp \
   $$PWD/de/hampe/common/image/Image.hpp \
   $$PWD/de/hampe/common/image/Types.hpp \
   $$PWD/de/hampe/common/logging/LogLevel.hpp \
   $$PWD/de/hampe/common/logging/Logger.hpp \
   $$PWD/de/hampe/common/logging/StdOutLogger.hpp \
   $$PWD/de/hampe/common/logging/Types.hpp \
   $$PWD/de/hampe/common/math/Types.hpp \
   $$PWD/de/hampe/common/math/sinCosTable.hpp \
   $$PWD/de/hampe/common/os/FileFinderSTL.hpp \
   $$PWD/de/hampe/common/os/FileMagic.hpp \
   $$PWD/de/hampe/common/os/FileSystemSTL.hpp \
   $$PWD/de/hampe/common/os/FileType.hpp \
   $$PWD/de/hampe/common/os/Types.hpp \
   $$PWD/de/hampe/common/ostreamGLM.hpp \
   $$PWD/de/hampe/common/sprintf.hpp
SOURCES +=   \
   $$PWD/de/hampe/common/PerfTimer.cpp \
   $$PWD/de/hampe/common/StringUtil.cpp \
   $$PWD/de/hampe/common/image/Color.cpp \
   $$PWD/de/hampe/common/image/Image.cpp \
   $$PWD/de/hampe/common/logging/StdOutLogger.cpp \
   $$PWD/de/hampe/common/os/FileFinderSTL.cpp \
   $$PWD/de/hampe/common/os/FileMagic.cpp \
   $$PWD/de/hampe/common/os/FileSystemSTL.cpp \
   $$PWD/de/hampe/common/os/FileType.cpp

LIBS += -lstdc++fs
