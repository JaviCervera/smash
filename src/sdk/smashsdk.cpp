#include "smashsdk.h"
#include "../mod_core/string.h"
#include "../common/scriptarray.h"
#include "../common/scriptdictionary.h"

static void RegisterFunction(SmashSDK* sdk, const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall);
static void RegisterGlobal(SmashSDK* sdk, const char* decl, void* ptr);
static void RegisterClass(SmashSDK* sdk, const char* name, int size, asDWORD flags);
static void RegisterMethod(SmashSDK* sdk, const char* className, const char* decl, const asSFuncPtr& ptr, asDWORD callConv);
static void RegisterProperty(SmashSDK* sdk, const char* className, const char* decl, int offset);
static void RegisterBehaviour(SmashSDK* sdk, const char* className, asEBehaviours behaviour, const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThiscall);
static void RegisterInterface(SmashSDK* sdk, const char* name);
static void RegisterInterfaceMethod(SmashSDK* sdk, const char* interfaceName, const char* decl);
static void RegisterStringFactory(SmashSDK* sdk, const char* className, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall);
static void RegisterDefaultTypes(SmashSDK* sdk);
static asIObjectType* ScriptType(SmashSDK* sdk, const char* typeName);
static void* ArrayToScriptArray(SmashSDK* sdk, const Array<void*>& array, asIObjectType* arrayType);
static void* StringArrayToScriptArray(SmashSDK* sdk, const Array<String>& array);
static void SetEntryPoint(SmashSDK* sdk, EntryPointFunc entryPoint);
static asIScriptFunction* ScriptFunction(SmashSDK* sdk, const char* decl);
static asIScriptFunction* ScriptMethod(SmashSDK* sdk, asIObjectType* type, const char* decl);
static void PrepareScriptFunction(SmashSDK* sdk, asIScriptFunction* func);
static void SetScriptThis(SmashSDK* sdk, asIScriptObject* object);
static void SetArgInt(SmashSDK* sdk, unsigned int index, int value);
static void SetArgAddress(SmashSDK* sdk, unsigned int index, void* address);
static int ExecuteContext(SmashSDK* sdk);
static void AbortContext(SmashSDK* sdk);
static asIScriptObject* CreateScriptObject(SmashSDK* sdk, asIObjectType* type, const char* factory);
static void Error(SmashSDK* sdk, const char* msg);

static asIObjectType* stringArrayType = NULL;

class ImplSmashSDK : public SmashSDK {
public:
    ImplSmashSDK(asIScriptEngine* engine, asIScriptContext* context, int argc, const char** argv) {
        this->engine = engine;
        this->context = context;
        this->argc = argc;
        this->argv = argv;
        registerFunction = ::RegisterFunction;
        registerGlobal = ::RegisterGlobal;
        registerClass = ::RegisterClass;
        registerMethod = ::RegisterMethod;
        registerProperty = ::RegisterProperty;
        registerBehaviour = ::RegisterBehaviour;
        registerInterface = ::RegisterInterface;
        registerInterfaceMethod = ::RegisterInterfaceMethod;
        registerStringFactory = ::RegisterStringFactory;
        registerDefaultTypes = ::RegisterDefaultTypes;
        scriptType = ::ScriptType;
        arrayToScriptArray = ::ArrayToScriptArray;
        stringArrayToScriptArray = ::StringArrayToScriptArray;
        setEntryPoint = ::SetEntryPoint;
        scriptFunction = ::ScriptFunction;
        scriptMethod = ::ScriptMethod;
        prepareScriptFunction = ::PrepareScriptFunction;
        setScriptThis = ::SetScriptThis;
        setArgInt = ::SetArgInt;
        setArgAddress = ::SetArgAddress;
        executeContext = ::ExecuteContext;
        abortContext = ::AbortContext;
        createScriptObject = ::CreateScriptObject;
        error = ::Error;
    }

    void SetEntryPointImpl(EntryPointFunc ep) { entryPoint = ep; }
};

SmashSDK* CreateSDK(asIScriptEngine* engine, asIScriptContext* context, int argc, const char** argv) {
    return new ImplSmashSDK(engine, context, argc, argv);
}

static String StringFactory(unsigned int length, const char* s) {
    (void)length;
    return String(s);
}

static void StringConstructor(String* thisp) {
    new(thisp) String;
}

static void StringConstructor2(String* thisp, unsigned int length, char c) {
    new(thisp) String(length, c);
}

static void StringCopy(String* thisp, const String& other) {
    new(thisp) String(other);
}

static void StringDestructor(String* thisp) {
    thisp->~String();
}

static String& StringAssign(String* thisp, const String& other) {
    return (*thisp) = other;
}

static String& StringAddAssign(String* thisp, const String& other) {
    return (*thisp) += other;
}

