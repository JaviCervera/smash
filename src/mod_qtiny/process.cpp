#include "process.h"
#include "event.h"
#include <QProcess>

Process::Process(const String& name) {
    // Parse program name and arguments from first parameter
    Array<String> cmdline = name.Split(" ");
    command = cmdline[0];
    String param = "";
    for ( int i = 1; i < cmdline.Size(); i++ ) {
        param += cmdline[i];

        // If we find quotes, match with closing quote
        if ( param.Left(1) == "\"" ) {
            if (param.Right(1) == "\"" ) {
                params.Add(param.Replace("\"", ""));
                param = "";
            }
        // Else, add new param
        } else {
            params.Add(param.ToCString());
            param = "";
        }
    }

    process = new QProcess();
    QObject::connect(process, SIGNAL(error(QProcess::ProcessError)), &GetEventDispatcher(), SLOT(ProgramError(QProcess::ProcessError)));
    QObject::connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), &GetEventDispatcher(), SLOT(ProgramFinished(int,QProcess::ExitStatus)));
    QObject::connect(process, SIGNAL(readyRead()), &GetEventDispatcher(), SLOT(ProgramOutputAvailable()));
}

Process::~Process() {
    Terminate();
    delete process;
}

void Process::Run() {
    QStringList qparams;
    for ( int i = 0; i < params.Size(); i++ ) {
        qparams << QString(params[i].ToCString());
    }
    process->start(command.ToCString(), qparams);
}

void Process::Terminate() {
    process->terminate();
    process->kill();
}

String Process::Output() const {
    return process->readAllStandardOutput().constData();
}

String Process::Error() const {
    return process->readAllStandardError().constData();
}
