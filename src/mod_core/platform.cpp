#include "platform.h"
#include "file.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#undef UNICODE
#endif

#ifndef _MSC_VER
#include <dirent.h>
#include <unistd.h>
#define _getcwd getcwd
#define _chdir chdir
#define _rmdir rmdir
#else
#include <direct.h>
#include "dirent.h"
#undef CopyFile
#undef DeleteFile
#endif

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#include <dlfcn.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#elif defined(__linux__)
#include <dlfcn.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#endif

#ifndef _WIN32
static String _StripMangling(String str);
#endif

void platform_DirContents(const String& path, Array<String>& arr) {
    // Open directory
    DIR* d = (DIR*)opendir(path.ToCString());
    if ( d == NULL ) return;

    // Copy directory contents
    struct dirent* entry;
    while ( (entry = (struct dirent*)readdir(d)) ) {
        arr.Add(entry->d_name);
    }

    // Close directory
    closedir(d);
}

String platform_CurrentDir() {
    char buf[FILENAME_MAX];
    _getcwd(buf, FILENAME_MAX);
    return String(buf);
}

void platform_ChangeDir(const String& path) {
    _chdir(path.ToCString());
}

void platform_CreateDir(const String& path) {
#ifdef _WIN32
    //_mkdir(path.ToCString());
    mkdir(path.ToCString());
#else
    mkdir(path.ToCString(), S_IRWXU | S_IRGRP | S_IXGRP);
#endif
}

void platform_DeleteDir(const String& path) {
    _rmdir(path.ToCString());
}

int platform_FileType(const String& filename) {
    struct stat statbuf;
    if ( stat(filename.ToCString(), &statbuf) == -1 )
        return FILETYPE_NONE;
    else if ( S_ISDIR(statbuf.st_mode) )
        return FILETYPE_DIR;
    else
        return FILETYPE_FILE;
}

unsigned long platform_FileSize(const String& filename) {
    struct stat statbuf;
    if ( stat(filename.ToCString(), &statbuf) == -1 )
        return -1;   // Does not exist
    else
        return statbuf.st_size;
}

void platform_DeleteFile(const String& filename) {
    remove(filename.ToCString());
}

void* platform_LoadLibrary(const String& libname) {
#if defined(_WIN32)
    return (void*)LoadLibrary((libname + ".dll").ToCString());
#elif defined(__APPLE__)
    return dlopen((libname + ".dylib").ToCString(), RTLD_LAZY); // 101
#elif defined(__linux__)
    return dlopen((libname + ".so").ToCString(), RTLD_LAZY);
#endif
}

void platform_FreeLibrary(void* lib) {
#if defined(_WIN32)
    FreeLibrary((HMODULE)lib);
#else
    dlclose(lib);
#endif
}

void* platform_LibraryFunction(void* lib, const String& funcname) {
#if defined(_WIN32)
    return (void*)GetProcAddress((HMODULE)lib, funcname.ToCString());
#else
    return dlsym(lib, _StripMangling(funcname).ToCString());
#endif
}

unsigned long platform_Millisecs() {
#if defined(_WIN32)
    return timeGetTime();
#elif defined(__linux__)
    static long basetime = -1;
    long t;
    struct timeval tv;
    gettimeofday(&tv, 0);
    t = tv.tv_sec * 1000;
    t += tv.tv_usec / 1000;
    if ( basetime == -1 ) {
        struct sysinfo info;
        sysinfo(&info);
        basetime = t - info.uptime * 1000;
    }
    return t - basetime;
#elif defined(__APPLE__)
    double t;
    UnsignedWide uw;
    Microseconds( &uw );
    t=(uw.hi<<(32-9))|(uw.lo>>9);
    return t/(1000.0/512.0);
#endif
}

void platform_Delay(unsigned long msecs) {
#if defined(_WIN32)
    Sleep(msecs);
#else
    struct timespec req;
    memset(&req, 0, sizeof(struct timespec));
    req.tv_sec = 0;
    req.tv_nsec = msecs * 1000000L;
    nanosleep(&req, (struct timespec*)0);
#endif
}

#ifndef _WIN32
String _StripMangling(String str) {
    Array<String> arr = str.Split("@");
    str = arr[0];
    if ( str.Left(1) == "_" ) str = str.Right(str.Length() - 1);
    return str;
}
#endif
