#Target info
win32:TARGET = ../../modules/smash.core.win32
mac:TARGET = smash.core.mac
unix:!mac:TARGET = smash.core.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
#CONFIG += staticlib
#To build a shared library, uncomment these lines
CONFIG += shared
DEFINES += BUILD_SHARED
win32:LIBS += -lwinmm
mac:LIBS += -framework AppKit
unix:!mac:LIBS += -ldl -lpthread

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32
win32:QMAKE_LFLAGS += -static-libgcc -static-libstdc++

unix:!mac:QMAKE_POST_LINK = cp "$${OUT_PWD}/libsmash.core.linux.so.1.0.0" "$${OUT_PWD}/../modules/smash.core.linux.so"
mac:QMAKE_POST_LINK += cp "$${OUT_PWD}/libsmash.core.mac.1.0.0.dylib" "$${OUT_PWD}/../modules/smash.core.mac.dylib"

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += ../src/sdk

SOURCES += \ 
    ../src/mod_core/system.cpp \
    ../src/mod_core/platform.cpp \
    ../src/mod_core/library.cpp \
    ../src/mod_core/loadmodule.cpp

HEADERS += \ 
    ../src/mod_core/time.h \
    ../src/mod_core/system.h \
    ../src/mod_core/string.h \
    ../src/mod_core/platform.h \
    ../src/mod_core/membuffer.h \
    ../src/mod_core/math.h \
    ../src/mod_core/main.h \
    ../src/mod_core/list.h \
    ../src/mod_core/library.h \
    ../src/mod_core/file.h \
    ../src/mod_core/dir.h \
    ../src/mod_core/dictionary.h \
    ../src/mod_core/console.h \
    ../src/mod_core/array.h \
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h
