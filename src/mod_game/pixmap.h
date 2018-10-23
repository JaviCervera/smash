#ifndef GAME_PIXMAP_H
#define GAME_PIXMAP_H

#include "../common/refcounter.h"
#include "../core/membuffer.h"
#include "../core/string.h"

class Pixmap : public RefCounter {
public:
    Pixmap(unsigned int width, unsigned int height, int color);
    Pixmap(const String& filename);
    Pixmap(const Pixmap& other);
    Pixmap(const String& fontname, float fontheight);
    ~Pixmap();

    Pixmap& operator=(const Pixmap& other);

    bool IsLoaded() const { return buffer != NULL; }
    MemBuffer* Buffer() { return membuffer; }
    const unsigned char* ConstBuffer() const { return buffer; }
    unsigned int Width() const { return width; }
    unsigned int Height() const { return height; }
    bool Write(const String& filename) const;
private:
    MemBuffer* membuffer;
    unsigned char* buffer;
    unsigned int width;
    unsigned int height;
};

#endif // GAME_PIXMAP_H
