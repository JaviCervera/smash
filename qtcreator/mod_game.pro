#Target info
win32:TARGET = ../../modules/smash.game.win32
mac:TARGET = smash.game.mac
unix:!mac:TARGET = smash.game.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
#CONFIG += staticlib
#To build a shared library, uncomment these lines
CONFIG += shared
DEFINES += BUILD_SHARED
win32:LIBS += -L../src/game/lib/SDL2/win32
mac:LIBS += -L../src/game/lib/SDL2/mac
unix:!mac:LIBS += -L../src/game/lib/SDL2/linux
LIBS += -lSDL2_mixer -lSDL2 -lvorbisfile -lvorbis -logg
win32:LIBS += -lwinmm -lopengl32 -lgdi32 -lole32 -loleaut32 -luuid -limm32 -lversion
mac:LIBS += -framework AppKit -framework AudioUnit -framework Carbon -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL
unix:!mac:LIBS += -lrt -ldl -lpthread

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32
win32:QMAKE_LFLAGS += -static-libgcc -static-libstdc++

unix:!mac:QMAKE_POST_LINK += cp "$${OUT_PWD}/libsmash.game.linux.so.1.0.0" "$${OUT_PWD}/../modules/smash.game.linux.so"
mac:QMAKE_POST_LINK += cp "$${OUT_PWD}/libsmash.game.mac.1.0.0.dylib" "$${OUT_PWD}/../modules/smash.game.mac.dylib"

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += ../src/sdk

SOURCES += \ 
    ../src/game/loadmodule.cpp \
    ../src/game/screen.cpp \
    ../src/game/main.cpp \
    ../src/game/renderer.cpp \
    ../src/core/platform.cpp \
    ../src/game/desktop.cpp \
    ../src/game/pixmap.cpp \
    ../src/game/lib/stb_image.c \
    ../src/game/image.cpp \
    ../src/game/input.cpp \
    ../src/game/sound.cpp \
    ../src/game/channel.cpp \
    ../src/game/music.cpp \
    ../src/game/font.cpp

HEADERS += \ 
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/game/screen.h \
    ../src/game/main.h \
    ../src/game/renderer.h \
    ../src/game/desktop.h \
    ../src/game/pixmap.h \
    ../src/game/image.h \
    ../src/game/input.h \
    ../src/game/sound.h \
    ../src/game/channel.h \
    ../src/game/music.h \
    ../src/game/font.h \
    ../src/game/glyph.h \
    ../src/game/lib/stb_image_write.h \
    ../src/game/lib/stb_truetype.h
