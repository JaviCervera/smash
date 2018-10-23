#include "main.h"
#include "../sdk/smashsdk.h"
#include "../sdk/angelscript.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_scancode.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_scancode.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_scancode.h"
#endif

static int blendSolid = BLEND_SOLID;
static int blendAlpha = BLEND_ALPHA;
static int blendAdd = BLEND_ADD;
static int blendModulate = BLEND_MODULATE;
static int mouseLeft = MOUSE_LEFT;
static int mouseRight = MOUSE_RIGHT;
static int mouseMiddle = MOUSE_MIDDLE;

static int KEY_A = SDL_SCANCODE_A;
static int KEY_B = SDL_SCANCODE_B;
static int KEY_C = SDL_SCANCODE_C;
static int KEY_D = SDL_SCANCODE_D;
static int KEY_E = SDL_SCANCODE_E;
static int KEY_F = SDL_SCANCODE_F;
static int KEY_G = SDL_SCANCODE_G;
static int KEY_H = SDL_SCANCODE_H;
static int KEY_I = SDL_SCANCODE_I;
static int KEY_J = SDL_SCANCODE_J;
static int KEY_K = SDL_SCANCODE_K;
static int KEY_L = SDL_SCANCODE_L;
static int KEY_M = SDL_SCANCODE_M;
static int KEY_N = SDL_SCANCODE_N;
static int KEY_O = SDL_SCANCODE_O;
static int KEY_P = SDL_SCANCODE_P;
static int KEY_Q = SDL_SCANCODE_Q;
static int KEY_R = SDL_SCANCODE_R;
static int KEY_S = SDL_SCANCODE_S;
static int KEY_T = SDL_SCANCODE_T;
static int KEY_U = SDL_SCANCODE_U;
static int KEY_V = SDL_SCANCODE_V;
static int KEY_W = SDL_SCANCODE_W;
static int KEY_X = SDL_SCANCODE_X;
static int KEY_Y = SDL_SCANCODE_Y;
static int KEY_Z = SDL_SCANCODE_Z;
static int KEY_1 = SDL_SCANCODE_1;
static int KEY_2 = SDL_SCANCODE_2;
static int KEY_3 = SDL_SCANCODE_3;
static int KEY_4 = SDL_SCANCODE_4;
static int KEY_5 = SDL_SCANCODE_5;
static int KEY_6 = SDL_SCANCODE_6;
static int KEY_7 = SDL_SCANCODE_7;
static int KEY_8 = SDL_SCANCODE_8;
static int KEY_9 = SDL_SCANCODE_9;
static int KEY_0 = SDL_SCANCODE_0;
static int KEY_RETURN = SDL_SCANCODE_RETURN;
static int KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
static int KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE;
static int KEY_TAB = SDL_SCANCODE_TAB;
static int KEY_SPACE = SDL_SCANCODE_SPACE;
static int KEY_MINUS = SDL_SCANCODE_MINUS;
static int KEY_EQUALS = SDL_SCANCODE_EQUALS;
static int KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
static int KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
static int KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH;
static int KEY_NONUSHASH = SDL_SCANCODE_NONUSHASH;
static int KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON;
static int KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE;
static int KEY_GRAVE = SDL_SCANCODE_GRAVE;
static int KEY_COMMA = SDL_SCANCODE_COMMA;
static int KEY_PERIOD = SDL_SCANCODE_PERIOD;
static int KEY_SLASH = SDL_SCANCODE_SLASH;
static int KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK;
static int KEY_F1 = SDL_SCANCODE_F1;
static int KEY_F2 = SDL_SCANCODE_F2;
static int KEY_F3 = SDL_SCANCODE_F3;
static int KEY_F4 = SDL_SCANCODE_F4;
static int KEY_F5 = SDL_SCANCODE_F5;
static int KEY_F6 = SDL_SCANCODE_F6;
static int KEY_F7 = SDL_SCANCODE_F7;
static int KEY_F8 = SDL_SCANCODE_F8;
static int KEY_F9 = SDL_SCANCODE_F9;
static int KEY_F10 = SDL_SCANCODE_F10;
static int KEY_F11 = SDL_SCANCODE_F11;
static int KEY_F12 = SDL_SCANCODE_F12;
static int KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
static int KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK;
static int KEY_PAUSE = SDL_SCANCODE_PAUSE;
static int KEY_INSERT = SDL_SCANCODE_INSERT;
static int KEY_HOME = SDL_SCANCODE_HOME;
static int KEY_PAGEUP = SDL_SCANCODE_PAGEUP;
static int KEY_DELETE = SDL_SCANCODE_DELETE;
static int KEY_END = SDL_SCANCODE_END;
static int KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;
static int KEY_RIGHT = SDL_SCANCODE_RIGHT;
static int KEY_LEFT = SDL_SCANCODE_LEFT;
static int KEY_DOWN = SDL_SCANCODE_DOWN;
static int KEY_UP = SDL_SCANCODE_UP;
static int KEY_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR;
static int KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE;
static int KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY;
static int KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS;
static int KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS;
static int KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER;
static int KEY_KP_1 = SDL_SCANCODE_KP_1;
static int KEY_KP_2 = SDL_SCANCODE_KP_2;
static int KEY_KP_3 = SDL_SCANCODE_KP_3;
static int KEY_KP_4 = SDL_SCANCODE_KP_4;
static int KEY_KP_5 = SDL_SCANCODE_KP_5;
static int KEY_KP_6 = SDL_SCANCODE_KP_6;
static int KEY_KP_7 = SDL_SCANCODE_KP_7;
static int KEY_KP_8 = SDL_SCANCODE_KP_8;
static int KEY_KP_9 = SDL_SCANCODE_KP_9;
static int KEY_KP_0 = SDL_SCANCODE_KP_0;
static int KEY_KP_PERIOD = SDL_SCANCODE_KP_PERIOD;
static int KEY_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH;
static int KEY_APPLICATION = SDL_SCANCODE_APPLICATION;
static int KEY_POWER = SDL_SCANCODE_POWER;
static int KEY_KP_EQUALS = SDL_SCANCODE_KP_EQUALS;
static int KEY_F13 = SDL_SCANCODE_F13;
static int KEY_F14 = SDL_SCANCODE_F14;
static int KEY_F15 = SDL_SCANCODE_F15;
static int KEY_F16 = SDL_SCANCODE_F16;
static int KEY_F17 = SDL_SCANCODE_F17;
static int KEY_F18 = SDL_SCANCODE_F18;
static int KEY_F19 = SDL_SCANCODE_F19;
static int KEY_F20 = SDL_SCANCODE_F20;
static int KEY_F21 = SDL_SCANCODE_F21;
static int KEY_F22 = SDL_SCANCODE_F22;
static int KEY_F23 = SDL_SCANCODE_F23;
static int KEY_F24 = SDL_SCANCODE_F24;
static int KEY_EXECUTE = SDL_SCANCODE_EXECUTE;
static int KEY_HELP = SDL_SCANCODE_HELP;
static int KEY_MENU = SDL_SCANCODE_MENU;
static int KEY_SELECT = SDL_SCANCODE_SELECT;
static int KEY_STOP = SDL_SCANCODE_STOP;
static int KEY_AGAIN = SDL_SCANCODE_AGAIN;
static int KEY_UNDO = SDL_SCANCODE_UNDO;
static int KEY_CUT = SDL_SCANCODE_CUT;
static int KEY_COPY = SDL_SCANCODE_COPY;
static int KEY_PASTE = SDL_SCANCODE_PASTE;
static int KEY_FIND = SDL_SCANCODE_FIND;
static int KEY_MUTE = SDL_SCANCODE_MUTE;
static int KEY_VOLUMEUP = SDL_SCANCODE_VOLUMEUP;
static int KEY_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN;
static int KEY_KP_COMMA = SDL_SCANCODE_KP_COMMA;
static int KEY_KP_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400;
static int KEY_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1;
static int KEY_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2;
static int KEY_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3;
static int KEY_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4;
static int KEY_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5;
static int KEY_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6;
static int KEY_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7;
static int KEY_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8;
static int KEY_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9;
static int KEY_LANG1 = SDL_SCANCODE_LANG1;
static int KEY_LANG2 = SDL_SCANCODE_LANG2;
static int KEY_LANG3 = SDL_SCANCODE_LANG3;
static int KEY_LANG4 = SDL_SCANCODE_LANG4;
static int KEY_LANG5 = SDL_SCANCODE_LANG5;
static int KEY_LANG6 = SDL_SCANCODE_LANG6;
static int KEY_LANG7 = SDL_SCANCODE_LANG7;
static int KEY_LANG8 = SDL_SCANCODE_LANG8;
static int KEY_LANG9 = SDL_SCANCODE_LANG9;
static int KEY_ALTERASE = SDL_SCANCODE_ALTERASE;
static int KEY_SYSREQ = SDL_SCANCODE_SYSREQ;
static int KEY_CANCEL = SDL_SCANCODE_CANCEL;
static int KEY_CLEAR = SDL_SCANCODE_CLEAR;
static int KEY_PRIOR = SDL_SCANCODE_PRIOR;
static int KEY_RETURN2 = SDL_SCANCODE_RETURN2;
static int KEY_SEPARATOR = SDL_SCANCODE_SEPARATOR;
static int KEY_OUT = SDL_SCANCODE_OUT;
static int KEY_OPER = SDL_SCANCODE_OPER;
static int KEY_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN;
static int KEY_CRSEL = SDL_SCANCODE_CRSEL;
static int KEY_EXSEL = SDL_SCANCODE_EXSEL;
static int KEY_KP_00 = SDL_SCANCODE_KP_00;
static int KEY_KP_000 = SDL_SCANCODE_KP_000;
static int KEY_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR;
static int KEY_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR;
static int KEY_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT;
static int KEY_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT;
static int KEY_KP_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN;
static int KEY_KP_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN;
static int KEY_KP_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE;
static int KEY_KP_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE;
static int KEY_KP_TAB = SDL_SCANCODE_KP_TAB;
static int KEY_KP_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE;
static int KEY_KP_A = SDL_SCANCODE_KP_A;
static int KEY_KP_B = SDL_SCANCODE_KP_B;
static int KEY_KP_C = SDL_SCANCODE_KP_C;
static int KEY_KP_D = SDL_SCANCODE_KP_D;
static int KEY_KP_E = SDL_SCANCODE_KP_E;
static int KEY_KP_F = SDL_SCANCODE_KP_F;
static int KEY_KP_XOR = SDL_SCANCODE_KP_XOR;
static int KEY_KP_POWER = SDL_SCANCODE_KP_POWER;
static int KEY_KP_PERCENT = SDL_SCANCODE_KP_PERCENT;
static int KEY_KP_LESS = SDL_SCANCODE_KP_LESS;
static int KEY_KP_GREATER = SDL_SCANCODE_KP_GREATER;
static int KEY_KP_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND;
static int KEY_KP_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND;
static int KEY_KP_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR;
static int KEY_KP_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR;
static int KEY_KP_COLON = SDL_SCANCODE_KP_COLON;
static int KEY_KP_HASH = SDL_SCANCODE_KP_HASH;
static int KEY_KP_SPACE = SDL_SCANCODE_KP_SPACE;
static int KEY_KP_AT = SDL_SCANCODE_KP_AT;
static int KEY_KP_EXCLAM = SDL_SCANCODE_KP_EXCLAM;
static int KEY_KP_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE;
static int KEY_KP_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL;
static int KEY_KP_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR;
static int KEY_KP_MEMADD = SDL_SCANCODE_KP_MEMADD;
static int KEY_KP_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT;
static int KEY_KP_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY;
static int KEY_KP_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE;
static int KEY_KP_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS;
static int KEY_KP_CLEAR = SDL_SCANCODE_KP_CLEAR;
static int KEY_KP_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY;
static int KEY_KP_BINARY = SDL_SCANCODE_KP_BINARY;
static int KEY_KP_OCTAL = SDL_SCANCODE_KP_OCTAL;
static int KEY_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL;
static int KEY_KP_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL;
static int KEY_LCTRL = SDL_SCANCODE_LCTRL;
static int KEY_LSHIFT = SDL_SCANCODE_LSHIFT;
static int KEY_LALT = SDL_SCANCODE_LALT;
static int KEY_LGUI = SDL_SCANCODE_LGUI;
static int KEY_RCTRL = SDL_SCANCODE_RCTRL;
static int KEY_RSHIFT = SDL_SCANCODE_RSHIFT;
static int KEY_RALT = SDL_SCANCODE_RALT;
static int KEY_RGUI = SDL_SCANCODE_RGUI;
static int KEY_MODE = SDL_SCANCODE_MODE;
static int KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT;
static int KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV;
static int KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP;
static int KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY;
static int KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE;
static int KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT;
static int KEY_WWW = SDL_SCANCODE_WWW;
static int KEY_MAIL = SDL_SCANCODE_MAIL;
static int KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR;
static int KEY_COMPUTER = SDL_SCANCODE_COMPUTER;
static int KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH;
static int KEY_AC_HOME = SDL_SCANCODE_AC_HOME;
static int KEY_AC_BACK = SDL_SCANCODE_AC_BACK;
static int KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD;
static int KEY_AC_STOP = SDL_SCANCODE_AC_STOP;
static int KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH;
static int KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS;
static int KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN;
static int KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP;
static int KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH;
static int KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE;
static int KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN;
static int KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP;
static int KEY_EJECT = SDL_SCANCODE_EJECT;
static int KEY_SLEEP = SDL_SCANCODE_SLEEP;
static int KEY_APP1 = SDL_SCANCODE_APP1;
static int KEY_APP2 = SDL_SCANCODE_APP2;

