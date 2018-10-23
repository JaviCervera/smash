#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#define BLEND_SOLID      0
#define BLEND_ALPHA      1
#define BLEND_ADD        2
#define BLEND_MODULATE   3

class Renderer {
public:
    static void SetOrigin(double x, double y);
    static void SetViewport(int x, int y, int width, int height);
    static void SetBlendMode(int blend);
    static void SetColor(int color);
    static int Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    static unsigned char Red(int color);
    static unsigned char Green(int color);
    static unsigned char Blue(int color);
    static unsigned char Alpha(int color);
    static void DrawPoint(double x, double y);
    static void DrawLine(double x1, double y1, double x2, double y2);
    static void DrawRect(double x, double y, double width, double height);
    static void DrawEllipse(double x, double y, double xrad, double yrad);
protected:
    Renderer() {}
    ~Renderer() {}
private:
};

#endif // GAME_RENDERER_H
