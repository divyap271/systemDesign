#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "../strategies/playStrategy.h"
#include "../device/audioOutputDevice.h"

#include <iostream>

using namespace std;

class AudioEngine {
private:
    PlayStrategy* strategy;
    AudioOutputDevice* device;

public:
    AudioEngine() : strategy(nullptr), device(nullptr) {}

    void setStrategy(PlayStrategy* strategy) {
        this->strategy = strategy;
    }

    void setDevice(AudioOutputDevice* device) {
        this->device = device;
    }

    void play() {
        if (strategy && device) {
            Song song = strategy->getCurrentSong();
            if (!song.title.empty()) {
                device->playAudio(song);
            } else {
                std::cout << "No song to play." << std::endl;
            }
        } else {
            std::cout << "Strategy or Device not set." << std::endl;
        }
    }

    void next() {
        if (strategy) {
            strategy->next();
            play();
        }
    }

    void previous() {
        if (strategy) {
            strategy->previous();
            play();
        }
    }
};

#endif // AUDIO_ENGINE_H