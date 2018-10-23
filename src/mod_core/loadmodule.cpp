#include "../sdk/smashsdk.h"
#include "../sdk/angelscript.h"
#include "main.h"
#include <new>
#include <vector>

static int fileRead = FILE_READ;
static int fileWrite = FILE_WRITE;
static int fileAppend = FILE_APPEND;
static int filetypeNone = FILETYPE_NONE;
static int filetypeFile = FILETYPE_FILE;
static int filetypeDir = FILETYPE_DIR;
static int platformWindows = PLATFORM_WINDOWS;
static int platformMac = PLATFORM_MAC;
static int platformLinux = PLATFORM_LINUX;
static SmashSDK* globSDK = NULL;

static Dir* DirFactory(const String& path) {
    return new Dir(path);
}

static File* FileFactory(const String& filename, int mode) {
    return new File(filename, mode);
}

static Library* LibraryFactory(const String& filename) {
    return new Library(filename);
}

static MemBuffer* MemBufferFactory(unsigned int size) {
    return new MemBuffer(size);
}

static void* SystemCommandLine() {
    return globSDK->StringArrayToScriptArray(System::CommandLine());
}

extern "C" SDKFUNC void LoadModule(SmashSDK* sdk) {
    globSDK = sdk;

    // Set program name and command line
    System::SetProgramName(sdk->GetArgV()[0]);
    System::SetCommandLine(sdk->GetArgC()-1, &sdk->GetArgV()[1]);

    // Register default Array, Dictionary and String classes
    sdk->RegisterDefaultTypes();

    // Console
    sdk->RegisterFunction("void Print(const String &in)", asFUNCTION(Console::Print), asCALL_CDECL);
    sdk->RegisterFunction("String Input(const String &in)", asFUNCTION(Console::Input), asCALL_CDECL);

    // Dir
    sdk->RegisterClass("Dir", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Dir", asBEHAVE_FACTORY, "Dir@ f(const String& in)", asFUNCTION(DirFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Dir", asBEHAVE_ADDREF, "void f()", asMETHOD(Dir, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Dir", asBEHAVE_RELEASE, "void f()", asMETHOD(Dir, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Dir", "bool HasNext() const", asMETHOD(Dir, HasNext), asCALL_THISCALL);
    sdk->RegisterMethod("Dir", "const String& Next()", asMETHOD(Dir, Next), asCALL_THISCALL);
    sdk->RegisterFunction("String CurrentDir()", asFUNCTION(Dir::Current), asCALL_CDECL);
    sdk->RegisterFunction("void ChangeDir(const String& in)", asFUNCTION(Dir::Change), asCALL_CDECL);
    sdk->RegisterFunction("void CreateDir(const String& in)", asFUNCTION(Dir::Create), asCALL_CDECL);
    sdk->RegisterFunction("void DeleteDir(const String& in)", asFUNCTION(Dir::Delete), asCALL_CDECL);

    // File
    sdk->RegisterGlobal("const int FILE_READ", &fileRead);
    sdk->RegisterGlobal("const int FILE_WRITE", &fileWrite);
    sdk->RegisterGlobal("const int FILE_APPEND", &fileAppend);
    sdk->RegisterGlobal("const int FILETYPE_NONE", &filetypeNone);
    sdk->RegisterGlobal("const int FILETYPE_FILE", &filetypeFile);
    sdk->RegisterGlobal("const int FILETYPE_DIR", &filetypeDir);
    sdk->RegisterClass("File", 0, asOBJ_REF);
    sdk->RegisterBehaviour("File", asBEHAVE_FACTORY, "File@ f(const String& in, int)", asFUNCTION(FileFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("File", asBEHAVE_ADDREF, "void f()", asMETHOD(File, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("File", asBEHAVE_RELEASE, "void f()", asMETHOD(File, Release), asCALL_THISCALL);
    sdk->RegisterMethod("File", "bool IsOpened() const", asMETHOD(File, IsOpened), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void Close()", asMETHOD(File, Close), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint64 Size() const", asMETHOD(File, Size), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint64 Pos() const", asMETHOD(File, Pos), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void Seek(uint64)", asMETHOD(File, Seek), asCALL_THISCALL);
    sdk->RegisterMethod("File", "bool Eof() const", asMETHOD(File, Eof), asCALL_THISCALL);
    sdk->RegisterMethod("File", "int8 ReadInt8()", asMETHOD(File, ReadInt8), asCALL_THISCALL);
    sdk->RegisterMethod("File", "int16 ReadInt16()", asMETHOD(File, ReadInt16), asCALL_THISCALL);
    sdk->RegisterMethod("File", "int ReadInt()", asMETHOD(File, ReadInt), asCALL_THISCALL);
    sdk->RegisterMethod("File", "int64 ReadInt64()", asMETHOD(File, ReadInt64), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint8 ReadUInt8()", asMETHOD(File, ReadUInt8), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint16 ReadUInt16()", asMETHOD(File, ReadUInt16), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint ReadUInt()", asMETHOD(File, ReadUInt), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint64 ReadUInt64()", asMETHOD(File, ReadUInt64), asCALL_THISCALL);
    sdk->RegisterMethod("File", "float ReadFloat()", asMETHOD(File, ReadFloat), asCALL_THISCALL);
    sdk->RegisterMethod("File", "double ReadDouble()", asMETHOD(File, ReadDouble), asCALL_THISCALL);
    sdk->RegisterMethod("File", "String ReadCString()", asMETHOD(File, ReadCString), asCALL_THISCALL);
    sdk->RegisterMethod("File", "String ReadCLine()", asMETHOD(File, ReadCLine), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint ReadBytes(uint, uint)", asMETHOD(File, ReadBytes), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteInt8(int8)", asMETHOD(File, WriteInt8), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteInt16(int16)", asMETHOD(File, WriteInt16), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteInt(int)", asMETHOD(File, WriteInt), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteInt64(int64)", asMETHOD(File, WriteInt64), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteUInt8(uint8)", asMETHOD(File, WriteUInt8), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteUInt16(uint16)", asMETHOD(File, WriteUInt16), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteUInt(uint)", asMETHOD(File, WriteUInt), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteUInt64(uint64)", asMETHOD(File, WriteUInt64), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteFloat(float)", asMETHOD(File, WriteFloat), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteDouble(double)", asMETHOD(File, WriteDouble), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteCString(const String& in)", asMETHOD(File, WriteCString), asCALL_THISCALL);
    sdk->RegisterMethod("File", "void WriteCLine(const String& in)", asMETHOD(File, WriteCLine), asCALL_THISCALL);
    sdk->RegisterMethod("File", "uint WriteBytes(uint, uint)", asMETHOD(File, WriteBytes), asCALL_THISCALL);
    sdk->RegisterFunction("int FileType(const String& in)", asFUNCTION(File::Type), asCALL_CDECL);
    sdk->RegisterFunction("uint64 FileSize(const String& in)", asFUNCTION(File::Size_), asCALL_CDECL);
    sdk->RegisterFunction("void FileCopy(const String& in, const String& in)", asFUNCTION(File::Copy), asCALL_CDECL);
    sdk->RegisterFunction("void FileDelete(const String& in)", asFUNCTION(File::Delete), asCALL_CDECL);

    // Library
    sdk->RegisterClass("Library", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Library", asBEHAVE_FACTORY, "Library@ f(const String& in)", asFUNCTION(LibraryFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Library", asBEHAVE_ADDREF, "void f()", asMETHOD(Library, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Library", asBEHAVE_RELEASE, "void f()", asMETHOD(Library, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "bool IsOpened() const", asMETHOD(Library, IsOpened), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "uint Function(const String& in) const", asMETHOD(Library, Function), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "void PushInt(int)", asMETHOD(Library, PushInt), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "void PushFloat(float)", asMETHOD(Library, PushFloat), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "void PushCString(const String& in)", asMETHOD(Library, PushCString), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "void CallVoidFunction(uint)", asMETHOD(Library, CallVoidFunction), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "int CallIntFunction(uint)", asMETHOD(Library, CallIntFunction), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "float CallFloatFunction(uint)", asMETHOD(Library, CallFloatFunction), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "String CallCStringFunction(uint)", asMETHOD(Library, CallCStringFunction), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "void CallVoidFunctionC(uint)", asMETHOD(Library, CallVoidFunctionC), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "int CallIntFunctionC(uint)", asMETHOD(Library, CallIntFunctionC), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "float CallFloatFunctionC(uint)", asMETHOD(Library, CallFloatFunctionC), asCALL_THISCALL);
    sdk->RegisterMethod("Library", "String CallCStringFunctionC(uint)", asMETHOD(Library, CallCStringFunctionC), asCALL_THISCALL);

    // Math
    sdk->RegisterFunction("double Pi()", asFUNCTION(Math::Pi), asCALL_CDECL);
    sdk->RegisterFunction("double Floor(double)", asFUNCTION(Math::Floor), asCALL_CDECL);
    sdk->RegisterFunction("double Ceil(double)", asFUNCTION(Math::Ceil), asCALL_CDECL);
    sdk->RegisterFunction("int64 Abs(int64)", asFUNCTION(Math::Abs), asCALL_CDECL);
    sdk->RegisterFunction("double Abs(double)", asFUNCTION(Math::FAbs), asCALL_CDECL);
    sdk->RegisterFunction("double Sqr(double)", asFUNCTION(Math::Sqr), asCALL_CDECL);
    sdk->RegisterFunction("double DegSin(double)", asFUNCTION(Math::DegSin), asCALL_CDECL);
    sdk->RegisterFunction("double DegCos(double)", asFUNCTION(Math::DegCos), asCALL_CDECL);
    sdk->RegisterFunction("double DegTan(double)", asFUNCTION(Math::DegTan), asCALL_CDECL);
    sdk->RegisterFunction("double DegASin(double)", asFUNCTION(Math::DegASin), asCALL_CDECL);
    sdk->RegisterFunction("double DegACos(double)", asFUNCTION(Math::DegACos), asCALL_CDECL);
    sdk->RegisterFunction("double DegATan(double)", asFUNCTION(Math::DegATan), asCALL_CDECL);
    sdk->RegisterFunction("double DegATan2(double, double)", asFUNCTION(Math::DegATan2), asCALL_CDECL);
    sdk->RegisterFunction("double Exp(double)", asFUNCTION(Math::Exp), asCALL_CDECL);
    sdk->RegisterFunction("double Log(double)", asFUNCTION(Math::Log), asCALL_CDECL);
    sdk->RegisterFunction("double Log10(double)", asFUNCTION(Math::Log10), asCALL_CDECL);
    sdk->RegisterFunction("int Rand(int, int)", asFUNCTION(Math::Rand), asCALL_CDECL);
    sdk->RegisterFunction("double Rand(double, double)", asFUNCTION(Math::FRand), asCALL_CDECL);
    sdk->RegisterFunction("void SeedRand(uint)", asFUNCTION(Math::SeedRand), asCALL_CDECL);
    sdk->RegisterFunction("double Wrap(double, double)", asFUNCTION(Math::Wrap), asCALL_CDECL);

    // MemBuffer
    sdk->RegisterClass("MemBuffer", 0, asOBJ_REF);
    sdk->RegisterBehaviour("MemBuffer", asBEHAVE_FACTORY, "MemBuffer@ f(uint)", asFUNCTION(MemBufferFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("MemBuffer", asBEHAVE_ADDREF, "void f()", asMETHOD(MemBuffer, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("MemBuffer", asBEHAVE_RELEASE, "void f()", asMETHOD(MemBuffer, Release), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint Size() const", asMETHOD(MemBuffer, Size), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void Resize(uint size)", asMETHOD(MemBuffer, Resize), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "int8 PeekInt8(uint) const", asMETHOD(MemBuffer, PeekInt8), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "int16 PeekInt16(uint) const", asMETHOD(MemBuffer, PeekInt16), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "int PeekInt(uint) const", asMETHOD(MemBuffer, PeekInt), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "int64 PeekInt64(uint) const", asMETHOD(MemBuffer, PeekInt64), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint8 PeekUInt8(uint) const", asMETHOD(MemBuffer, PeekUInt8), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint16 PeekUInt16(uint) const", asMETHOD(MemBuffer, PeekUInt16), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint PeekUInt(uint) const", asMETHOD(MemBuffer, PeekUInt), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint64 PeekUInt64(uint) const", asMETHOD(MemBuffer, PeekUInt64), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "float PeekFloat(uint) const", asMETHOD(MemBuffer, PeekFloat), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "double PeekDouble(uint) const", asMETHOD(MemBuffer, PeekDouble), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "String PeekCString(uint, int = 0) const", asMETHOD(MemBuffer, PeekCString), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeInt8(uint, int8)", asMETHOD(MemBuffer, PokeInt8), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeInt16(uint, int16)", asMETHOD(MemBuffer, PokeInt16), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeInt(uint, int)", asMETHOD(MemBuffer, PokeInt), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeInt64(uint, int64)", asMETHOD(MemBuffer, PokeInt64), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeUInt8(uint, uint8)", asMETHOD(MemBuffer, PokeUInt8), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeUInt16(uint, uint16)", asMETHOD(MemBuffer, PokeUInt16), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeUInt(uint, uint)", asMETHOD(MemBuffer, PokeUInt), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeUInt64(uint, uint64)", asMETHOD(MemBuffer, PokeUInt64), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeFloat(uint, float)", asMETHOD(MemBuffer, PokeFloat), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeDouble(uint, double)", asMETHOD(MemBuffer, PokeDouble), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "void PokeCString(uint, const String& in)", asMETHOD(MemBuffer, PokeCString), asCALL_THISCALL);
    sdk->RegisterMethod("MemBuffer", "uint Buffer()", asMETHOD(MemBuffer, Buffer), asCALL_THISCALL);

    // System
    sdk->RegisterGlobal("const int PLATFORM_WINDOWS", &platformWindows);
    sdk->RegisterGlobal("const int PLATFORM_MAC", &platformMac);
    sdk->RegisterGlobal("const int PLATFORM_LINUX", &platformLinux);
    sdk->RegisterFunction("int PlatformId()", asFUNCTION(System::PlatformId), asCALL_CDECL);
    sdk->RegisterFunction("const String& ProgramName()", asFUNCTION(System::ProgramName), asCALL_CDECL);
	sdk->RegisterFunction("const array<String>@ CommandLine()", asFUNCTION(SystemCommandLine), asCALL_CDECL);
    sdk->RegisterFunction("String GetEnv(const String& in)", asFUNCTION(System::GetEnv), asCALL_CDECL);
    sdk->RegisterFunction("int SystemCall(const String& in)", asFUNCTION(System::SystemCall), asCALL_CDECL);
    sdk->RegisterFunction("String RunProgram(const String& in)", asFUNCTION(System::RunProgram), asCALL_CDECL);
    sdk->RegisterFunction("void Exit(int)", asFUNCTION(System::Exit), asCALL_CDECL);

    // Time
    sdk->RegisterFunction("uint64 Millisecs()", asFUNCTION(Time::Millisecs), asCALL_CDECL);
    sdk->RegisterFunction("void Delay(uint64)", asFUNCTION(Time::Delay), asCALL_CDECL);
    sdk->RegisterFunction("String CurrentDate()", asFUNCTION(Time::CurrentDate), asCALL_CDECL);
    sdk->RegisterFunction("String CurrentTime()", asFUNCTION(Time::CurrentTime), asCALL_CDECL);
}
