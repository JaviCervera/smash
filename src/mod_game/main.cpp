#include "main.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL.h"
#include "lib/SDL2/win32/SDL_mixer.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL.h"
#include "lib/SDL2/mac/SDL_mixer.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL.h"
#include "lib/SDL2/linux/SDL_mixer.h"
#endif

String SDLError() {
    return SDL_GetError();
}

String MixerError() {
    return Mix_GetError();
}

void InitGame() {
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) == 0 ) {
        // Init SDL_mixer
        //MIX_INIT_FLAC | MIX_INIT_MODPLUG | MIX_INIT_MP3 | MIX_INIT_OGG
        Mix_Init(MIX_INIT_OGG);
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

        // Get desktop dimensions
        SDL_DisplayMode mode;
        SDL_GetDesktopDisplayMode(0, &mode);
        Desktop::SetWidth(mode.w);
        Desktop::SetHeight(mode.h);
    }
}

void FinishGame() {
    SDL_Quit();
    Mix_Quit();
}

void HandleEvents() {
    SDL_Event event;
    Screen* screen = NULL;
    while ( SDL_PollEvent(&event) ) {
        switch ( event.type ) {
        case SDL_WINDOWEVENT:
            screen = Screen::ScreenForSDLWindow(SDL_GetWindowFromID(event.window.windowID));
            if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
                screen->CloseEvent();
            }
            break;
        case SDL_QUIT:
            // Add something here...
            break;
        }
    }
}
