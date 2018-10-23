#include "font.h"
#include "renderer.h"
#include "../mod_core/file.h"
#include <math.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "lib/stb_truetype.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_opengl.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_opengl.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_opengl.h"
#endif

static unsigned short UTF8Rep(char c);

/*Font::Font(const Pixmap* pixmap) : Image(pixmap, 16, 16) {
    _Init(pixmap);
}

Font::Font(const String& filename) : Image(filename, 1, 1) {
    Pixmap pixmap(filename);
    _Init(&pixmap);
}*/

Font::Font(const String& fontname, float pixelheight, unsigned int mapsize) : Image(NULL, 1, 1) {
    // Set height
    height = pixelheight;

    // Try to open file
    File file(fontname, FILE_READ);
    if ( !file.IsOpened() ) return;

    // Read file into memory
    MemBuffer buf(file.Size());
    file.ReadBytes(buf.Buffer(), file.Size());
    file.Close();

    // Bake font into temp alpha buffer
    stbtt_bakedchar charData[256];
    unsigned char* alphaBuffer = (unsigned char*)malloc(mapsize * mapsize);
    stbtt_BakeFontBitmap((const unsigned char*)buf.Buffer(), 0, pixelheight, alphaBuffer, mapsize, mapsize, 0, 256, charData);

    // Copy alpha buffer into Pixmap
    Pixmap pixmap(mapsize, mapsize, 0);
    for ( unsigned int i = 0; i < mapsize*mapsize; i++ ) {
        ((unsigned char*)pixmap.Buffer()->Buffer())[i*4 + 0] = alphaBuffer[i];
        ((unsigned char*)pixmap.Buffer()->Buffer())[i*4 + 1] = alphaBuffer[i];
        ((unsigned char*)pixmap.Buffer()->Buffer())[i*4 + 2] = alphaBuffer[i];
        ((unsigned char*)pixmap.Buffer()->Buffer())[i*4 + 3] = alphaBuffer[i];
    }
    free(alphaBuffer);

    // Init image
    Image::_Init(&pixmap, 1, 1);

    // Create glyphs
    //String("").Write("font.txt", false);
    for ( unsigned int i = 0; i < 256; i++ ) {
        //(String::FromInt(charData[i].xoff) + ", " + String::FromInt(charData[i].yoff) + "\n").Write("font.txt", true);
        glyphs.Add(Glyph(charData[i].x0, charData[i].y0, charData[i].x1 - charData[i].x0, charData[i].y1 - charData[i].y0, charData[i].xoff, charData[i].yoff));
    }
}

int Font::TextWidth(const String& text) const {
    int width = 0;
    for ( int i = 0; i < text.Length(); i++ ) {
        if ( text[i] == ' ' ) width += height/3;
        else width += glyphs[UTF8Rep(text[i])].Width();
    }
    return width;
}

int Font::TextHeight(const String& text) const {
    int height = 0;
    for ( int i = 0; i < text.Length(); i++ ) {
        if ( glyphs[UTF8Rep(text[i])].Height() > height ) height = glyphs[UTF8Rep(text[i])].Height();
    }
    return height;
}

void Font::Draw(const String& text, double x, double y) {
    for ( int i = 0; i < text.Length(); i++ ) {
        Glyph& glyph = glyphs[UTF8Rep(text[i])];
        //Image::Draw(x + glyph.OffsetX(), y + glyph.OffsetY(), (unsigned char)text[i]);
        if ( text[i] == ' ' ) x += height/3;
        else if ( glyph.Width() != 0 && glyph.Height() != 0 ) Image::Draw(x + glyph.OffsetX(), y + abs(glyph.OffsetY()), 0, 0, 0, 0, glyph.X(), glyph.Y(), glyph.Width(), glyph.Height());
        x += glyph.Width();
    }
}

