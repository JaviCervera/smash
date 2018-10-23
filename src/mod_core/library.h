#ifndef LIBRARY_H
#define LIBRARY_H

#include "../common/refcounter.h"
#include "array.h"
#include "platform.h"
#include "string.h"

class Library : public RefCounter {
public:
    Library(const String& filename) { handle = platform_LoadLibrary(filename); }
    ~Library() { if ( handle ) platform_FreeLibrary(handle); }

    bool IsOpened() const { return handle != 0; }

    void* Function(const String& name) const { return platform_LibraryFunction(handle, name); }

    void PushInt(int val) { PushObject((void*)val); }
    void PushFloat(float val);
    void PushCString(const String& val) { PushObject((void*)val.ToCString()); }
    void PushObject(void* val) { stack.Add(val); }

    void CallVoidFunction(void* func);
    int CallIntFunction(void* func);
    float CallFloatFunction(void* func);
    String CallCStringFunction(void* func);
    void* CallObjectFunction(void* func);
    void CallVoidFunctionC(void* func);
    int CallIntFunctionC(void* func);
    float CallFloatFunctionC(void* func);
    String CallCStringFunctionC(void* func);
    void* CallObjectFunctionC(void* func);
private:
    void* handle;
    Array<void*> stack;
};

inline void Library::PushFloat(float val) {
    void* p = 0;
    memcpy(&p, &val, sizeof(float));
    PushObject(p);
}

#endif // LIBRARY_H
