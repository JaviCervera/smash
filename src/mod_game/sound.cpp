#include "sound.h"
#include "channel.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_mixer.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_mixer.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_mixer.h"
#endif

Sound::Sound(const String& filename) {
    buffer = (void*)Mix_LoadWAV(filename.ToCString());
}

Sound::~Sound() {
    if ( buffer ) Mix_FreeChunk((Mix_Chunk*)buffer);
}

Channel* Sound::Play() {
    return Channel::Create(Mix_PlayChannel(-1, (Mix_Chunk*)buffer, 0));
}

Channel* Sound::Loop() {
    return Channel::Create(Mix_PlayChannel(-1, (Mix_Chunk*)buffer, -1));
}
