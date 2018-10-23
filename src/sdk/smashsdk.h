#ifndef SMASHSDK_H
#define SMASHSDK_H

#include "angelscript.h"
#include "../mod_core/array.h"
#include "../mod_core/string.h"

#ifdef _WIN32
#define SDKFUNC __declspec(dllexport)
#else
#define SDKFUNC
#endif

typedef void (*EntryPointFunc)();

class SmashSDK {
public:
    // API registration
    void RegisterFunction(const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall = NULL) { registerFunction(this, decl, ptr, callConv, objForThisCall); }
    void RegisterGlobal(const char* decl, void* ptr) { registerGlobal(this, decl, ptr); }
    void RegisterClass(const char* name, int size, asDWORD flags) { registerClass(this, name, size, flags); }
    void RegisterMethod(const char* className, const char* decl, const asSFuncPtr& ptr, asDWORD callConv) { registerMethod(this, className, decl, ptr, callConv); }
    void RegisterProperty(const char* className, const char* decl, int offset) { registerProperty(this, className, decl, offset); }
    void RegisterBehaviour(const char* className, asEBehaviours behaviour, const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThiscall = NULL) { registerBehaviour(this, className, behaviour, decl, ptr, callConv, objForThiscall); }
    void RegisterInterface(const char* name) { registerInterface(this, name); }
    void RegisterInterfaceMethod(const char* interfaceName, const char* decl) { registerInterfaceMethod(this, interfaceName, decl); }
    void RegisterStringFactory(const char* className, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall = NULL) { registerStringFactory(this, className, ptr, callConv, objForThisCall); }
    void RegisterDefaultTypes() { registerDefaultTypes(this); }

    // Type conversions
    asIObjectType* ScriptType(const char* typeName) { return scriptType(this, typeName); }
    void* ArrayToScriptArray(const Array<void*>& array, asIObjectType* arrayType) { return arrayToScriptArray(this, array, arrayType); }
    void* StringArrayToScriptArray(const Array<String>& array) { return stringArrayToScriptArray(this, array); }

    // Module-driven runtime
    void SetEntryPoint(EntryPointFunc ep) { return setEntryPoint(this, ep); }
    EntryPointFunc EntryPoint() { return entryPoint; }
    asIScriptFunction* ScriptFunction(const char* decl) { return scriptFunction(this, decl); }
    asIScriptFunction* ScriptMethod(asIObjectType* type, const char* decl) { return scriptMethod(this, type, decl); }
    void PrepareScriptFunction(asIScriptFunction* func) { return prepareScriptFunction(this, func); }
    void SetScriptThis(asIScriptObject* object) { setScriptThis(this, object); }
    void SetArgInt(unsigned int index, int value) { setArgInt(this, index, value); }
    void SetArgAddress(unsigned int index, void* address) { setArgAddress(this, index, address); }
    int ExecuteContext() { return executeContext(this); }
    void AbortContext(int code) { abortContext(this); abortCode = code; }
    int AbortCode() { return abortCode; }
    asIScriptObject* CreateScriptObject(asIObjectType* type, const char* factory) { return createScriptObject(this, type, factory); }

    // Scripting engine
    asIScriptEngine* Engine() { return engine; }
    asIScriptContext* Context() { return context; }

    // Argument passing
    int GetArgC() { return argc; }
    const char** GetArgV() { return argv; }

    // Error handling
    void Error(const char* msg) { return error(this, msg); }
protected:
    SmashSDK() : entryPoint(NULL), abortCode(0) {}
    virtual ~SmashSDK() {}

    int (*getArgC)(SmashSDK*);
    const char** (*getArgV)(SmashSDK*);
    void (*registerFunction)(SmashSDK*, const char*, const asSFuncPtr&, asDWORD, void*);
    void (*registerGlobal)(SmashSDK*, const char*, void*);
    void (*registerClass)(SmashSDK*, const char*, int, asDWORD);
    void (*registerMethod)(SmashSDK*, const char*, const char*, const asSFuncPtr&, asDWORD);
    void (*registerProperty)(SmashSDK*, const char*, const char*, int);
    void (*registerBehaviour)(SmashSDK*, const char*, asEBehaviours, const char*, const asSFuncPtr&, asDWORD, void*);
    void (*registerInterface)(SmashSDK*, const char*);
    void (*registerInterfaceMethod)(SmashSDK*, const char*, const char*);
    void (*registerStringFactory)(SmashSDK*, const char*, const asSFuncPtr&, asDWORD, void*);
    void (*registerDefaultTypes)(SmashSDK*);
    asIObjectType* (*scriptType)(SmashSDK*, const char*);
    void* (*arrayToScriptArray)(SmashSDK*, const Array<void*>&, asIObjectType*);
    void* (*stringArrayToScriptArray)(SmashSDK*, const Array<String>&);
    void (*setEntryPoint)(SmashSDK*, EntryPointFunc);
    asIScriptFunction* (*scriptFunction)(SmashSDK*, const char*);
    asIScriptFunction* (*scriptMethod)(SmashSDK*, asIObjectType*, const char*);
    void (*prepareScriptFunction)(SmashSDK*, asIScriptFunction*);
    void (*setScriptThis)(SmashSDK*, asIScriptObject*);
    void (*setArgInt)(SmashSDK*, unsigned int, int);
    void (*setArgAddress)(SmashSDK*, unsigned int, void*);
    int (*executeContext)(SmashSDK*);
    void (*abortContext)(SmashSDK*);
    asIScriptObject* (*createScriptObject)(SmashSDK*, asIObjectType*, const char*);
    void (*error)(SmashSDK*, const char*);

    asIScriptEngine* engine;
    asIScriptContext* context;
    int argc;
    const char** argv;

    EntryPointFunc entryPoint;
    int abortCode;
};

#endif // SMASHSDK_H
