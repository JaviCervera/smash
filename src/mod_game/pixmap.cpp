#include "pixmap.h"
#include "../core/file.h"
#include "../core/membuffer.h"
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"
#include "lib/stb_truetype.h"

// stb_image.c functions
extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

Pixmap::Pixmap(unsigned int width, unsigned int height, int color) {
    // Load
    buffer = (unsigned char*)malloc(sizeof(char) * width * height * 4);
    this->width = width;
    this->height = height;

    // Fill with color
    int* ibuffer = (int*)buffer;
    for ( unsigned int i = 0; i < width * height; i++ ) {
        ibuffer[i] = color;
    }

    // Assign membuffer
    membuffer = new MemBuffer(buffer, width * height * 4);
}

Pixmap::Pixmap(const String& filename) {
    // Load buffer
    int w, h, c;
    buffer = stbi_load(filename.ToCString(), &w, &h, &c, 4);
    width = (unsigned int)w;
    height = (unsigned int)h;

    // Assign membuffer
    membuffer = new MemBuffer(buffer, width * height * 4);
}

Pixmap::Pixmap(const String& fontname, float fontheight) {
    // Try to open file
    buffer = NULL;
    membuffer = NULL;
    File file(fontname, FILE_READ);
    if ( !file.IsOpened() ) return;

    // Read file into memory
    MemBuffer buf(file.Size());
    file.ReadBytes(buf.Buffer(), file.Size());
    file.Close();

    // Bake font into temp alpha buffer
    width = 512;
    height = 512;
    stbtt_bakedchar charData[256];
    unsigned char* alphaBuffer = (unsigned char*)malloc(width * height);
    stbtt_BakeFontBitmap((const unsigned char*)buf.Buffer(), 0, fontheight, alphaBuffer, width, height, 0, 256, charData);

    // Copy alpha buffer into color buffer
    buffer = (unsigned char*)malloc(width * height * 4);
    for ( unsigned int i = 0; i < width*height; i++ ) {
        buffer[i*4 + 0] = alphaBuffer[i];
        buffer[i*4 + 1] = alphaBuffer[i];
        buffer[i*4 + 2] = alphaBuffer[i];
        buffer[i*4 + 3] = alphaBuffer[i];
    }
    free(alphaBuffer);

    // Assign membuffer
    membuffer = new MemBuffer(buffer, width * height * 4);
}

Pixmap::Pixmap(const Pixmap& other) {
    buffer = (unsigned char*)malloc(sizeof(char) * other.Width() * other.Height() * 4);
    memcpy(buffer, other.ConstBuffer(), sizeof(char) * other.Width() * other.Height() * 4);
    width = other.Width();
    height = other.Height();

    // Assign membuffer
    membuffer = new MemBuffer(buffer, width * height * 4);
}

Pixmap& Pixmap::operator=(const Pixmap& other) {
    if ( buffer ) free(buffer);
    if ( membuffer ) delete membuffer;
    buffer = (unsigned char*)malloc(sizeof(char) * other.Width() * other.Height() * 4);
    memcpy(buffer, other.ConstBuffer(), sizeof(char) * other.Width() * other.Height() * 4);
    width = other.Width();
    height = other.Height();
    membuffer = new MemBuffer(buffer, width * height * 4);
    return *this;
}

Pixmap::~Pixmap() {
    if ( buffer ) free(buffer);
    if ( membuffer ) delete membuffer;
}

bool Pixmap::Write(const String& filename) const {
    if ( filename.ExtractExt().Lower() == "png" ) return stbi_write_png(filename.ToCString(), Width(), Height(), 4, ConstBuffer(), 0) != 0;
    else if ( filename.ExtractExt().Lower() == "bmp" ) return stbi_write_bmp(filename.ToCString(), Width(), Height(), 4, ConstBuffer()) != 0;
    else if ( filename.ExtractExt().Lower() == "tga" ) return stbi_write_tga(filename.ToCString(), Width(), Height(), 4, ConstBuffer()) != 0;
    else return false;
}
