#include "music.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_mixer.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_mixer.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_mixer.h"
#endif

void* Music::music = NULL;

bool Music::Load(const String& filename) {
    Free();
    music = Mix_LoadMUS(filename.ToCString());
    return music != 0;
}

void Music::Free() {
    if ( music ) {
        Stop();
        Mix_FreeMusic((Mix_Music*)music);
        music = 0;
    }
}

void Music::Play() {
    Mix_PlayMusic((Mix_Music*)music, 1);
}

void Music::Loop() {
    Mix_PlayMusic((Mix_Music*)music, -1);
}

void Music::Stop() {
    Mix_HaltMusic();
}

void Music::Pause() {
    Mix_PauseMusic();
}

void Music::Resume() {
    Mix_ResumeMusic();
}

void Music::SetVolume(float volume) {
    Mix_VolumeMusic((int)(volume*128));
}

bool Music::IsPlaying() {
     return Mix_PlayingMusic();
}
