#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include "array.h"
#include "string.h"
#include <stdlib.h>
#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

#define PLATFORM_WINDOWS    1
#define PLATFORM_MAC        2
#define PLATFORM_LINUX      3

class System {
public:
    static int PlatformId();
    static const String& ProgramName() { return programName; }
    static const Array<String>& CommandLine() { return commandLine; }
    static String GetEnv(const String& var) { return getenv(var.ToCString()); }
    static int SystemCall(const String& command) { return system(command.ToCString()); }
    static String RunProgram(const String& program);
    static void Exit(int exitCode) { exit(exitCode); }

    // Call them on the main function and never again
    static void SetProgramName(const char* name) { programName = name; }
    static void SetCommandLine(int num, const char* args[]) { commandLine.Clear(); for ( int i = 0; i < num; i++ ) commandLine.Add(args[i]); }
protected:
    System() {}
private:
    static String programName;
    static Array<String> commandLine;
};

inline int System::PlatformId() {
#if defined(_WIN32)
    return PLATFORM_WINDOWS;
#elif defined(__APPLE__)
    return PLATFORM_MAC;
#elif defined(__linux__)
    return PLATFORM_LINUX;
#else
    return 0;
#endif
}

inline String System::RunProgram(const String& program) {
    String output;

    // Open pipe
    FILE* pipe = popen(program.ToCString(), "rt");
    if ( !pipe ) return "";

    // Read pipe
    while ( !feof(pipe) ) {
        char tmp[128];
        if ( fgets(tmp, 128, pipe) != 0 ) output += tmp;
    }

    // Close pipe
    pclose(pipe);

    return output;
}

#ifdef _WIN32
#undef popen
#undef pclose
#endif

#endif // CORE_SYSTEM_H
