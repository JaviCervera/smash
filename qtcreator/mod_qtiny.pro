#Target info
win32:TARGET = ../../modules/smash.qtiny.win32
mac:TARGET = smash.qtiny.mac
unix:!mac:TARGET = smash.qtiny.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
#CONFIG += staticlib
#To build a shared library, uncomment these lines
CONFIG += shared
DEFINES += BUILD_SHARED
win32:LIBS += -L../src/mod_qtiny/Qt/lib/win32-mingw
mac:LIBS += -L../src/mod_qtiny/Qt/lib/mac
unix:!mac:LIBS += -L../src/mod_qtiny/Qt/lib/linux
LIBS += -lQt5Core -lQt5Gui -lQt5Widgets -lQt5PrintSupport -lQt5PlatformSupport
win32:LIBS +=
mac:LIBS += -lqcocoa -lcocoaprintersupport -lz -framework CoreFoundation -framework Carbon -framework AppKit -framework IOKit -framework OpenGL -lc++
unix:!mac:LIBS +=

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32
win32:QMAKE_LFLAGS += -static-libgcc -static-libstdc++

unix:!mac:QMAKE_POST_LINK = cp "$${OUT_PWD}/libsmash.qtiny.linux.so.1.0.0" "$${OUT_PWD}/../modules/smash.qtiny.linux.so"
mac:QMAKE_POST_LINK += cp "$${OUT_PWD}/libsmash.qtiny.mac.1.0.0.dylib" "$${OUT_PWD}/../modules/smash.qtiny.mac.dylib"

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += ../src/sdk ../src/mod_qtiny/Qt/include ../src/mod_qtiny/Qt/include/QtCore ../src/mod_qtiny/Qt/include/QtGui ../src/mod_qtiny/Qt/include/QtWidgets

SOURCES += \
    ../src/mod_qtiny/loadmodule.cpp \
    ../src/mod_qtiny/widget.cpp \
    ../src/mod_qtiny/window.cpp \
    ../src/mod_qtiny/app.cpp \
    ../src/mod_qtiny/button.cpp \
    ../src/mod_qtiny/event.cpp \
    ../src/mod_qtiny/moc_event.cpp \
    ../src/mod_qtiny/checkbox.cpp \
    ../src/mod_qtiny/requester.cpp \
    ../src/mod_qtiny/combobox.cpp \
    ../src/mod_qtiny/editor.cpp \
    ../src/mod_qtiny/guifont.cpp \
    ../src/mod_qtiny/guiicon.cpp \
    ../src/mod_qtiny/frame.cpp \
    ../src/mod_qtiny/label.cpp \
    ../src/mod_qtiny/lineedit.cpp \
    ../src/mod_qtiny/menu.cpp \
    ../src/mod_qtiny/statusbar.cpp \
    ../src/mod_qtiny/tabbar.cpp \
    ../src/mod_qtiny/toolbar.cpp \
    ../src/mod_qtiny/process.cpp

HEADERS += \ 
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/mod_qtiny/widget.h \
    ../src/mod_qtiny/window.h \
    ../src/mod_qtiny/app.h \
    ../src/mod_qtiny/button.h \
    ../src/mod_qtiny/event.h \
    ../src/mod_qtiny/checkbox.h \
    ../src/mod_qtiny/requester.h \
    ../src/mod_qtiny/combobox.h \
    ../src/mod_qtiny/editor.h \
    ../src/mod_qtiny/guifont.h \
    ../src/mod_qtiny/guiicon.h \
    ../src/mod_qtiny/frame.h \
    ../src/mod_qtiny/label.h \
    ../src/mod_qtiny/lineedit.h \
    ../src/mod_qtiny/menu.h \
    ../src/mod_qtiny/statusbar.h \
    ../src/mod_qtiny/tabbar.h \
    ../src/mod_qtiny/toolbar.h \
    ../src/mod_qtiny/process.h