static bool StringEquals(String* thisp, const String& other) {
    return (*thisp) == other;
}

static int StringCmp(String* thisp, const String& other) {
    if ( (*thisp) < other )
        return -1;
    else if ( (*thisp) > other )
        return 1;
    else
        return 0;
}

static String StringAdd(String* thisp, const String& other) {
    return (*thisp) + other;
}

static CScriptArray* SplitString(const String& str, const String& delim) {
    return (CScriptArray*)StringArrayToScriptArray(NULL, str.Split(delim));
}

static void RegisterFunction(SmashSDK* sdk, const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall) {
    sdk->Engine()->RegisterGlobalFunction(decl, ptr, callConv, objForThisCall);
}

static void RegisterGlobal(SmashSDK* sdk, const char* decl, void* ptr) {
    sdk->Engine()->RegisterGlobalProperty(decl, ptr);
}

static void RegisterClass(SmashSDK* sdk, const char* name, int size, asDWORD flags) {
    sdk->Engine()->RegisterObjectType(name, size, flags);
}

static void RegisterMethod(SmashSDK* sdk, const char* className, const char* decl, const asSFuncPtr& ptr, asDWORD callConv) {
    sdk->Engine()->RegisterObjectMethod(className, decl, ptr, callConv);
}

static void RegisterProperty(SmashSDK* sdk, const char* className, const char* decl, int offset) {
    sdk->Engine()->RegisterObjectProperty(className, decl, offset);
}

static void RegisterBehaviour(SmashSDK* sdk, const char* className, asEBehaviours behaviour, const char* decl, const asSFuncPtr& ptr, asDWORD callConv, void* objForThiscall) {
    sdk->Engine()->RegisterObjectBehaviour(className, behaviour, decl, ptr, callConv, objForThiscall);
}

static void RegisterInterface(SmashSDK* sdk, const char* name) {
    sdk->Engine()->RegisterInterface(name);
}

static void RegisterInterfaceMethod(SmashSDK* sdk, const char* interfaceName, const char* decl) {
    sdk->Engine()->RegisterInterfaceMethod(interfaceName, decl);
}

static void RegisterStringFactory(SmashSDK* sdk, const char* className, const asSFuncPtr& ptr, asDWORD callConv, void* objForThisCall) {
    sdk->Engine()->RegisterStringFactory(className, ptr, callConv, objForThisCall);
}

