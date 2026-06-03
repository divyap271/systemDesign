#ifndef AUDIO_OUTPUT_DEVICE_H
#define AUDIO_OUTPUT_DEVICE_H

#include "../models/song.h"

class AudioOutputDevice {
public:
    virtual ~AudioOutputDevice() {}
    virtual void playAudio(Song song) = 0; 
};

#endif // AUDIO_OUTPUT_DEVICE_H