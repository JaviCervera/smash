win32:TARGET = ../../bin/smashc.win32
mac:TARGET = ../bin/smashc.mac
unix:!mac:TARGET = ../bin/smashc.linux
TEMPLATE = app
CONFIG -= qt
win32:CONFIG += console
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

SOURCES += \ 
    ../src/compiler/scriptbuilder.cpp \
    ../src/compiler/compiler.cpp \
    ../src/sdk/smashsdk.cpp \
	../src/mod_core/library.cpp \
	../src/mod_core/platform.cpp \
	../src/mod_core/system.cpp \
    ../src/compiler/icon.mac.cpp \
    ../src/common/scriptarray.cpp \
    ../src/common/scriptdictionary.cpp

HEADERS += \ 
	../src/mod_core/file.h \
	../src/mod_core/console.h \
	../src/mod_core/string.h \
    ../src/compiler/scriptbuilder.h \
    ../src/sdk/smashsdk.h \
	../src/mod_core/library.h \
	../src/mod_core/dir.h \
	../src/mod_core/time.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/common/bytecodestream.h \
	../src/mod_core/system.h \
    ../src/common/scriptarray.h \
    ../src/common/scriptdictionary.h

