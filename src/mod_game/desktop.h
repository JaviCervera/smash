#ifndef GAME_DESKTOP_H
#define GAME_DESKTOP_H

class Desktop {
public:
    static int Width() { return width; }
    static int Height() { return height; }

    // Not to be exported
    static void SetWidth(int width) { Desktop::width = width; }
    static void SetHeight(int height) { Desktop::height = height; }
protected:
    Desktop() {}
    ~Desktop() {}
private:
    static int width;
    static int height;
};

#endif // GAME_DESKTOP_H
