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
win32:LIBS += -L../src/qtiny/Qt/lib/win32-mingw
mac:LIBS += -L../src/qtiny/Qt/lib/mac
unix:!mac:LIBS += -L../src/qtiny/Qt/lib/linux
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

INCLUDEPATH += ../src/sdk ../src/qtiny/Qt/include ../src/qtiny/Qt/include/QtCore ../src/qtiny/Qt/include/QtGui ../src/qtiny/Qt/include/QtWidgets

SOURCES += \
    ../src/qtiny/loadmodule.cpp \
    ../src/qtiny/widget.cpp \
    ../src/qtiny/window.cpp \
    ../src/qtiny/app.cpp \
    ../src/qtiny/button.cpp \
    ../src/qtiny/event.cpp \
    ../src/qtiny/moc_event.cpp \
    ../src/qtiny/checkbox.cpp \
    ../src/qtiny/requester.cpp \
    ../src/qtiny/combobox.cpp \
    ../src/qtiny/editor.cpp \
    ../src/qtiny/guifont.cpp \
    ../src/qtiny/guiicon.cpp \
    ../src/qtiny/frame.cpp \
    ../src/qtiny/label.cpp \
    ../src/qtiny/lineedit.cpp \
    ../src/qtiny/menu.cpp \
    ../src/qtiny/statusbar.cpp \
    ../src/qtiny/tabbar.cpp \
    ../src/qtiny/toolbar.cpp \
    ../src/qtiny/process.cpp

HEADERS += \ 
    ../src/sdk/smashsdk.h \
    ../src/sdk/angelscript.h \
    ../src/common/refcounter.h \
    ../src/qtiny/widget.h \
    ../src/qtiny/window.h \
    ../src/qtiny/app.h \
    ../src/qtiny/button.h \
    ../src/qtiny/event.h \
    ../src/qtiny/checkbox.h \
    ../src/qtiny/requester.h \
    ../src/qtiny/combobox.h \
    ../src/qtiny/editor.h \
    ../src/qtiny/guifont.h \
    ../src/qtiny/guiicon.h \
    ../src/qtiny/frame.h \
    ../src/qtiny/label.h \
    ../src/qtiny/lineedit.h \
    ../src/qtiny/menu.h \
    ../src/qtiny/statusbar.h \
    ../src/qtiny/tabbar.h \
    ../src/qtiny/toolbar.h \
    ../src/qtiny/process.h