static Screen* mainScreen = NULL;

/*static Font* FontFactory(Pixmap* pixmap) {
    Font* font = new Font(pixmap);
    if ( pixmap ) pixmap->Release();
    return font;
}

static Font* FontFactory2(const String& filename) {
    return new Font(filename);
}*/

static Font* FontFactory3(const String& fontName, float pixelHeight, unsigned int mapsize) {
    return new Font(fontName, pixelHeight, mapsize);
}

static Image* ImageFactory(Pixmap* pixmap, int hframes, int vframes) {
    Image* image = new Image(pixmap, hframes, vframes);
    if ( pixmap ) pixmap->Release();
    return image;
}

static Image* ImageFactory2(const String& filename, int hframes, int vframes) {
    return new Image(filename, hframes, vframes);
}

static Pixmap* PixmapFactory(unsigned int width, unsigned int height, int color) {
    return new Pixmap(width, height, color);
}

static Pixmap* PixmapFactory2(const String& filename) {
    return new Pixmap(filename);
}

static Pixmap* PixmapFactory3(const String& fontname, float height) {
    return new Pixmap(fontname, height);
}

static void OpenScreen(int width, int height, bool fullscreen) {
    if ( mainScreen ) delete mainScreen;
    mainScreen = new Screen(width, height, fullscreen);
}

