#ifndef CORE_MEMBUFFER_H
#define CORE_MEMBUFFER_H

#include "../common/refcounter.h"
#include "string.h"

class MemBuffer : public RefCounter {
public:
    MemBuffer(unsigned int size) : size(size), fixed(false) { buffer = malloc(size); }
    MemBuffer(void* buffer, unsigned int size) : buffer(buffer), size(size), fixed(true) {}
    ~MemBuffer() { if ( !fixed ) free(buffer); }

    unsigned int Size() const { return size; }
    void Resize(unsigned int size) { if ( !fixed ) { this->size = size; buffer = realloc(buffer, size); } }

    signed char PeekInt8(unsigned int offset) const { signed char v; memcpy(&v, (char*)buffer+offset, sizeof(char)); return v; }
    signed short PeekInt16(unsigned int offset) const { signed short v; memcpy(&v, (char*)buffer+offset, sizeof(short)); return v; }
    signed int PeekInt(unsigned int offset) const { signed int v; memcpy(&v, (char*)buffer+offset, sizeof(int)); return v; }
    signed long PeekInt64(unsigned int offset) const { signed long v; memcpy(&v, (char*)buffer+offset, sizeof(long)); return v; }
    unsigned char PeekUInt8(unsigned int offset) const { unsigned char v; memcpy(&v, (char*)buffer+offset, sizeof(char)); return v; }
    unsigned short PeekUInt16(unsigned int offset) const { unsigned short v; memcpy(&v, (char*)buffer+offset, sizeof(short)); return v; }
    unsigned int PeekUInt(unsigned int offset) const { unsigned char v; memcpy(&v, (char*)buffer+offset, sizeof(int)); return v; }
    unsigned long PeekUInt64(unsigned int offset) const { unsigned long v; memcpy(&v, (char*)buffer+offset, sizeof(long)); return v; }
    float PeekFloat(unsigned int offset) const { float v; memcpy(&v, (char*)buffer+offset, sizeof(float)); return v; }
    double PeekDouble(unsigned int offset) const { double v; memcpy(&v, (char*)buffer+offset, sizeof(double)); return v; }
    String PeekCString(unsigned int offset, int size = 0) const;

    void PokeInt8(unsigned int offset, signed char val) { memcpy((char*)buffer+offset, &val, sizeof(char)); }
    void PokeInt16(unsigned int offset, signed short val) { memcpy((char*)buffer+offset, &val, sizeof(short)); }
    void PokeInt(unsigned int offset, signed int val) { memcpy((char*)buffer+offset, &val, sizeof(int)); }
    void PokeInt64(unsigned int offset, signed long val) { memcpy((char*)buffer+offset, &val, sizeof(long)); }
    void PokeUInt8(unsigned int offset, unsigned char val) { memcpy((char*)buffer+offset, &val, sizeof(char)); }
    void PokeUInt16(unsigned int offset, unsigned short val) { memcpy((char*)buffer+offset, &val, sizeof(short)); }
    void PokeUInt(unsigned int offset, unsigned int val) { memcpy((char*)buffer+offset, &val, sizeof(int)); }
    void PokeUInt64(unsigned int offset, unsigned long val) { memcpy((char*)buffer+offset, &val, sizeof(long)); }
    void PokeFloat(unsigned int offset, float val) { memcpy((char*)buffer+offset, &val, sizeof(float)); }
    void PokeDouble(unsigned int offset, double val) { memcpy((char*)buffer+offset, &val, sizeof(double)); }
    void PokeCString(unsigned int offset, const String& val) { { memcpy((char*)buffer+offset, val.ToCString(), sizeof(char)*(val.Length()+1)); } }

    void* Buffer() { return buffer; }
private:
    void* buffer;
    unsigned int size;
    bool fixed;
};

inline String MemBuffer::PeekCString(unsigned int offset, int size) const {
    String str;
    if ( size > 0 ) {
        char* buf = (char*)malloc(sizeof(char)*(size + 1));
        memcpy(buf, (char*)buffer+offset, sizeof(char)*size);
        buf[size] = 0;
        str = buf;
        free(buf);
    } else {
        char c = PeekUInt8(offset);
        while ( c != 0 ) {
            str += c;
            c = PeekUInt8(offset++);
        }
    }
    return str;
}

#endif // CORE_MEMBUFFER_H
