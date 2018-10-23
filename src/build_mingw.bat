@echo off

rem Build Core module
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/core.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Game module
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/game.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Qtiny module
C:/Qt/5.1.1/mingw48_32/bin/moc -oqtiny/moc_event.cpp qtiny/event.h
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/qtiny.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build XML module
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/xml.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Stub
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/stub.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Stub_Console
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/stub_console.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Build Compiler to generate stub cpp file
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/compiler.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

rem Generate stub cpp file
../bin/smashc.win32.exe -run ../stub/makestub.smash

rem Rebuild Compiler with new stub cpp file
C:/Qt/5.1.1/mingw48_32/bin/qmake ../qtcreator/compiler.pro
mingw32-make -j4
rmdir debug
rmdir release
del Makefile
del Makefile.Debug
del Makefile.Release
del *.o
del *.dll

pause