#Target info
win32:TARGET = ../../modules/smash.xml.win32
mac:TARGET = smash.xml.mac
unix:!mac:TARGET = smash.xml.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
#CONFIG += staticlib
#To build a shared library, uncomment these lines
CONFIG += shared
DEFINES += BUILD_SHARED
#win32:LIBS += -lwinmm
#mac:LIBS += -framework AppKit
#unix:!mac:LIBS += -ldl -lpthread

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32
win32:QMAKE_LFLAGS += -static-libgcc -static-libstdc++

unix:!mac:QMAKE_POST_LINK = cp "$${OUT_PWD}/libsmash.xml.linux.so.1.0.0" "$${OUT_PWD}/../modules/smash.xml.linux.so"
mac:QMAKE_POST_LINK += cp "$${OUT_PWD}/libsmash.xml.mac.1.0.0.dylib" "$${OUT_PWD}/../modules/smash.xml.mac.dylib"

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += ../src/sdk

SOURCES += \
    ../src/mod_xml/loadmodule.cpp

HEADERS += \ 
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/mod_xml/rapidxml.hpp \
    ../src/mod_core/string.h \
    ../src/mod_core/array.h
