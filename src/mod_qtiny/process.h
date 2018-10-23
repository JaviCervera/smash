#ifndef PROCESS_H
#define PROCESS_H

#include "../common/refcounter.h"
#include "../mod_core/array.h"
#include "../mod_core/string.h"

class QProcess;

class Process : public RefCounter {
public:
    Process(const String& name);
    virtual ~Process();

    void Run();
    void Terminate();

    String Output() const;
    String Error() const;
private:
    QProcess* process;
    String command;
    Array<String> params;
};

#endif // PROCESS_H
