#ifndef WIRED_SPEAKER_ADAPTER_H
#define WIRED_SPEAKER_ADAPTER_H

#include "audioOutputDevice.h"
#include "../external/wiredSpeakerApi.h"

class WiredSpeakerAdapter : public AudioOutputDevice {
private:
    WiredSpeakerAPI* api;
public:
    WiredSpeakerAdapter(WiredSpeakerAPI* api) : api(api) {}
    void playAudio(Song song) override {
        api->play();
        std::cout << "Streaming to wired speaker: " << song.title << std::endl;
    }
};

#endif // WIRED_SPEAKER_ADAPTER_H