#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include "../common/refcounter.h"
#include "../mod_core/string.h"

class Channel;

class Sound : public RefCounter {
public:
    Sound(const String& filename);
    ~Sound();

    bool IsLoaded() const { return buffer != NULL; }
    Channel* Play();
    Channel* Loop();
private:
    void* buffer;
};

#endif // GAME_SOUND_H
