#ifndef HEADPHONE_ADAPTER_H
#define HEADPHONE_ADAPTER_H

#include "audioOutputDevice.h"
#include "../external/headPhoneApi.h"

class HeadPhoneAdapter : public AudioOutputDevice {
private:
    HeadPhoneAPI* api;
public:
    HeadPhoneAdapter(HeadPhoneAPI* api) : api(api) {}
    void playAudio(Song song) override {
        api->play();
        std::cout << "Streaming to headphones: " << song.title << std::endl;
    }
};

#endif // HEADPHONE_ADAPTER_H