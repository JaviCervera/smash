#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include "../common/refcounter.h"
#include "../core/string.h"
#include "pixmap.h"

class Image : public RefCounter {
public:
    Image(const Pixmap* pixmap, int hframes, int vframes);
    Image(const String& filename, int hframes, int vframes);
    ~Image();

    bool IsLoaded() const { return gltex != 0; }
    void Draw(double x, double y, int frame, double width = 0.0, double height = 0.0, double angle = 0.0, double rectx = 0.0, double recty = 0.0, double rectwidth = 0.0, double rectheight = 0.0);
    void DrawTiled(double offsetx, double offsety, double x, double y, double width, double height);
    int Frames() const { return hframes * vframes; }
    int HFrames() const { return hframes; }
    int VFrames() const { return vframes; }
    int Width() const { return width / hframes; }
    int Height() const { return height / vframes; }
    void SetHandle(int x, int y) { handlex = x; handley = y; }
    int HandleX() const { return handlex; }
    int HandleY() const { return handley; }
protected:
    void _Init(const Pixmap* pixmap, int hframes, int vframes);
    unsigned int _GLTexture() const { return gltex; }
private:
    int hframes, vframes;
    unsigned int width, height;
    int handlex, handley;
    double lastu, lastv;
    unsigned int gltex;
};

#endif // GAME_IMAGE_H
