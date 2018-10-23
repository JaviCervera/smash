#ifndef GAME_CHANNEL_H
#define GAME_CHANNEL_H

#include "../core/array.h"

class Channel {
public:
    void Stop();
    void Pause();
    void Resume();
    void SetVolume(float volume);
    bool IsPlaying() const;

    // Not to be exported
    static Channel* Create(unsigned int channel);
protected:
    Channel(unsigned int channel) : channel(channel) {}
    ~Channel() {}
private:
    unsigned int channel;

    static Array<Channel*> channels;
};

#endif // GAME_CHANNEL_H
