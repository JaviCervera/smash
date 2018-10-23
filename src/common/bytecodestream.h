#ifndef BYTECODESTREAM_H
#define BYTECODESTREAM_H

#include "../sdk/angelscript.h"
#include "../mod_core/file.h"

class BytecodeStream : public asIBinaryStream {
public:
    enum StreamType {
        STREAM_IN,
        STREAM_OUT
    };

	BytecodeStream(const String& filename, StreamType type) : f(filename, (type == STREAM_IN) ? FILE_READ : FILE_WRITE) {}

    virtual void Write(const void* ptr, asUINT size) { if ( size == 0 ) return; f.WriteBytes(ptr, size); }
    virtual void Read(void* ptr, asUINT size) { if ( size == 0 ) return; f.ReadBytes(ptr, size); }

    File& GetFile() { return f; }
    const File& GetFile() const { return f; }
private:
  File f;
};

#endif // BYTECODESTREAM_H
