TARGET = stub
TEMPLATE = app
CONFIG -= qt
!win32:CONFIG += console
CONFIG -= app_bundle

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32
win32:QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++

LIBS += -L../src/common
win32:LIBS += -langelscript.win32 -lwinmm
mac:LIBS += -langelscript.mac -framework AppKit
unix:!mac:LIBS += -langelscript.linux -ldl -lpthread

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

win32:RC_FILE += stub.rc

win32:QMAKE_POST_LINK += cp "$${OUT_PWD}/release/stub.exe" "$${OUT_PWD}/../bin/stub.win32"

SOURCES += \ 
    ../src/stub/stub.cpp \
    ../src/sdk/smashsdk.cpp \
    ../src/common/scriptdictionary.cpp \
    ../src/common/scriptarray.cpp \
    ../src/mod_core/platform.cpp \
    ../src/mod_core/library.cpp

HEADERS += \ 
    ../src/mod_core/string.h \
    ../src/mod_core/file.h \
    ../src/common/bytecodestream.h \
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/mod_core/library.h
