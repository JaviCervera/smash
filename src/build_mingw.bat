@echo off

rem Build Core module
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/mod_core.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Game module
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/mod_game.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Qtiny module
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/moc -omod_qtiny/moc_event.cpp mod_qtiny/event.h
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/mod_qtiny.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build XML module
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/mod_xml.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Stub
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/stub.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Stub_Console
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/stub_console.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Compiler to generate stub cpp file
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/compiler.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Generate stub cpp file
../bin/smashc.win32.exe -run ../stub/makestub.smash

rem Rebuild Compiler with new stub cpp file
C:/Qt/Qt5.11.2/5.11.2/mingw53_32/bin/qmake ../qtcreator/compiler.pro
mingw32-make -j4
rmdir /S /Q debug
rmdir /S /Q release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

pause