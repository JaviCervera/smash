#include "../sdk/angelscript.h"
#include "scriptbuilder.h"
#include "../common/bytecodestream.h"
#include "../mod_core/console.h"
#include "../mod_core/dir.h"
#include "../mod_core/file.h"
#include "../mod_core/library.h"
#include "../mod_core/string.h"
#include "../mod_core/system.h"
#include "../mod_core/time.h"
#include "../sdk/smashsdk.h"

enum ErrorCode {
	NO_ERROR = 0,
	ERROR_USAGE = -1,
	ERROR_CALLBACK = -2,
	ERROR_MODULE = -3,
	ERROR_BUILDER = -4,
	ERROR_LOAD = -5,
	ERROR_COMPILER = -6,
	ERROR_STUB = -7,
	ERROR_RUNTIME = -8
};

enum BuildMode {
	MODE_CHECK,
	MODE_BUILD,
	MODE_RUN
};

extern unsigned int iconSize;
extern unsigned char iconData[];

SmashSDK* CreateSDK(asIScriptEngine* engine, asIScriptContext* context, int argc, const char** argv);

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
	unsigned long startTime = Time::Millisecs();

	// Define platform
	String platform = "";
#if defined(_WIN32)
	platform = ".win32";
#elif defined(__APPLE__)
	platform = ".mac";
#elif defined(linux)
	platform = ".linux";
