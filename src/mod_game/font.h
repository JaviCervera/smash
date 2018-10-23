#ifndef GAME_FONT_H
#define GAME_FONT_H

#include "../mod_core/array.h"
#include "glyph.h"
#include "image.h"

class Font : public Image {
public:
    //Font(const Pixmap* pixmap);
    //Font(const String& filename);
    Font(const String& fontname, float pixelheight, unsigned int mapsize = 512);

    int Size() const { return Height(); }
    int TextWidth(const String& text) const;
    int TextHeight(const String& text) const;

    void Draw(const String& text, double x, double y);
protected:
    //void _Init(const Pixmap* pixmap);
    //int _PixelColor(const unsigned char* buffer, int width, int x, int y) const;
    //void _SetPixelColor(unsigned char* buffer, int width, int x, int y, int color);
private:
    float height;
    Array<Glyph> glyphs;
};

#endif // GAME_FONT_H
