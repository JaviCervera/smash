#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "../common/refcounter.h"
#include "../mod_core/array.h"

class Screen : public RefCounter {
public:
    Screen(int width, int height, bool fullscreen);
    virtual ~Screen();

    bool IsOpened() const { return window != 0; }

    void Clear(int color);
    void Refresh();

    int Width() const { return width; }
    int Height() const { return height; }
    int FPS() const { return currentFPS; }
    double DeltaTime() const { return deltaTime; }

    // Not to be exported
    void CloseEvent();
    static Screen* ScreenForSDLWindow(void* window);
private:
    void* window;
    void* context;
    int width, height;
    double lastTime, deltaTime;
    int currentFPS;
    int fpsCounter;
    double fpsAccumTime;

    static Array<Screen*> screens;
};

#endif // GAME_SCREEN_H
