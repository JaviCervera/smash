#include "screen.h"
#include "main.h"
#include "../core/time.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL.h"
#include "lib/SDL2/win32/SDL_opengl.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL.h"
#include "lib/SDL2/mac/SDL_opengl.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL.h"
#include "lib/SDL2/linux/SDL_opengl.h"
#endif
#include <stdlib.h>

Array<Screen*> Screen::screens;

Screen::Screen(int width, int height, bool fullscreen) : currentFPS(0), fpsCounter(0), fpsAccumTime(0.0) {
    // Add to array of screens
    screens.Add(this);
    
    // Calculate flags
    Uint32 flags = SDL_WINDOW_OPENGL;
    if ( fullscreen ) flags |= SDL_WINDOW_FULLSCREEN;

    // Open screen
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    context = SDL_GL_CreateContext((SDL_Window*)window);
    this->width = width;
    this->height = height;

    // Init OpenGL
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    Renderer::SetBlendMode(BLEND_ALPHA);

    // Setup viewport
    Renderer::SetViewport(0, 0, width, height);

    // Setup projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1000);

    // Setup viewer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lastTime = Time::Millisecs() / 1000.0;
    deltaTime = 0.0;
}

Screen::~Screen() {
    // Remove from array of screens
    screens.Remove(this);

    // Destroy SDL stuff
    if ( context ) SDL_GL_DeleteContext((SDL_GLContext)context);
    if ( window ) SDL_DestroyWindow((SDL_Window*)window);
}

void Screen::Clear(int color) {
    glClearColor(Renderer::Red(color) / 255.0f, Renderer::Green(color) / 255.0f, Renderer::Blue(color) / 255.0f, Renderer::Alpha(color) / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::Refresh() {
    // Update timer
    deltaTime = (Time::Millisecs() / 1000.0) - lastTime;
    lastTime = (Time::Millisecs() / 1000.0);
    
    // Update FPS
    fpsCounter++;
    fpsAccumTime += deltaTime;
    if ( fpsAccumTime >= 1.0f ) {
    	currentFPS = fpsCounter;
    	fpsCounter = 0;
    	fpsAccumTime = 0;
    }
    
	// Poll events
    HandleEvents();
    
    // Refresh screen
    SDL_GL_SwapWindow((SDL_Window*)window);
}

void Screen::CloseEvent() {
    window = NULL;
    context = NULL;
}

Screen* Screen::ScreenForSDLWindow(void* window) {
    for ( int i = 0; i < screens.Size(); i++ ) {
        if ( screens[i]->window == (SDL_Window*)window ) {
            return screens[i];
        }
    }
    return NULL;
}
