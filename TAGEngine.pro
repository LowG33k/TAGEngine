TEMPLATE = lib

CONFIG -= qt
#CONFIG += dll
CONFIG += staticlib

OBJECTS_DIR = tmp/TAGEngine

TARGET = TAGEngine-s
#TARGET = TAGEngine
DESTDIR = lib

DEFINES += TAG_STATIC
#DEFINES += TAG_EXPORT
DEFINES += SFML_STATIC

#LIBS += -L"extlibs/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
LIBS += -L"extlibs/lib" -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d

DEPENDPATH += ./src/TAG
DEPENDPATH += ./src/TAG/Debug
DEPENDPATH += ./src/TAG/Core
DEPENDPATH += ./src/TAG/Utilities
DEPENDPATH += ./include/TAG
DEPENDPATH += ./include/TAG/Config
DEPENDPATH += ./include/TAG/Core
DEPENDPATH += ./include/TAG/Debug
DEPENDPATH += ./include/TAG/Utilities

INCLUDEPATH += ./include
INCLUDEPATH += ./include/TAG
INCLUDEPATH += ./include/TAG/Config
INCLUDEPATH += ./include/TAG/Core
INCLUDEPATH += ./include/TAG/Debug
INCLUDEPATH += ./include/TAG/Utilities

INCLUDEPATH += ./extlibs

# HEADERS
HEADERS += Config.hpp \
    include/TAG/Debug/MemoryDebugOff.hpp
HEADERS += Singleton.hpp
HEADERS += TAGApplication.hpp
HEADERS += MemoryManager.hpp
HEADERS += MemoryDebug.hpp
HEADERS += MemoryDebugOff.hpp
HEADERS += LoggerFile.hpp
HEADERS += LoggerConsole.hpp
HEADERS += ILogger.hpp
HEADERS += Date.hpp
HEADERS += Time.hpp
HEADERS += String.hpp
HEADERS += Functor.hpp
HEADERS += Console.hpp

# TEMPLATES
HEADERS += Functor.inl
HEADERS += String.inl

# SOURCES
SOURCES += TAGApplication.cpp
SOURCES += MemoryManager.cpp
SOURCES += LoggerFile.cpp
SOURCES += LoggerConsole.cpp
SOURCES += ILogger.cpp
SOURCES += Date.cpp
SOURCES += Time.cpp
SOURCES += Console.cpp