#endif

	// Check command line
	if ( argc < 2 ) {
		Console::Print(String("Usage: ") + String(argv[0]).StripDir() + " [options] sourcefile\n");
		Console::Print("Options:\n");
		Console::Print("-check: Check syntax (do not generate output)\n");
		Console::Print("-run: Run program\n");
		Console::Print("-console: Build app with console window\n");
		return ERROR_USAGE;
	}

	// Get command line options
	bool consoleMode = false;
	BuildMode buildMode = MODE_BUILD;
	for ( int i = 1; i < argc-1; i++ ) {
		if ( String(argv[i]) == "-check" ) {
			buildMode = MODE_CHECK;
		} else if ( String(argv[i]) == "-run" ) {
			buildMode = MODE_RUN;
		} else if ( String(argv[i]) == "-console" ) {
			consoleMode = true;
		} else {
			Console::Print(String("ERROR: Invalid option ") + argv[i] + "\n");
			return ERROR_USAGE;
		}
	}

	// Get filename and directories
	String sourceFilename = String(argv[argc-1]).RealPath();
	String launchDir = Dir::Current();
	String appDir = String(argv[0]).RealPath().ExtractDir();
	String sourceDir = sourceFilename.ExtractDir();

	// Create the script engine
	asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	// Set the message callback to receive information on errors in human readable form
	if ( engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL) < 0 ) {
		Console::Print("ERROR: Could not set message callback\n");
		return ERROR_CALLBACK;
	}

	// Create engine context
	asIScriptContext* context = engine->CreateContext();

	// Create script builder
	ScriptBuilder builder;

	// Create main script module
	if ( builder.StartNewModule(engine, "MainModule") < 0 ) {
		return ERROR_MODULE;
	}

	// Add script to builder
	Console::Print(String("Compiling '") + sourceFilename + "'...\n");
	if ( builder.AddSectionFromFile(sourceFilename.ToCString()) < 0 ) {
		Console::Print("ERROR: Could not add source file to context\n");
		return ERROR_BUILDER;
	}

	// Load all used modules
	Dir::Change(appDir);
	SmashSDK* sdk = CreateSDK(engine, context, argc, (const char**)argv);
	Array<Library*> loadedModules;
	for ( int i = 0; i < builder.GetLoadedModules().Size(); i++ ) {
		Console::Print(String("Loading module '") + builder.GetLoadedModules()[i] + "'...\n");

		// Get filename
		String filename = String("../modules").RealPath() + "/smash." + builder.GetLoadedModules()[i] + platform;

		// Load library
		Library* lib = new Library(filename);
		if ( lib->IsOpened() ) {
			// Register module
			void* funcPtr = lib->Function("LoadModule");
			if ( funcPtr ) {
				lib->PushObject(sdk);
				lib->CallVoidFunctionC(funcPtr);
			} else {
				Console::Print(String("ERROR: 'LoadModule' function not found in '") + builder.GetLoadedModules()[i] + "' module\n");
				return ERROR_LOAD;
			}
		} else {
			Console::Print(String("ERROR: Could not load module '") + builder.GetLoadedModules()[i] + "'\n");
			return ERROR_LOAD;
		}

		// Add to modules list
		loadedModules.Add(lib);
	}
	Dir::Change(launchDir);
	Console::Print("Done loading modules\n");

	// Build script module
	if ( builder.BuildModule() < 0 ) {
		return ERROR_COMPILER;
	}

	// Build bytecode if in build mode
	if ( buildMode == MODE_BUILD ) {
		String bytecodeFilename = sourceFilename.StripExt() + platform;
#if defined(_WIN32)
		String stubFilename = "stub.win32";
		if ( consoleMode ) stubFilename = "stub.win32_console";
		bytecodeFilename += ".exe";
#elif defined(__APPLE__)
		String stubFilename = "stub.mac";
#elif defined(linux)
		String stubFilename = "stub.linux";
#endif

		// Load stub buffer
		File stubFile(stubFilename, FILE_READ);
		if ( !stubFile.IsOpened() ) {
			Console::Print(String("Error: Could not find stub '") + stubFilename + "'\n");
			return ERROR_STUB;
		}
		unsigned int stubSize = stubFile.Size();
		unsigned char* stubData = (unsigned char*)malloc(stubSize);
		stubFile.ReadBytes(stubData, stubSize);

		Console::Print(String("Writing output executable '") + bytecodeFilename + "'\n");

		BytecodeStream* stream = new BytecodeStream(bytecodeFilename, BytecodeStream::STREAM_OUT);

		// Write stub
		stream->GetFile().WriteBytes(stubData, stubSize);

		// Delete stub buffer
		free(stubData);

		// Write custom modules path
		stream->GetFile().WriteCString("");

		// Write list of modules
		String moduleNames;
		for ( int i = 0; i < builder.GetLoadedModules().Size(); i++ ) {
			if ( moduleNames.Length() > 0 ) moduleNames += "\n";
			moduleNames += builder.GetLoadedModules()[i];
		}
		stream->GetFile().WriteCString(moduleNames);

		// Save bytecode
		Console::Print(String::FromInt(int(builder.GetModule())) + "\n");
		builder.GetModule()->SaveByteCode(stream, true);

		// Write offset
		stream->GetFile().WriteUInt(stubSize);

		// Delete stream (closing the file)
		delete stream;

		// Set execution permissions
#if defined(__APPLE__) || defined(linux)
		System::SystemCall(String("chmod +x \"") + bytecodeFilename + "\"");
#endif

		// Build bundle if needed
#ifdef __APPLE__
		if ( !consoleMode ) {
			String bundleName = bytecodeFilename.StripExt() + ".app";

			bool bundleIsFile = false;
			switch ( File::Type(bundleName) ) {
			case FILETYPE_NONE:
				Console::Print("Creating application bundle\n");
				Dir::Create(bundleName);
				break;
			case FILETYPE_FILE:
				Console::Print("File already exists, skipping bundle generation\n");
				bundleIsFile = true;
				break;
			case FILETYPE_DIR:
				Console::Print("App bundle already exists, reusing\n");
				break;
			}

			if ( !bundleIsFile ) {
				// Create bundle subfolders
				Dir::Create(bundleName + "/Contents");
				Dir::Create(bundleName + "/Contents/MacOS");
				Dir::Create(bundleName + "/Contents/Resources");

				// Move executable
				System::SystemCall(String("mv \"") + bytecodeFilename + "\" \"" + bundleName + "/Contents/MacOS\"");

				// Create .icns file if it does not exist
				String icnsFile = bundleName + "/Contents/Resources/Icon.icns";
				if ( File::Type(icnsFile) == FILETYPE_NONE ) {
					File fhandle(icnsFile, FILE_WRITE);
					fhandle.WriteBytes(iconData, iconSize);
					fhandle.Close();
				}

				// Create Info.plist
				String plistFile = bundleName + "/Contents/Info.plist";
				if ( File::Type(plistFile) == FILETYPE_NONE ) {
					File fhandle(plistFile, FILE_WRITE);
					fhandle.WriteCLine("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
					fhandle.WriteCLine("<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">");
					fhandle.WriteCLine("<plist version=\"1.0\">");
					fhandle.WriteCLine("<dict>");
					fhandle.WriteCLine("\t<key>CFBundleExecutable</key>");
					fhandle.WriteCLine(String("\t<string>") + bytecodeFilename.StripDir() + "</string>");
					fhandle.WriteCLine("\t<key>CFBundleIconFile</key>");
					fhandle.WriteCLine("\t<string>Icon</string>");
					fhandle.WriteCLine("\t<key>CFBundlePackageType</key>");
					fhandle.WriteCLine("\t<string>APPL</string>");
					fhandle.WriteCLine("</dict>");
					fhandle.WriteCLine("</plist>");
					fhandle.Close();
				}
			}
		}
#endif
	}

	Console::Print(String("Done in ") + String::FromFloat((Time::Millisecs() - startTime) / 1000.0f) + " seconds\n");

	// Run script if in run mode
	if ( buildMode == MODE_RUN ) {
		Dir::Change(sourceDir);

		// Call main function or entry point
		if ( !sdk->EntryPoint() ) {
			// Look for main function
			asIScriptFunction* func = builder.GetModule()->GetFunctionByDecl("void Main()");
			if ( !func ) {
				Console::Print("ERROR: void Main() function not found\n");
				return ERROR_RUNTIME;
			}

			// Run program
			context->Prepare(func);
			int ret = context->Execute();
			if ( ret != asEXECUTION_FINISHED ) {
				if ( ret == asEXECUTION_EXCEPTION ) {
					Console::Print(String("Uncaught exception ") + context->GetExceptionString() + "\n");
					return ERROR_RUNTIME;
				}
			}
		} else {
			// Call entry point
			sdk->EntryPoint()();
		}
	}

	/*// Free used modules
	//Console::Print("Freeing modules...\n");
	for ( int i = 0; i < loadedModules.Size(); i++ ) {
		//Console::Print(String("Module ") + String::FromInt(i) + "\n");
		delete loadedModules[i];
	}

	// Release scripting context & engine
	//Console::Print("Releasing scripting engine...\n");
	context->Release();
	engine->Release();*/

	Console::Print("\n");
	return 0;
}
