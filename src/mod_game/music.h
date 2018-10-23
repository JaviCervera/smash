#ifndef GAME_MUSIC_H
#define GAME_MUSIC_H

#include "../core/string.h"

class Music {
public:
    static bool Load(const String& filename);
    static void Free();
    static void Play();
    static void Loop();
    static void Stop();
    static void Pause();
    static void Resume();
    static void SetVolume(float volume);
    static bool IsPlaying();
protected:
    Music() {}
    ~Music() {}
private:
    static void* music;
};

#endif // GAME_MUSIC_H