static void RegisterDefaultTypes(SmashSDK* sdk) {
    // Register String class
    sdk->RegisterClass("String", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

    // Register Array class and methods
    RegisterScriptArray(sdk->Engine(), true);

    // Register String methods (requires Array to be registered)
    sdk->RegisterStringFactory("String", asFUNCTION(StringFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("String", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(StringConstructor), asCALL_CDECL_OBJFIRST);
    sdk->RegisterBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION(StringCopy), asCALL_CDECL_OBJFIRST);
    sdk->RegisterBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint, uint8)", asFUNCTION(StringConstructor2), asCALL_CDECL_OBJFIRST);
    sdk->RegisterBehaviour("String", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(StringDestructor), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "String &opAssign(const String &in)", asFUNCTION(StringAssign), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "String &opAddAssign(const String &in)", asFUNCTION(StringAddAssign), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "bool opEquals(const String &in) const", asFUNCTION(StringEquals), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "int opCmp(const String &in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "String opAdd(const String &in) const", asFUNCTION(StringAdd), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("String", "int Length() const", asMETHOD(String, Length), asCALL_THISCALL);
    sdk->RegisterFunction("String Str(int)", asFUNCTION(String::FromInt), asCALL_CDECL);
    sdk->RegisterFunction("String Hex(int)", asFUNCTION(String::HexFromInt), asCALL_CDECL);
    sdk->RegisterFunction("String Str(float)", asFUNCTION(String::FromFloat), asCALL_CDECL);
    sdk->RegisterMethod("String", "int ToInt() const", asMETHOD(String, ToInt), asCALL_THISCALL);
    sdk->RegisterMethod("String", "float ToFloat() const", asMETHOD(String, ToFloat), asCALL_THISCALL);
    sdk->RegisterFunction("String Chr(uint8)", asFUNCTION(String::Chr), asCALL_CDECL);
    sdk->RegisterMethod("String", "uint8 Asc() const", asMETHOD(String, Asc), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Left(int) const", asMETHOD(String, Left), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Right(int) const", asMETHOD(String, Right), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Mid(int, int) const", asMETHOD(String, Mid), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Replace(const String& in, const String& in) const", asMETHOD(String, Replace), asCALL_THISCALL);
    sdk->RegisterMethod("String", "int Find(const String& in, int) const", asMETHOD(String, Find), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Upper() const", asMETHOD(String, Upper), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Lower() const", asMETHOD(String, Lower), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String LTrim() const", asMETHOD(String, LTrim), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String RTrim() const", asMETHOD(String, RTrim), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String Trim() const", asMETHOD(String, Trim), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String LSet(int, const String& in) const", asMETHOD(String, LSet), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String RSet(int, const String& in) const", asMETHOD(String, RSet), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String StripExt() const", asMETHOD(String, StripExt), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String StripDir() const", asMETHOD(String, StripDir), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String ExtractExt() const", asMETHOD(String, ExtractExt), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String ExtractDir() const", asMETHOD(String, ExtractDir), asCALL_THISCALL);
    sdk->RegisterMethod("String", "String RealPath() const", asMETHOD(String, RealPath), asCALL_THISCALL);
    sdk->RegisterFunction("String ReadString(const String& in)", asFUNCTION(String::Read), asCALL_CDECL);
    sdk->RegisterMethod("String", "void Write(const String& in, bool) const", asMETHOD(String, Write), asCALL_THISCALL);
	//sdk->RegisterMethod("String", "Array<String>@ Split(const String& in) const", asFUNCTION(SplitString), asCALL_CDECL_OBJFIRST);

    // Register Dictionary class and methods (requires String to be registered)
	//RegisterScriptDictionary(sdk->Engine());

    // Get Array<String> type, used by String::Split
	//stringArrayType = sdk->ScriptType("Array<String>");
	stringArrayType = sdk->ScriptType("array<String>");
}

static asIObjectType* ScriptType(SmashSDK* sdk, const char* typeName) {
	int typeId = sdk->Engine()->GetModule("MainModule")->GetTypeIdByDecl(typeName);
	if ( typeId < 0 ) typeId = sdk->Engine()->GetTypeIdByDecl(typeName);
    return sdk->Engine()->GetObjectTypeById(typeId);
}

static void* ArrayToScriptArray(SmashSDK* sdk, const Array<void*>& array, asIObjectType* arrayType) {
    (void)sdk;  // Remove "unused arg" warning
    CScriptArray* scriptArr = new CScriptArray(0, arrayType);
    scriptArr->Resize(array.Size());
    for ( int i = 0; i < array.Size(); i++ ) {
        void** elem = (void**)scriptArr->At(i);
        *elem = array[i];
    }
    return (void*)scriptArr;
}

static void* StringArrayToScriptArray(SmashSDK* sdk, const Array<String>& array) {
    (void)sdk;  // Remove "unused arg" warning
    CScriptArray* scriptArr = new CScriptArray(0, stringArrayType);
    scriptArr->Resize(array.Size());
    for ( int i = 0; i < array.Size(); i++ ) {
        String* elem = (String*)scriptArr->At(i);
        *elem = array[i];
    }
    return (void*)scriptArr;
}

static void SetEntryPoint(SmashSDK* sdk, EntryPointFunc entryPoint) {
    ((ImplSmashSDK*)sdk)->SetEntryPointImpl(entryPoint);
}

static asIScriptFunction* ScriptFunction(SmashSDK* sdk, const char* decl) {
    return sdk->Engine()->GetModule("MainModule")->GetFunctionByDecl(decl);
}

static asIScriptFunction* ScriptMethod(SmashSDK* sdk, asIObjectType* type, const char* decl) {
    return type->GetMethodByDecl(decl);
}

static void PrepareScriptFunction(SmashSDK* sdk, asIScriptFunction* func) {
    sdk->Context()->Prepare(func);
}

static void SetScriptThis(SmashSDK* sdk, asIScriptObject* object) {
    sdk->Context()->SetObject(object);
}

static void SetArgInt(SmashSDK* sdk, unsigned int index, int value) {
    sdk->Context()->SetArgDWord(index, value);
}

static void SetArgAddress(SmashSDK* sdk, unsigned int index, void* address) {
    sdk->Context()->SetArgAddress(index, address);
}

static int ExecuteContext(SmashSDK* sdk) {
    return sdk->Context()->Execute();
}

static void AbortContext(SmashSDK* sdk) {
    sdk->Context()->Abort();
}

static asIScriptObject* CreateScriptObject(SmashSDK* sdk, asIObjectType* type, const char* factory) {
    asIScriptFunction* factFunc = type->GetFactoryByDecl(factory);
    sdk->PrepareScriptFunction(factFunc);
    sdk->ExecuteContext();
    asIScriptObject* obj = *(asIScriptObject**)sdk->Context()->GetAddressOfReturnValue();
    obj->AddRef();
    return obj;
}

static void Error(SmashSDK* sdk, const char* msg) {
    sdk->Engine()->WriteMessage("", 0, 0, asMSGTYPE_ERROR, msg);
}