/*void Font::_Init(const Pixmap* other) {
    if ( other->IsLoaded() ) {
        Pixmap* pixmap = new Pixmap(*other);

        // Get glyph info
        for ( int i = 0; i < 256; i++ ) {
            // Find glyph within the frame
            double xoffset = 0;
            double yoffset = 0;
            double width = Width();
            double height = Height();
            int row = (int)floor(i*1.0 / HFrames());
            int column = i % HFrames();
            for ( int y = row*Height(); y < (row + 1)*Height(); y++ ) {
                for ( int x = column*Width(); x < (column + 1)*Width(); x++ ) {
                    int color = _PixelColor(pixmap->ConstBuffer(), pixmap->Width(), x, y);
                    if ( Renderer::Red(color) == 255  &&  Renderer::Green(color) == 255  &&  Renderer::Blue(color) == 0 ) {
                        xoffset = (x - column*Width())*-1.0;
                        yoffset = (y - row*Height())*-1.0;
                        _SetPixelColor((unsigned char*)pixmap->Buffer()->Buffer(), pixmap->Width(), x, y, Renderer::Color(255, 255, 0, 0));
                    } else if ( Renderer::Red(color) == 255  &&  Renderer::Green(color) == 0  &&  Renderer::Blue(color) == 0 ) {
                        width = (x - column*Width()) + xoffset;
                        height = (y - row*Height()) + yoffset;
                        _SetPixelColor((unsigned char*)pixmap->Buffer()->Buffer(), pixmap->Width(), x, y, Renderer::Color(255, 0, 0, 0));
                    } else if ( Renderer::Red(color) == 0  &&  Renderer::Green(color) == 0  &&  Renderer::Blue(color) == 0 ) {
                        _SetPixelColor((unsigned char*)pixmap->Buffer()->Buffer(), pixmap->Width(), x, y, Renderer::Color(0, 0, 0, 0));
                    }
                }
            }

            // Add glyph to list
            glyphs.Add(Glyph(xoffset, yoffset, width, height));
        }

        // Change texture (we have turned some pixels into transparent)
        glBindTexture(GL_TEXTURE_2D, _GLTexture());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap->Width(), pixmap->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixmap->ConstBuffer());
        glBindTexture(GL_TEXTURE_2D, 0);

        delete pixmap;
    }
}

int Font::_PixelColor(const unsigned char* buffer, int width, int x, int y) const {
    return Renderer::Color(buffer[(y*width + x)*4 + 0], buffer[(y*width + x)*4 + 1], buffer[(y*width + x)*4 + 2], buffer[(y*width + x)*4 + 3]);
}

void Font::_SetPixelColor(unsigned char* buffer, int width, int x, int y, int color) {
    buffer[(y*width + x)*4 + 0] = Renderer::Red(color);
    buffer[(y*width + x)*4 + 1] = Renderer::Green(color);
    buffer[(y*width + x)*4 + 2] = Renderer::Blue(color);
    buffer[(y*width + x)*4 + 3] = Renderer::Alpha(color);
}*/

static char* stb_to_utf8(char* buffer, wchar_t* str, int n) {
   int i=0;
   --n;
   while (*str) {
      if (*str < 0x80) {
         if (i+1 > n) return NULL;
         buffer[i++] = (char) *str++;
      } else if (*str < 0x800) {
         if (i+2 > n) return NULL;
         buffer[i++] = 0xc0 + (*str >> 6);
         buffer[i++] = 0x80 + (*str & 0x3f);
         str += 1;
      } else if (*str >= 0xd800 && *str < 0xdc00) {
         unsigned int c;
         if (i+4 > n) return NULL;
         c = ((str[0] - 0xd800) << 10) + ((str[1]) - 0xdc00) + 0x10000;
         buffer[i++] = 0xf0 + (c >> 18);
         buffer[i++] = 0x80 + ((c >> 12) & 0x3f);
         buffer[i++] = 0x80 + ((c >>  6) & 0x3f);
         buffer[i++] = 0x80 + ((c      ) & 0x3f);
         str += 2;
      } else if (*str >= 0xdc00 && *str < 0xe000) {
         return NULL;
      } else {
         if (i+3 > n) return NULL;
         buffer[i++] = 0xe0 + (*str >> 12);
         buffer[i++] = 0x80 + ((*str >> 6) & 0x3f);
         buffer[i++] = 0x80 + ((*str     ) & 0x3f);
         str += 1;
      }
   }
   buffer[i] = 0;
   return buffer;
}

static unsigned short UTF8Rep(char c) {
    // Generate wchar string
    char str[] = {c, 0};
    wchar_t wstr[] = {0, 0};
    mbstowcs(wstr, str, 1);

    // Convert to UTF8
    stb_to_utf8(str, wstr, 1);

    return (unsigned char)str[0];
}
