#ifndef GAME_GLYPH_H
#define GAME_GLYPH_H

class Glyph {
public:
    Glyph() : x(0), y(0), width(0), height(0), offsetx(0), offsety(0) {}
    Glyph(double x, double y, double width, double height, double offsetx, double offsety) : x(x), y(y), width(width), height(height), offsetx(offsetx), offsety(offsety) {}

    double X() const { return x; }
    double Y() const { return y; }
    double Width() const { return width; }
    double Height() const { return height; }
    double OffsetX() const { return offsetx; }
    double OffsetY() const { return offsety; }
private:
    double x;
    double y;
    double width;
    double height;
    double offsetx;
    double offsety;
};

#endif // GAME_GLYPH_H
