#include "../sdk/smashsdk.h"
#include "../common/bytecodestream.h"
#include "../mod_core/array.h"
#include "../mod_core/console.h"
#include "../mod_core/dir.h"
#include "../mod_core/file.h"
#include "../mod_core/library.h"
#include "../mod_core/string.h"

SmashSDK* CreateSDK(asIScriptEngine* engine, asIScriptContext* context, int argc, const char** argv);

bool IsBundled(const String& binpath) {
    Array<String> pathComps = binpath.Split("/");
    if ( pathComps.Size() >= 3 ) {
        if ( pathComps[pathComps.Size()-1] == "MacOS" && pathComps[pathComps.Size()-2] == "Contents" && pathComps[pathComps.Size()-3].ExtractExt().Lower() == "app" ) {
            return true;
        }
    }
    return false;
}

String BundlePath(const String& binpath) {
    Array<String> pathComps = binpath.Split("/");
    String path;
    for ( int i = 0; i < pathComps.Size()-3; i++ ) {
        if ( pathComps[i].Length() > 0 ) path += String("/") + pathComps[i];
    }
    return path;
}

void MessageCallback(const asSMessageInfo *msg, void *param) {
    (void)param;
    const char *type = "ERROR";
    if ( msg->type == asMSGTYPE_WARNING )
        type = "WARNING";
    else if ( msg->type == asMSGTYPE_INFORMATION )
        type = "INFO";

    printf("%s (%d, %d) %s: %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

int main(int argc, char* argv[]) {
    // Define platform
    String platform = "";
#if defined(_WIN32)
    platform = ".win32";
#elif defined(__APPLE__)
    platform = ".mac";
#elif defined(linux)
    platform = ".linux";
#endif

    // Create bytecode stream
    BytecodeStream* stream = new BytecodeStream(String(argv[0]).RealPath(), BytecodeStream::STREAM_IN);

    // Move to appended data
    stream->GetFile().Seek(stream->GetFile().Size() - 4);
    stream->GetFile().Seek(stream->GetFile().ReadUInt());

    // Get custom modules path
    String customModPath = stream->GetFile().ReadCString();

    // Get list of used modules
    Array<String> moduleNames = stream->GetFile().ReadCString().Split("\n");

    // Create the script engine
    asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    // Set the message callback to receive information on errors in human readable form.
    if ( engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL) < 0 ) {
        Console::Print("ERROR: Could not set message callback\n");
        return -1;
    }

    // Create context
    asIScriptContext* context = engine->CreateContext();

    // Create main script module
    asIScriptModule* module = engine->GetModule("MainModule", asGM_ALWAYS_CREATE);
    if ( !module ) {
        Console::Print("ERROR: Could not create main module\n");
        return -1;
    }

    // If app is bundled, fix startup dir
#ifdef __APPLE__
    if ( IsBundled(String(argv[0]).RealPath().ExtractDir()) ) Dir::Change(BundlePath(String(argv[0]).RealPath().ExtractDir()));
#endif

    // Load all used modules
    Array<Library*> loadedModules;
    SmashSDK* sdk = CreateSDK(engine, context, argc, (const char**)argv);
    for ( int i = 0; i < moduleNames.Size(); i++ ) {
        Library* lib = NULL;

        // If there is a custom path set, try to laod from there
        if ( customModPath != "" ) {
            lib = new Library(customModPath + "/smash." + moduleNames[i] + platform);
            if ( !lib->IsOpened() ) {
                delete lib;
                lib = NULL;
            }
        }

        // Try to load from current folder
        if ( !lib ) {
            lib = new Library(String("smash.") + moduleNames[i] + platform);
            if ( !lib->IsOpened() ) {
                delete lib;
                lib = NULL;
            }
        }

        // Try to load from modules folder
        if ( !lib ) {
            lib = new Library(String("modules/smash.") + moduleNames[i] + platform);
        }

        // Register modules
        if ( lib->IsOpened() ) {
            void* funcPtr = lib->Function("LoadModule");
            if ( funcPtr ) {
                lib->PushObject(sdk);
                lib->CallVoidFunctionC(funcPtr);
            } else {
                Console::Print(String("ERROR: 'LoadModule' function not found in '") + moduleNames[i] + "' module\n");
                return -1;
            }
        } else {
            Console::Print(String("ERROR: Could not load module '") + moduleNames[i] + "'\n");
            delete lib;
            lib = NULL;
            return -1;
        }
    }

    // Load bytecode
    bool debugInfoStripped = false;
    if ( module->LoadByteCode(stream, &debugInfoStripped) < 0 ) {
        Console::Print("Could not load bytecode\n");
        return -1;
    }
    delete stream;

    // Call main function or entry point
    if ( !sdk->EntryPoint() ) {
        // Look for "void Main()" function
        asIScriptFunction* func = module->GetFunctionByDecl("void Main()");
        if ( !func ) {
            Console::Print("ERROR: void Main() function not found\n");
            return -1;
        }

        // Run program
        context->Prepare(func);
        int ret = context->Execute();
        if ( ret != asEXECUTION_FINISHED ) {
            if ( ret == asEXECUTION_EXCEPTION ) {
                Console::Print(String("Uncaught exception ") + context->GetExceptionString() + "\n");
                return -1;
            }
        }
    } else {
        // Call entry point
        sdk->EntryPoint()();
    }

    // Release context
    context->Release();

    // Release scripting engine
    engine->Release();

    return 0;
}
