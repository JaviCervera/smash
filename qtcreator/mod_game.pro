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
win32:LIBS += -L../src/mod_game/lib/SDL2/win32
mac:LIBS += -L../src/mod_game/lib/SDL2/mac
unix:!mac:LIBS += -L../src/mod_game/lib/SDL2/linux
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
    ../src/mod_game/loadmodule.cpp \
    ../src/mod_game/screen.cpp \
    ../src/mod_game/main.cpp \
    ../src/mod_game/renderer.cpp \
    ../src/mod_core/platform.cpp \
    ../src/mod_game/desktop.cpp \
    ../src/mod_game/pixmap.cpp \
    ../src/mod_game/lib/stb_image.c \
    ../src/mod_game/image.cpp \
    ../src/mod_game/input.cpp \
    ../src/mod_game/sound.cpp \
    ../src/mod_game/channel.cpp \
    ../src/mod_game/music.cpp \
    ../src/mod_game/font.cpp

HEADERS += \ 
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/mod_game/screen.h \
    ../src/mod_game/main.h \
    ../src/mod_game/renderer.h \
    ../src/mod_game/desktop.h \
    ../src/mod_game/pixmap.h \
    ../src/mod_game/image.h \
    ../src/mod_game/input.h \
    ../src/mod_game/sound.h \
    ../src/mod_game/channel.h \
    ../src/mod_game/music.h \
    ../src/mod_game/font.h \
    ../src/mod_game/glyph.h \
    ../src/mod_game/lib/stb_image_write.h \
    ../src/mod_game/lib/stb_truetype.h
