#include "input.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL.h"
#endif

void Input::ShowMouse(bool show) {
    SDL_ShowCursor(show);
}

void Input::MoveMouse(int x, int y) {
    SDL_WarpMouseInWindow(0, x, y);
}

int Input::MouseX() {
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int Input::MouseY() {
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

bool Input::MouseButtonPressed(int button) {
    switch ( button ) {
    case MOUSE_LEFT:
    	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
    case MOUSE_RIGHT:
    	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
    case MOUSE_MIDDLE:
    	return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
    default:
    	return 0;
    }
}

bool Input::KeyPressed(int key) {
    return (bool)SDL_GetKeyboardState(NULL)[key];
}
