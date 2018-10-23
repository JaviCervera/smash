#ifndef CORE_CONSOLE_H
#define CORE_CONSOLE_H

#include "string.h"
#include <stdio.h>

class Console {
public:
    static void Print(const String& str) { printf("%s", str.ToCString()); }
    static String Input(const String& prompt);
protected:
    Console() {}
};

inline String Console::Input(const String& prompt) {
    char buffer[1024];
    printf("%s", prompt.ToCString());
    fgets(buffer, 1024, stdin);
    return buffer;
}

#endif // CORE_CONSOLE_H
