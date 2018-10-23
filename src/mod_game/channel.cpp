#include "channel.h"
#if defined(_WIN32)
#include "lib/SDL2/win32/SDL_mixer.h"
#elif defined(__APPLE__)
#include "lib/SDL2/mac/SDL_mixer.h"
#elif defined(__linux__)
#include "lib/SDL2/linux/SDL_mixer.h"
#endif

Array<Channel*> Channel::channels;

Channel* Channel::Create(unsigned int channel) {
    // If channel exists, return existing instance
    for ( int i = 0; i < channels.Size(); i++ ) {
        if ( channels[i]->channel == channel ) {
            return channels[i];
        }
    }

    // Create it
    Channel* obj = new Channel(channel);
    channels.Add(obj);
    return obj;
}

void Channel::Stop() {
    Mix_HaltChannel(channel);
}

void Channel::Pause() {
    Mix_Pause(channel);
}

void Channel::Resume() {
    Mix_Resume(channel);
}

void Channel::SetVolume(float volume) {
    Mix_Volume(channel, (int)(volume*128));
}

bool Channel::IsPlaying() const {
    return Mix_Playing(channel);
}
