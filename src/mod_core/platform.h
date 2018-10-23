#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include "array.h"
#include "string.h"

void platform_DirContents(const String& path, Array<String>& arr);
String platform_CurrentDir();
void platform_ChangeDir(const String& path);
void platform_CreateDir(const String& path);
void platform_DeleteDir(const String& path);
int platform_FileType(const String& filename);
unsigned long platform_FileSize(const String& filename);
void platform_DeleteFile(const String& filename);
void* platform_LoadLibrary(const String& libname);
void platform_FreeLibrary(void* lib);
void* platform_LibraryFunction(void* lib, const String& funcname);
unsigned long platform_Millisecs();
void platform_Delay(unsigned long msecs);

#endif // CORE_PLATFORM_H