static void CloseScreen() {
    if ( mainScreen ) {
        delete mainScreen;
        mainScreen = NULL;
    }
}

static bool ScreenOpened() {
    if ( !mainScreen ) return false;
    return mainScreen->IsOpened();
}

static void ClearScreen(int color) {
    mainScreen->Clear(color);
}

static void RefreshScreen() {
    mainScreen->Refresh();
}

static int ScreenWidth() {
    return mainScreen->Width();
}

static int ScreenHeight() {
    return mainScreen->Height();
}

static int ScreenFPS() {
    return mainScreen->FPS();
}

static double DeltaTime() {
    return mainScreen->DeltaTime();
}

static Sound* SoundFactory(const String& filename) {
    return new Sound(filename);
}

extern "C" SDKFUNC void LoadModule(SmashSDK* sdk) {
    // Init module
    InitGame();
    atexit(FinishGame);

    // Main
    sdk->RegisterFunction("String SDLError()", asFUNCTION(SDLError), asCALL_CDECL);
    sdk->RegisterFunction("String MixerError()", asFunctionPtr(MixerError), asCALL_CDECL);

    // Channel
    sdk->RegisterClass("Channel", 0, asOBJ_REF | asOBJ_NOCOUNT);
    sdk->RegisterMethod("Channel", "void Stop()", asMETHOD(Channel, Stop), asCALL_THISCALL);
    sdk->RegisterMethod("Channel", "void Pause()", asMETHOD(Channel, Pause), asCALL_THISCALL);
    sdk->RegisterMethod("Channel", "void Resume()", asMETHOD(Channel, Resume), asCALL_THISCALL);
    sdk->RegisterMethod("Channel", "void SetVolume(float)", asMETHOD(Channel, SetVolume), asCALL_THISCALL);
    sdk->RegisterMethod("Channel", "bool IsPlaying() const", asMETHOD(Channel, IsPlaying), asCALL_THISCALL);

    // Desktop
    sdk->RegisterFunction("int DesktopWidth()", asFUNCTION(Desktop::Width), asCALL_CDECL);
    sdk->RegisterFunction("int DesktopHeight()", asFUNCTION(Desktop::Height), asCALL_CDECL);

    // Input
    sdk->RegisterGlobal("const int MOUSE_LEFT", &mouseLeft);
    sdk->RegisterGlobal("const int MOUSE_RIGHT", &mouseRight);
    sdk->RegisterGlobal("const int MOUSE_MIDDLE", &mouseMiddle);
    sdk->RegisterGlobal("const int KEY_A", &KEY_A);
    sdk->RegisterGlobal("const int KEY_B", &KEY_B);
    sdk->RegisterGlobal("const int KEY_C", &KEY_C);
    sdk->RegisterGlobal("const int KEY_D", &KEY_D);
    sdk->RegisterGlobal("const int KEY_E", &KEY_E);
    sdk->RegisterGlobal("const int KEY_F", &KEY_F);
    sdk->RegisterGlobal("const int KEY_G", &KEY_G);
    sdk->RegisterGlobal("const int KEY_H", &KEY_H);
    sdk->RegisterGlobal("const int KEY_I", &KEY_I);
    sdk->RegisterGlobal("const int KEY_J", &KEY_J);
    sdk->RegisterGlobal("const int KEY_K", &KEY_K);
    sdk->RegisterGlobal("const int KEY_L", &KEY_L);
    sdk->RegisterGlobal("const int KEY_M", &KEY_M);
    sdk->RegisterGlobal("const int KEY_N", &KEY_N);
    sdk->RegisterGlobal("const int KEY_O", &KEY_O);
    sdk->RegisterGlobal("const int KEY_P", &KEY_P);
    sdk->RegisterGlobal("const int KEY_Q", &KEY_Q);
    sdk->RegisterGlobal("const int KEY_R", &KEY_R);
    sdk->RegisterGlobal("const int KEY_S", &KEY_S);
    sdk->RegisterGlobal("const int KEY_T", &KEY_T);
    sdk->RegisterGlobal("const int KEY_U", &KEY_U);
    sdk->RegisterGlobal("const int KEY_V", &KEY_V);
    sdk->RegisterGlobal("const int KEY_W", &KEY_W);
    sdk->RegisterGlobal("const int KEY_X", &KEY_X);
    sdk->RegisterGlobal("const int KEY_Y", &KEY_Y);
    sdk->RegisterGlobal("const int KEY_Z", &KEY_Z);
    sdk->RegisterGlobal("const int KEY_1", &KEY_1);
    sdk->RegisterGlobal("const int KEY_2", &KEY_2);
    sdk->RegisterGlobal("const int KEY_3", &KEY_3);
    sdk->RegisterGlobal("const int KEY_4", &KEY_4);
    sdk->RegisterGlobal("const int KEY_5", &KEY_5);
    sdk->RegisterGlobal("const int KEY_6", &KEY_6);
    sdk->RegisterGlobal("const int KEY_7", &KEY_7);
    sdk->RegisterGlobal("const int KEY_8", &KEY_8);
    sdk->RegisterGlobal("const int KEY_9", &KEY_9);
    sdk->RegisterGlobal("const int KEY_0", &KEY_0);
    sdk->RegisterGlobal("const int KEY_RETURN", &KEY_RETURN);
    sdk->RegisterGlobal("const int KEY_ESCAPE", &KEY_ESCAPE);
    sdk->RegisterGlobal("const int KEY_BACKSPACE", &KEY_BACKSPACE);
    sdk->RegisterGlobal("const int KEY_TAB", &KEY_TAB);
    sdk->RegisterGlobal("const int KEY_SPACE", &KEY_SPACE);
    sdk->RegisterGlobal("const int KEY_MINUS", &KEY_MINUS);
    sdk->RegisterGlobal("const int KEY_EQUALS", &KEY_EQUALS);
    sdk->RegisterGlobal("const int KEY_LEFTBRACKET", &KEY_LEFTBRACKET);
    sdk->RegisterGlobal("const int KEY_RIGHTBRACKET", &KEY_RIGHTBRACKET);
    sdk->RegisterGlobal("const int KEY_BACKSLASH", &KEY_BACKSLASH);
    sdk->RegisterGlobal("const int KEY_NONUSHASH", &KEY_NONUSHASH);
    sdk->RegisterGlobal("const int KEY_SEMICOLON", &KEY_SEMICOLON);
    sdk->RegisterGlobal("const int KEY_APOSTROPHE", &KEY_APOSTROPHE);
    sdk->RegisterGlobal("const int KEY_GRAVE", &KEY_GRAVE);
    sdk->RegisterGlobal("const int KEY_COMMA", &KEY_COMMA);
    sdk->RegisterGlobal("const int KEY_PERIOD", &KEY_PERIOD);
    sdk->RegisterGlobal("const int KEY_SLASH", &KEY_SLASH);
    sdk->RegisterGlobal("const int KEY_CAPSLOCK", &KEY_CAPSLOCK);
    sdk->RegisterGlobal("const int KEY_F1", &KEY_F1);
    sdk->RegisterGlobal("const int KEY_F2", &KEY_F2);
    sdk->RegisterGlobal("const int KEY_F3", &KEY_F3);
    sdk->RegisterGlobal("const int KEY_F4", &KEY_F4);
    sdk->RegisterGlobal("const int KEY_F5", &KEY_F5);
    sdk->RegisterGlobal("const int KEY_F6", &KEY_F6);
    sdk->RegisterGlobal("const int KEY_F7", &KEY_F7);
    sdk->RegisterGlobal("const int KEY_F8", &KEY_F8);
    sdk->RegisterGlobal("const int KEY_F9", &KEY_F9);
    sdk->RegisterGlobal("const int KEY_F10", &KEY_F10);
    sdk->RegisterGlobal("const int KEY_F11", &KEY_F11);
    sdk->RegisterGlobal("const int KEY_F12", &KEY_F12);
    sdk->RegisterGlobal("const int KEY_PRINTSCREEN", &KEY_PRINTSCREEN);
    sdk->RegisterGlobal("const int KEY_SCROLLLOCK", &KEY_SCROLLLOCK);
    sdk->RegisterGlobal("const int KEY_PAUSE", &KEY_PAUSE);
    sdk->RegisterGlobal("const int KEY_INSERT", &KEY_INSERT);
    sdk->RegisterGlobal("const int KEY_HOME", &KEY_HOME);
    sdk->RegisterGlobal("const int KEY_PAGEUP", &KEY_PAGEUP);
    sdk->RegisterGlobal("const int KEY_DELETE", &KEY_DELETE);
    sdk->RegisterGlobal("const int KEY_END", &KEY_END);
    sdk->RegisterGlobal("const int KEY_PAGEDOWN", &KEY_PAGEDOWN);
    sdk->RegisterGlobal("const int KEY_RIGHT", &KEY_RIGHT);
    sdk->RegisterGlobal("const int KEY_LEFT", &KEY_LEFT);
    sdk->RegisterGlobal("const int KEY_DOWN", &KEY_DOWN);
    sdk->RegisterGlobal("const int KEY_UP", &KEY_UP);
    sdk->RegisterGlobal("const int KEY_NUMLOCKCLEAR", &KEY_NUMLOCKCLEAR);
    sdk->RegisterGlobal("const int KEY_KP_DIVIDE", &KEY_KP_DIVIDE);
    sdk->RegisterGlobal("const int KEY_KP_MULTIPLY", &KEY_KP_MULTIPLY);
    sdk->RegisterGlobal("const int KEY_KP_MINUS", &KEY_KP_MINUS);
    sdk->RegisterGlobal("const int KEY_KP_PLUS", &KEY_KP_PLUS);
    sdk->RegisterGlobal("const int KEY_KP_ENTER", &KEY_KP_ENTER);
    sdk->RegisterGlobal("const int KEY_KP_1", &KEY_KP_1);
    sdk->RegisterGlobal("const int KEY_KP_2", &KEY_KP_2);
    sdk->RegisterGlobal("const int KEY_KP_3", &KEY_KP_3);
    sdk->RegisterGlobal("const int KEY_KP_4", &KEY_KP_4);
    sdk->RegisterGlobal("const int KEY_KP_5", &KEY_KP_5);
    sdk->RegisterGlobal("const int KEY_KP_6", &KEY_KP_6);
    sdk->RegisterGlobal("const int KEY_KP_7", &KEY_KP_7);
    sdk->RegisterGlobal("const int KEY_KP_8", &KEY_KP_8);
    sdk->RegisterGlobal("const int KEY_KP_9", &KEY_KP_9);
    sdk->RegisterGlobal("const int KEY_KP_0", &KEY_KP_0);
    sdk->RegisterGlobal("const int KEY_KP_PERIOD", &KEY_KP_PERIOD);
    sdk->RegisterGlobal("const int KEY_NONUSBACKSLASH", &KEY_NONUSBACKSLASH);
    sdk->RegisterGlobal("const int KEY_APPLICATION", &KEY_APPLICATION);
    sdk->RegisterGlobal("const int KEY_POWER", &KEY_POWER);
    sdk->RegisterGlobal("const int KEY_KP_EQUALS", &KEY_KP_EQUALS);
    sdk->RegisterGlobal("const int KEY_F13", &KEY_F13);
    sdk->RegisterGlobal("const int KEY_F14", &KEY_F14);
    sdk->RegisterGlobal("const int KEY_F15", &KEY_F15);
    sdk->RegisterGlobal("const int KEY_F16", &KEY_F16);
    sdk->RegisterGlobal("const int KEY_F17", &KEY_F17);
    sdk->RegisterGlobal("const int KEY_F18", &KEY_F18);
    sdk->RegisterGlobal("const int KEY_F19", &KEY_F19);
    sdk->RegisterGlobal("const int KEY_F20", &KEY_F20);
    sdk->RegisterGlobal("const int KEY_F21", &KEY_F21);
    sdk->RegisterGlobal("const int KEY_F22", &KEY_F22);
    sdk->RegisterGlobal("const int KEY_F23", &KEY_F23);
    sdk->RegisterGlobal("const int KEY_F24", &KEY_F24);
    sdk->RegisterGlobal("const int KEY_EXECUTE", &KEY_EXECUTE);
    sdk->RegisterGlobal("const int KEY_HELP", &KEY_HELP);
    sdk->RegisterGlobal("const int KEY_MENU", &KEY_MENU);
    sdk->RegisterGlobal("const int KEY_SELECT", &KEY_SELECT);
    sdk->RegisterGlobal("const int KEY_STOP", &KEY_STOP);
    sdk->RegisterGlobal("const int KEY_AGAIN", &KEY_AGAIN);
    sdk->RegisterGlobal("const int KEY_UNDO", &KEY_UNDO);
    sdk->RegisterGlobal("const int KEY_CUT", &KEY_CUT);
    sdk->RegisterGlobal("const int KEY_COPY", &KEY_COPY);
    sdk->RegisterGlobal("const int KEY_PASTE", &KEY_PASTE);
    sdk->RegisterGlobal("const int KEY_FIND", &KEY_FIND);
    sdk->RegisterGlobal("const int KEY_MUTE", &KEY_MUTE);
    sdk->RegisterGlobal("const int KEY_VOLUMEUP", &KEY_VOLUMEUP);
    sdk->RegisterGlobal("const int KEY_VOLUMEDOWN", &KEY_VOLUMEDOWN);
    sdk->RegisterGlobal("const int KEY_KP_COMMA", &KEY_KP_COMMA);
    sdk->RegisterGlobal("const int KEY_KP_EQUALSAS400", &KEY_KP_EQUALSAS400);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL1", &KEY_INTERNATIONAL1);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL2", &KEY_INTERNATIONAL2);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL3", &KEY_INTERNATIONAL3);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL4", &KEY_INTERNATIONAL4);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL5", &KEY_INTERNATIONAL5);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL6", &KEY_INTERNATIONAL6);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL7", &KEY_INTERNATIONAL7);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL8", &KEY_INTERNATIONAL8);
    sdk->RegisterGlobal("const int KEY_INTERNATIONAL9", &KEY_INTERNATIONAL9);
    sdk->RegisterGlobal("const int KEY_LANG1", &KEY_LANG1);
    sdk->RegisterGlobal("const int KEY_LANG2", &KEY_LANG2);
    sdk->RegisterGlobal("const int KEY_LANG3", &KEY_LANG3);
    sdk->RegisterGlobal("const int KEY_LANG4", &KEY_LANG4);
    sdk->RegisterGlobal("const int KEY_LANG5", &KEY_LANG5);
    sdk->RegisterGlobal("const int KEY_LANG6", &KEY_LANG6);
    sdk->RegisterGlobal("const int KEY_LANG7", &KEY_LANG7);
    sdk->RegisterGlobal("const int KEY_LANG8", &KEY_LANG8);
    sdk->RegisterGlobal("const int KEY_LANG9", &KEY_LANG9);
    sdk->RegisterGlobal("const int KEY_ALTERASE", &KEY_ALTERASE);
    sdk->RegisterGlobal("const int KEY_SYSREQ", &KEY_SYSREQ);
    sdk->RegisterGlobal("const int KEY_CANCEL", &KEY_CANCEL);
    sdk->RegisterGlobal("const int KEY_CLEAR", &KEY_CLEAR);
    sdk->RegisterGlobal("const int KEY_PRIOR", &KEY_PRIOR);
    sdk->RegisterGlobal("const int KEY_RETURN2", &KEY_RETURN2);
    sdk->RegisterGlobal("const int KEY_SEPARATOR", &KEY_SEPARATOR);
    sdk->RegisterGlobal("const int KEY_OUT", &KEY_OUT);
    sdk->RegisterGlobal("const int KEY_OPER", &KEY_OPER);
    sdk->RegisterGlobal("const int KEY_CLEARAGAIN", &KEY_CLEARAGAIN);
    sdk->RegisterGlobal("const int KEY_CRSEL", &KEY_CRSEL);
    sdk->RegisterGlobal("const int KEY_EXSEL", &KEY_EXSEL);
    sdk->RegisterGlobal("const int KEY_KP_00", &KEY_KP_00);
    sdk->RegisterGlobal("const int KEY_KP_000", &KEY_KP_000);
    sdk->RegisterGlobal("const int KEY_THOUSANDSSEPARATOR", &KEY_THOUSANDSSEPARATOR);
    sdk->RegisterGlobal("const int KEY_DECIMALSEPARATOR", &KEY_DECIMALSEPARATOR);
    sdk->RegisterGlobal("const int KEY_CURRENCYUNIT", &KEY_CURRENCYUNIT);
    sdk->RegisterGlobal("const int KEY_CURRENCYSUBUNIT", &KEY_CURRENCYSUBUNIT);
    sdk->RegisterGlobal("const int KEY_KP_LEFTPAREN", &KEY_KP_LEFTPAREN);
    sdk->RegisterGlobal("const int KEY_KP_RIGHTPAREN", &KEY_KP_RIGHTPAREN);
    sdk->RegisterGlobal("const int KEY_KP_LEFTBRACE", &KEY_KP_LEFTBRACE);
    sdk->RegisterGlobal("const int KEY_KP_RIGHTBRACE", &KEY_KP_RIGHTBRACE);
    sdk->RegisterGlobal("const int KEY_KP_TAB", &KEY_KP_TAB);
    sdk->RegisterGlobal("const int KEY_KP_BACKSPACE", &KEY_KP_BACKSPACE);
    sdk->RegisterGlobal("const int KEY_KP_A", &KEY_KP_A);
    sdk->RegisterGlobal("const int KEY_KP_B", &KEY_KP_B);
    sdk->RegisterGlobal("const int KEY_KP_C", &KEY_KP_C);
    sdk->RegisterGlobal("const int KEY_KP_D", &KEY_KP_D);
    sdk->RegisterGlobal("const int KEY_KP_E", &KEY_KP_E);
    sdk->RegisterGlobal("const int KEY_KP_F", &KEY_KP_F);
    sdk->RegisterGlobal("const int KEY_KP_XOR", &KEY_KP_XOR);
    sdk->RegisterGlobal("const int KEY_KP_POWER", &KEY_KP_POWER);
    sdk->RegisterGlobal("const int KEY_KP_PERCENT", &KEY_KP_PERCENT);
    sdk->RegisterGlobal("const int KEY_KP_LESS", &KEY_KP_LESS);
    sdk->RegisterGlobal("const int KEY_KP_GREATER", &KEY_KP_GREATER);
    sdk->RegisterGlobal("const int KEY_KP_AMPERSAND", &KEY_KP_AMPERSAND);
    sdk->RegisterGlobal("const int KEY_KP_DBLAMPERSAND", &KEY_KP_DBLAMPERSAND);
    sdk->RegisterGlobal("const int KEY_KP_VERTICALBAR", &KEY_KP_VERTICALBAR);
    sdk->RegisterGlobal("const int KEY_KP_DBLVERTICALBAR", &KEY_KP_DBLVERTICALBAR);
    sdk->RegisterGlobal("const int KEY_KP_COLON", &KEY_KP_COLON);
    sdk->RegisterGlobal("const int KEY_KP_HASH", &KEY_KP_HASH);
    sdk->RegisterGlobal("const int KEY_KP_SPACE", &KEY_KP_SPACE);
    sdk->RegisterGlobal("const int KEY_KP_AT", &KEY_KP_AT);
    sdk->RegisterGlobal("const int KEY_KP_EXCLAM", &KEY_KP_EXCLAM);
    sdk->RegisterGlobal("const int KEY_KP_MEMSTORE", &KEY_KP_MEMSTORE);
    sdk->RegisterGlobal("const int KEY_KP_MEMRECALL", &KEY_KP_MEMRECALL);
    sdk->RegisterGlobal("const int KEY_KP_MEMCLEAR", &KEY_KP_MEMCLEAR);
    sdk->RegisterGlobal("const int KEY_KP_MEMADD", &KEY_KP_MEMADD);
    sdk->RegisterGlobal("const int KEY_KP_MEMSUBTRACT", &KEY_KP_MEMSUBTRACT);
    sdk->RegisterGlobal("const int KEY_KP_MEMMULTIPLY", &KEY_KP_MEMMULTIPLY);
    sdk->RegisterGlobal("const int KEY_KP_MEMDIVIDE", &KEY_KP_MEMDIVIDE);
    sdk->RegisterGlobal("const int KEY_KP_PLUSMINUS", &KEY_KP_PLUSMINUS);
    sdk->RegisterGlobal("const int KEY_KP_CLEAR", &KEY_KP_CLEAR);
    sdk->RegisterGlobal("const int KEY_KP_CLEARENTRY", &KEY_KP_CLEARENTRY);
    sdk->RegisterGlobal("const int KEY_KP_BINARY", &KEY_KP_BINARY);
    sdk->RegisterGlobal("const int KEY_KP_OCTAL", &KEY_KP_OCTAL);
    sdk->RegisterGlobal("const int KEY_KP_DECIMAL", &KEY_KP_DECIMAL);
    sdk->RegisterGlobal("const int KEY_KP_HEXADECIMAL", &KEY_KP_HEXADECIMAL);
    sdk->RegisterGlobal("const int KEY_LCTRL", &KEY_LCTRL);
    sdk->RegisterGlobal("const int KEY_LSHIFT", &KEY_LSHIFT);
    sdk->RegisterGlobal("const int KEY_LALT", &KEY_LALT);
    sdk->RegisterGlobal("const int KEY_LGUI", &KEY_LGUI);
    sdk->RegisterGlobal("const int KEY_RCTRL", &KEY_RCTRL);
    sdk->RegisterGlobal("const int KEY_RSHIFT", &KEY_RSHIFT);
    sdk->RegisterGlobal("const int KEY_RALT", &KEY_RALT);
    sdk->RegisterGlobal("const int KEY_RGUI", &KEY_RGUI);
    sdk->RegisterGlobal("const int KEY_MODE", &KEY_MODE);
    sdk->RegisterGlobal("const int KEY_AUDIONEXT", &KEY_AUDIONEXT);
    sdk->RegisterGlobal("const int KEY_AUDIOPREV", &KEY_AUDIOPREV);
    sdk->RegisterGlobal("const int KEY_AUDIOSTOP", &KEY_AUDIOSTOP);
    sdk->RegisterGlobal("const int KEY_AUDIOPLAY", &KEY_AUDIOPLAY);
    sdk->RegisterGlobal("const int KEY_AUDIOMUTE", &KEY_AUDIOMUTE);
    sdk->RegisterGlobal("const int KEY_MEDIASELECT", &KEY_MEDIASELECT);
    sdk->RegisterGlobal("const int KEY_WWW", &KEY_WWW);
    sdk->RegisterGlobal("const int KEY_MAIL", &KEY_MAIL);
    sdk->RegisterGlobal("const int KEY_CALCULATOR", &KEY_CALCULATOR);
    sdk->RegisterGlobal("const int KEY_COMPUTER", &KEY_COMPUTER);
    sdk->RegisterGlobal("const int KEY_AC_SEARCH", &KEY_AC_SEARCH);
    sdk->RegisterGlobal("const int KEY_AC_HOME", &KEY_AC_HOME);
    sdk->RegisterGlobal("const int KEY_AC_BACK", &KEY_AC_BACK);
    sdk->RegisterGlobal("const int KEY_AC_FORWARD", &KEY_AC_FORWARD);
    sdk->RegisterGlobal("const int KEY_AC_STOP", &KEY_AC_STOP);
    sdk->RegisterGlobal("const int KEY_AC_REFRESH", &KEY_AC_REFRESH);
    sdk->RegisterGlobal("const int KEY_AC_BOOKMARKS", &KEY_AC_BOOKMARKS);
    sdk->RegisterGlobal("const int KEY_BRIGHTNESSDOWN", &KEY_BRIGHTNESSDOWN);
    sdk->RegisterGlobal("const int KEY_BRIGHTNESSUP", &KEY_BRIGHTNESSUP);
    sdk->RegisterGlobal("const int KEY_DISPLAYSWITCH", &KEY_DISPLAYSWITCH);
    sdk->RegisterGlobal("const int KEY_KBDILLUMTOGGLE", &KEY_KBDILLUMTOGGLE);
    sdk->RegisterGlobal("const int KEY_KBDILLUMDOWN", &KEY_KBDILLUMDOWN);
    sdk->RegisterGlobal("const int KEY_KBDILLUMUP", &KEY_KBDILLUMUP);
    sdk->RegisterGlobal("const int KEY_EJECT", &KEY_EJECT);
    sdk->RegisterGlobal("const int KEY_SLEEP", &KEY_SLEEP);
    sdk->RegisterGlobal("const int KEY_APP1", &KEY_APP1);
    sdk->RegisterGlobal("const int KEY_APP2", &KEY_APP2);
    sdk->RegisterFunction("void ShowMouse(bool)", asFUNCTION(Input::ShowMouse), asCALL_CDECL);
    sdk->RegisterFunction("void MoveMouse(int, int)", asFUNCTION(Input::MoveMouse), asCALL_CDECL);
    sdk->RegisterFunction("int MouseX()", asFUNCTION(Input::MouseX), asCALL_CDECL);
    sdk->RegisterFunction("int MouseY()", asFUNCTION(Input::MouseY), asCALL_CDECL);
    sdk->RegisterFunction("bool MouseButtonPressed(int)", asFUNCTION(Input::MouseButtonPressed), asCALL_CDECL);
    sdk->RegisterFunction("bool KeyPressed(int)", asFUNCTION(Input::KeyPressed), asCALL_CDECL);

    // Music
    sdk->RegisterFunction("bool LoadMusic(const String& in)", asFUNCTION(Music::Load), asCALL_CDECL);
    sdk->RegisterFunction("void FreeMusic()", asFUNCTION(Music::Free), asCALL_CDECL);
    sdk->RegisterFunction("void PlayMusic()", asFUNCTION(Music::Play), asCALL_CDECL);
    sdk->RegisterFunction("void LoopMusic()", asFUNCTION(Music::Loop), asCALL_CDECL);
    sdk->RegisterFunction("void StopMusic()", asFUNCTION(Music::Stop), asCALL_CDECL);
    sdk->RegisterFunction("void PauseMusic()", asFUNCTION(Music::Pause), asCALL_CDECL);
    sdk->RegisterFunction("void ResumeMusic()", asFUNCTION(Music::Resume), asCALL_CDECL);
    sdk->RegisterFunction("void SetMusicVolume(float)", asFUNCTION(Music::SetVolume), asCALL_CDECL);
    sdk->RegisterFunction("bool IsMusicPlaying()", asFUNCTION(Music::IsPlaying), asCALL_CDECL);

    // Pixmap
    sdk->RegisterClass("Pixmap", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Pixmap", asBEHAVE_FACTORY, "Pixmap@ f(uint, uint, int)", asFUNCTION(PixmapFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Pixmap", asBEHAVE_FACTORY, "Pixmap@ f(const String& in)", asFUNCTION(PixmapFactory2), asCALL_CDECL);
    sdk->RegisterBehaviour("Pixmap", asBEHAVE_FACTORY, "Pixmap@ f(const String& in, float)", asFUNCTION(PixmapFactory3), asCALL_CDECL);
    sdk->RegisterBehaviour("Pixmap", asBEHAVE_ADDREF, "void f()", asMETHOD(Pixmap, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Pixmap", asBEHAVE_RELEASE, "void f()", asMETHOD(Pixmap, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Pixmap", "bool IsLoaded() const", asMETHOD(Pixmap, IsLoaded), asCALL_THISCALL);
    sdk->RegisterMethod("Pixmap", "MemBuffer& Buffer()", asMETHOD(Pixmap, Buffer), asCALL_THISCALL);
    sdk->RegisterMethod("Pixmap", "uint Width() const", asMETHOD(Pixmap, Width), asCALL_THISCALL);
    sdk->RegisterMethod("Pixmap", "uint Height() const", asMETHOD(Pixmap, Height), asCALL_THISCALL);
    sdk->RegisterMethod("Pixmap", "bool Write(const String& in) const", asMETHOD(Pixmap, Write), asCALL_THISCALL);

    // Renderer
    sdk->RegisterGlobal("const int BLEND_SOLID", &blendSolid);
    sdk->RegisterGlobal("const int BLEND_ALPHA", &blendAlpha);
    sdk->RegisterGlobal("const int BLEND_ADD", &blendAdd);
    sdk->RegisterGlobal("const int BLEND_MODULATE", &blendModulate);
    sdk->RegisterFunction("void SetOrigin(double, double)", asFUNCTION(Renderer::SetOrigin), asCALL_CDECL);
    sdk->RegisterFunction("void SetViewport(int, int, int, int)", asFUNCTION(Renderer::SetViewport), asCALL_CDECL);
    sdk->RegisterFunction("void SetBlendMode(int)", asFUNCTION(Renderer::SetBlendMode), asCALL_CDECL);
    sdk->RegisterFunction("void SetColor(int)", asFUNCTION(Renderer::SetColor), asCALL_CDECL);
    sdk->RegisterFunction("int Color(uint8, uint8, uint8, uint8 = 255)", asFUNCTION(Renderer::Color), asCALL_CDECL);
    sdk->RegisterFunction("uint8 Red(int)", asFUNCTION(Renderer::Red), asCALL_CDECL);
    sdk->RegisterFunction("uint8 Green(int)", asFUNCTION(Renderer::Green), asCALL_CDECL);
    sdk->RegisterFunction("uint8 Blue(int)", asFUNCTION(Renderer::Blue), asCALL_CDECL);
    sdk->RegisterFunction("uint8 Alpha(int)", asFUNCTION(Renderer::Alpha), asCALL_CDECL);
    sdk->RegisterFunction("void DrawPoint(double, double)", asFUNCTION(Renderer::DrawPoint), asCALL_CDECL);
    sdk->RegisterFunction("void DrawLine(double, double, double, double)", asFUNCTION(Renderer::DrawLine), asCALL_CDECL);
    sdk->RegisterFunction("void DrawRect(double, double, double, double)", asFUNCTION(Renderer::DrawRect), asCALL_CDECL);
    sdk->RegisterFunction("void DrawEllipse(double, double, double, double)", asFUNCTION(Renderer::DrawEllipse), asCALL_CDECL);

    // Screen
    sdk->RegisterFunction("void OpenScreen(int, int, bool)", asFUNCTION(OpenScreen), asCALL_CDECL);
    sdk->RegisterFunction("void CloseScreen()", asFUNCTION(CloseScreen), asCALL_CDECL);
    sdk->RegisterFunction("bool ScreenOpened()", asFUNCTION(ScreenOpened), asCALL_CDECL);
    sdk->RegisterFunction("void ClearScreen(int = 0)", asFUNCTION(ClearScreen), asCALL_CDECL);
    sdk->RegisterFunction("void RefreshScreen()", asFUNCTION(RefreshScreen), asCALL_CDECL);
    sdk->RegisterFunction("int ScreenWidth()", asFUNCTION(ScreenWidth), asCALL_CDECL);
    sdk->RegisterFunction("int ScreenHeight()", asFUNCTION(ScreenHeight), asCALL_CDECL);
    sdk->RegisterFunction("int ScreenFPS()", asFUNCTION(ScreenFPS), asCALL_CDECL);
    sdk->RegisterFunction("double DeltaTime()", asFUNCTION(DeltaTime), asCALL_CDECL);

    // Sound
    sdk->RegisterClass("Sound", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Sound", asBEHAVE_FACTORY, "Sound@ f(const String& in)", asFUNCTION(SoundFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Sound", asBEHAVE_ADDREF, "void f()", asMETHOD(Sound, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Sound", asBEHAVE_RELEASE, "void f()", asMETHOD(Sound, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Sound", "bool IsLoaded() const", asMETHOD(Sound, IsLoaded), asCALL_THISCALL);
    sdk->RegisterMethod("Sound", "Channel@ Play()", asMETHOD(Sound, Play), asCALL_THISCALL);
    sdk->RegisterMethod("Sound", "Channel@ Loop()", asMETHOD(Sound, Loop), asCALL_THISCALL);

    // Image (requires Pixmap)
    sdk->RegisterClass("Image", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Image", asBEHAVE_FACTORY, "Image@ f(const Pixmap& in, int, int)", asFUNCTION(ImageFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Image", asBEHAVE_FACTORY, "Image@ f(const String& in, int = 1, int = 1)", asFUNCTION(ImageFactory2), asCALL_CDECL);
    sdk->RegisterBehaviour("Image", asBEHAVE_ADDREF, "void f()", asMETHOD(Image, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Image", asBEHAVE_RELEASE, "void f()", asMETHOD(Image, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "bool IsLoaded() const", asMETHOD(Image, IsLoaded), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "void Draw(double, double, int = 0, double = 0.0, double = 0.0, double = 0.0, double = 0.0, double = 0.0, double = 0.0, double = 0.0)", asMETHOD(Image, Draw), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "void DrawTiled(double, double, double, double, double, double)", asMETHOD(Image, DrawTiled), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int Frames() const", asMETHOD(Image, Frames), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int HFrames() const", asMETHOD(Image, HFrames), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int VFrames() const", asMETHOD(Image, VFrames), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int Width() const", asMETHOD(Image, Width), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int Height() const", asMETHOD(Image, Height), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "void SetHandle(int, int)", asMETHOD(Image, SetHandle), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int HandleX() const", asMETHOD(Image, HandleX), asCALL_THISCALL);
    sdk->RegisterMethod("Image", "int HandleY() const", asMETHOD(Image, HandleY), asCALL_THISCALL);

    // Font (requires Pixmap)
    sdk->RegisterClass("Font", 0, asOBJ_REF);
    //sdk->RegisterBehaviour("Font", asBEHAVE_FACTORY, "Font@ f(const Pixmap& in)", asFUNCTION(FontFactory), asCALL_CDECL);
    //sdk->RegisterBehaviour("Font", asBEHAVE_FACTORY, "Font@ f(const String& in)", asFUNCTION(FontFactory2), asCALL_CDECL);
    sdk->RegisterBehaviour("Font", asBEHAVE_FACTORY, "Font@ f(const String& in, float, uint = 512)", asFUNCTION(FontFactory3), asCALL_CDECL);
    sdk->RegisterBehaviour("Font", asBEHAVE_ADDREF, "void f()", asMETHOD(Font, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Font", asBEHAVE_RELEASE, "void f()", asMETHOD(Font, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Font", "bool IsLoaded() const", asMETHOD(Font, IsLoaded), asCALL_THISCALL);
    sdk->RegisterMethod("Font", "int Size() const", asMETHOD(Font, Size), asCALL_THISCALL);
    sdk->RegisterMethod("Font", "int TextWidth(const String& in) const", asMETHOD(Font, TextWidth), asCALL_THISCALL);
    sdk->RegisterMethod("Font", "int TextHeight(const String& in) const", asMETHOD(Font, TextHeight), asCALL_THISCALL);
    sdk->RegisterMethod("Font", "void Draw(const String& in, double, double)", asMETHODPR(Font, Draw, (const String&, double, double), void), asCALL_THISCALL);
}
