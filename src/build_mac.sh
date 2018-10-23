#Build Core module
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/mod_core.pro
make -j4
rm Makefile
rm *.o
rm *.dylib

#Build Game module
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/game.pro
make -j4
rm Makefile
rm *.o
rm *.dylib

#Build Qtiny module
~/Qt/5.1.1/clang_64/bin/moc -oqtiny/moc_event.cpp qtiny/event.h
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/qtiny.pro
make -j4
rm Makefile
rm *.o
rm *.dylib

#Build XML module
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/mod_xml.pro
make -j4
rm Makefile
rm *.o
rm *.dylib

#Build Stub
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/stub.pro
make -j4
rm Makefile
rm *.o

#Build Compiler to generate stub cpp file
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/compiler.pro
make -j4
rm Makefile
rm *.o

#Generate stub cpp file
../bin/smashc.mac -run ../stub/makestub.smash

#Rebuild Compiler with new stub cpp file
~/Qt/5.1.1/clang_64/bin/qmake ../qtcreator/compiler.pro
make -j4
rm Makefile
rm *.o
