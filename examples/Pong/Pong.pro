TEMPLATE = app

CONFIG -= qt

CONFIG += console

OBJECTS_DIR = tmp

TARGET = pong
DESTDIR = ../../bin

DEFINES += TAG_STATIC
DEFINES += SFML_STATIC

#LIBS += -L"../../lib" -lTAGEngine
#LIBS += -L"../../extlibs/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
LIBS += -L"../../lib" -lTAGEngine-s
LIBS += -L"../../extlibs/lib" -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d

INCLUDEPATH += ../../extlibs
INCLUDEPATH += .
INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/TAG
INCLUDEPATH += ../../include/TAG/Config
INCLUDEPATH += ../../include/TAG/Core
INCLUDEPATH += ../../include/TAG/Debug
INCLUDEPATH += ../../include/TAG/Utilities


SOURCES += main.cpp
SOURCES += PongApplication.cpp
HEADERS += PongApplication.hpp
