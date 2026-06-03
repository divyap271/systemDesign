#ifndef BLUETOOTH_SPEAKER_API_H
#define BLUETOOTH_SPEAKER_API_H

#include <iostream>

class BluetoothSpeakerAPI {
public:
    bool connectToSpeaker(const std::string& speakerName) {
        // Simulate connecting to a Bluetooth speaker
        std::cout << "Connecting to Bluetooth speaker: " << speakerName << std::endl;
        return true; // Assume connection is always successful for this simulation
    }
    void disconnectSpeaker() {
        // Simulate disconnecting from the Bluetooth speaker
        std::cout << "Disconnecting from Bluetooth speaker" << std::endl;
    }
    void playAudio(const std::string& audioData) {
        // Simulate playing audio through the Bluetooth speaker
        std::cout << "Playing audio through Bluetooth speaker: " << audioData << std::endl;
    }
};

#endif // BLUETOOTH_SPEAKER_API_H