# Smash
Smash is a 32-bit runtime based on the [AngelScript](http://www.angelcode.com/angelscript/) programming language developed by Andreas Jönsson. It generates executable files that embed both the interpreter and the bytecode for your program that can be redistributed to end users.

The syntax of the language is similar to that of C++, C# and Java. All the classes and functions available to the language are provided through specially formatted shared libraries (called "modules"). Included are a "core" and a "game" module. A SDK to create additional modules will be available soon. When distributing a Smash program, the modules used must be copied in the same path as the executable file, or inside a "modules" folder.

## Using the compiler command line on Windows

The compiler is distributed as a command-line tool in the "bin" folder. This folder can be added to your PATH environment variable to be able to compile from any location in your hard drive. The compiler is invoked in the following way:

```
smashc.win32.exe [options] sourcefile
```

Here, the `[options]` part is optional and can be one or several of the following:

- `check`: Check syntax (does not generate an executable).

- `run`: Run program (does not generate an executable).

- `console`: Build app with console window.

## Core module

This module contains the core functionality of the system, such as string and array support, file system access, file reading and writing, etc.

All the string literals defined in your program using double quotes (i.e. `"Hello world!"`) are always converted to an `String` object. All the arrays declared with the square bracket syntax (i.e. `int[5] arr`) are always converted to an `Array` object.


Although it could be replaced by a custom Core module, it is recommended that you always use the standard one. It includes the following classes and functions:

### Array

```
class Array<T> {
  Array<T>();
  Array<T>(uint size);
  Array<T>(uint size, const T& value);

  T& operator [](uint index);
  const T& operator [](uint index) const;
  Array<T>& operator =(const Array<T>& other);
  bool operator ==(const Array<T>& other);
  bool operator !=(const Array<T>& other);

  uint Length() const;
  bool IsEmpty() const;
  void Reserve(uint size);
  void Resize(uint size);
  void Reverse();
  void InsertAt(uint index, const T& element);
  void InsertLast(const T& element);
  void RemoveAt(uint index);
  void RemoveLast();
  void SortAsc();
  void SortAsc(uint index, uint count);
  void SortDesc();
  void SortDesc(uint index, uint count);
  int Find(const T& element);
  int Find(uint index, const T& element);
}
```

### Console

```
void Print(const String& text);
String Input(const String& prompt);
```

### Dictionary

```
class Dictionary<T> {
  Dictionary<T>();

  Dictionary<T>& operator =(const Dictionary<T>& other);

  void Set(const String& key, const T& value);
  bool Get(const String& key, T& value);
  Array<String>@ GetKeys() const;
  bool Exists(const String& key) const;
  void Delete(const String& key);
  void DeleteAll();
  bool IsEmpty() const;
  uint Size() const;
}
```

### Dir

```
class Dir {
  Dir(const String& path);

  bool HasNext() const;
  const String& Next();
}

String CurrentDir();
void ChangeDir(const String& path);
void CreateDir(const String& path);
void DeleteDir(const String& path);
```

### File

```
const int FILE_READ;
const int FILE_WRITE;
const int FILE_APPEND;
const int FILETYPE_NONE;
const int FILETYPE_FILE;
const int FILETYPE_DIR;

class File {
  File(const String& path, int mode);

  bool IsOpened() const;
  void Close();
  uint64 Size() const;
  uint64 Pos() const;
  void Seek(uint64 pos);
  bool Eof() const;
  int8 ReadInt8();
  int16 ReadInt16();
  int ReadInt();
  int64 ReadInt64();
  uint8 ReadUInt8();
  uint16 ReadUInt16();
  uint ReadUInt();
  uint64 ReadUInt64();
  float ReadFloat();
  double ReadDouble();
  String ReadCString();
  String ReadCLine();
  uint ReadBytes(uint buffer, uint size);
  void WriteInt8(int8 val);
  void WriteInt16(int16 val);
  void WriteInt(int val);
  void WriteInt64(uint64 val);
  void WriteUInt8(uint8 val);
  void WriteUInt16(uint16 val);
  void WriteUInt(uint val);
  void WriteUInt64(uint64 val);
  void WriteFloat(float val);
  void WriteDouble(double val);
  void WriteCString(const String& val);
  void WriteCLine(const String& val);
  void WriteBytes(uint buffer, uint size);
}

int FileType(const String& path);
uint64 FileSize(const String& path);
void FileCopy(const String& from, const String& to);
void FileDelete(const String& path);
```

### Library

```
class Library {
  Library(const String& filename);

  bool IsOpened() const;
  uint Function(const String& in) const;
  void PushInt(int val);
  void PushFloat(float val);
  void PushCString(const String& val);
  void CallVoidFunction(uint func);
  int CallIntFunction(uint func);
  float CallFloatFunction(uint func);
  String CallCStringFunction(uint func);
  void CallVoidFunctionC(uint func);
  int CallIntFunctionC(uint func);
  float CallFloatFunctionC(uint func);
  String CallCStringFunctionC(uint func);
}
```

### Math

```
double Pi();
double Floor(double val);
double Ceil(double val);
int64 Abs(int64 val);
double Abs(double val);
double Sqr(double val);
double DegSin(double val);
double DegCos(double val);
double DegTan(double val);
double DegASin(double val);
double DegACos(double val);
double DegATan(double val);
double DegATan2(double y, double x);
double Exp(double val);
double Log(double val);
double Log10(double val);
int Rand(int min, int max);
double Rand(double min, double max);
void SeedRand(uint seed);
double Wrap(double value, double module);
```

### MemBuffer

```
class MemBuffer {
  MemBuffer(uint size);

  uint Size() const;
  void Resize(uint size);
  int8 PeekInt8(uint offset) const;
  int16 PeekInt16(uint offset) const;
  int PeekInt(uint offset) const;
  int64 PeekInt64(uint offset) const;
  uint8 PeekUInt8(uint offset) const;
  uint16 PeekUInt16(uint offset) const;
  uint PeekUInt(uint offset) const;
  uint64 PeekUInt64(uint offset) const;
  float PeekFloat(uint offset) const;
  float PeekDouble(uint offset) const;
  String PeekCString(uint offset, int size = 0) const;
  void PokeInt8(uint offset, int8 val);
  void PokeInt16(uint offset, int16 val);
  void PokeInt(uint offset, int val);
  void PokeInt64(uint offset, int64 val);
  void PokeUInt8(uint offset, uint8 val);
  void PokeUInt16(uint offset, uint16 val);
  void PokeUInt(uint offset, uint val);
  void PokeUInt64(uint offset, uint64 val);
  void PokeFloat(uint offset, float val);
  void PokeDouble(uint offset, double val);
  void PokeCString(uint offset, const String& val);
  uint Buffer();
}
```

### String

```
class String {
        String();
        String(const String& other);
        String(uint length, uint8 char);

        bool operator ==(const String& other) const;
        bool operator !=(const String& other) const;
        bool operator <(const String& other) const;
        bool operator >(const String& other) const;
        String operator +(const String& other) const;
        String& operator =(const String& other);
        String& operator +=(const String& other);

        int Length() const;
        int ToInt() const;
        float ToFloat() const;
        uint8 Asc() const;
        String Left(int count) const;
        String Right(int count) const;
        String Mid(int offset, int count) const;
        String Replace(const String& find, const String& replace) const;
        int Find(const String& find, int offset) const;
        String Upper() const;
        String Lower() const;
        String LTrim() const;
        String RTrim() const;
        String Trim() const;
        String LSet(int length, const String& fill) const;
        String RSet(int length, const String& fill) const;
        String StripExt() const;
        String StripDir() const;
        String ExtractExt() const;
        String ExtractDir() const;
        String RealPath() const;
        void Write(const String& filename, bool append) const;
        Array<String>@ Split(const String& separator) const;
}

String Str(int val);
String Str(float val);
String Hex(int val);
String Chr(uint8 ascii);
String ReadString(const String& filename);
```

### System

```
const int PLATFORM_WINDOWS;
const int PLATFORM_MAC;
const int PLATFORM_LINUX;

int PlatformId();
const String& ProgramName();
const Array<String>@ CommandLine();
String GetEnv(const String& var);
int SystemCall(const String& command);
String RunProgram(const String& program);
void Exit(int code);
```

### Time

```
uint64 Millisecs();
void Delay(uint64 millisecs);
String CurrentDate();
String CurrentTime();
```

## Game module

### Channel

```
class Channel {
  void Stop();
  void Pause();
  void Resume();
  void SetVolume(float volume);
  bool IsPlaying() const;
}
```

### Desktop

```
int DesktopWidth();
int DesktopHeight();
```

### Font

```
class Font {
  Font(const Pixmap& pixmap);
  Font(const String& filename);

  bool IsLoaded() const;
  int Size() const;
  int TextWidth(const String& text) const;
  int TextHeight(const String& text) const;
  void Draw(const String& text, double x, double y);
}
```

### Image

```
class Image {
  Image(const Pixmap& pixmap, int hframes, int vframes);
  Image(const String& filename, int hframes, int vframes);

  bool IsLoaded() const;
  void Draw(double x, double y, int frame, double width = 0.0, double height = 0.0, double angle = 0.0);
  void DrawTiled(double offsetx, double offsety, double x, double y, double width, double height);
  int Frames() const;
  int HFrames() const;
  int VFrames() const;
  int Width() const;
  int Height() const;
  void SetHandle(int x, int y);
  int HandleX() const;
  int HandleY() const;
}
```

### Input

```
const int MOUSE_LEFT;
const int MOUSE_RIGHT;
const int MOUSE_MIDDLE;

void ShowMouse(bool show);
void MoveMouse(int x, int y);
int MouseX();
int MouseY();
bool MouseButtonPressed(int button);
bool KeyPressed(int key);
```

### Music

```
bool LoadMusic(const String& filename);
void FreeMusic();
void PlayMusic();
void LoopMusic();
void StopMusic();
void PauseMusic();
void ResumeMusic();
void SetMusicVolume(float volume);
bool IsMusicPlaying();
```

### Pixmap

```
class Pixmap {
        Pixmap(uint width, uint height, int color);
        Pixmap(const String& filename);

        bool IsLoaded() const;
        MemBuffer& Buffer();
        uint Width() const;
        uint Height() const;
}
```

### Renderer

```
const int BLEND_SOLID;
const int BLEND_ALPHA;
const int BLEND_ADD;
const int BLEND_MODULATE;

void SetOrigin(double x, double y);
void SetViewport(int x, int y, int width, int height);
void SetBlendMode(int mode);
void SetColor(int color);
int Color(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255);
uint8 Red(int color);
uint8 Green(int color);
uint8 Blue(int color);
uint8 Alpha(int color);
void DrawPoint(double x, double y);
void DrawLine(double x1, double y1, double x2, double y2);
void DrawRect(double x, double y, double width, double height);
void DrawEllipse(double xcenter, double ycenter, double xrad, double yrad);
```

### Screen

```
void OpenScreen(int width, int height, bool fullscreen);
void CloseScreen();
bool ScreenOpened();
void ClearScreen(int color);
void RefreshScreen();
int ScreenWidth();
int ScreenHeight();
int ScreenFPS();
double DeltaTime();
```

### Sound

```
class Sound {
  Sound(const String& filename);

  bool IsLoaded() const;
  Channel@ Play();
  Channel@ Loop();
}
```
