#ifndef BLUETOOTH_SPEAKER_ADAPTER_H
#define BLUETOOTH_SPEAKER_ADAPTER_H

#include "audioOutputDevice.h"
#include "../external/bluetoothSpeakerApi.h"

class BluetoothSpeakerAdapter : public AudioOutputDevice {
private:
    BluetoothSpeakerAPI* api;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* api) : api(api) {}
    void playAudio(Song song) override {
        api->playAudio(song.title + " by " + song.artist);
    }
};

#endif // BLUETOOTH_SPEAKER_ADAPTER_H