#ifndef CORE_DIR_H
#define CORE_DIR_H

#include "../common/refcounter.h"
#include "array.h"
#include "platform.h"
#include "string.h"

class Dir : public RefCounter {
public:
    Dir(const String& path) : current(0) { platform_DirContents(path, contents); }

    bool HasNext() const { return current != contents.Size(); }
    const String& Next() { return contents[current++]; }

    static String Current() { return platform_CurrentDir(); }
    static void Change(const String& path) { platform_ChangeDir(path); }
    static void Create(const String& path) { platform_CreateDir(path); }
    static void Delete(const String& path) { platform_DeleteDir(path); }
private:
    Array<String> contents;
    int current;
};

#endif // CORE_DIR_H
