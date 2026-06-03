#ifndef WIRED_SPEAKER_API_H
#define WIRED_SPEAKER_API_H

#include <iostream>

using namespace std;

class WiredSpeakerAPI {
public:
    void connect() {
        cout << "Wired speaker connected." << endl;
    }
    void disconnect() {
        cout << "Wired speaker disconnected." << endl;
    }
    void play() {
        cout << "Playing music through wired speaker." << endl;
    }
    void stop() {
        cout << "Stopped music on wired speaker." << endl;
    }
};

#endif // WIRED_SPEAKER_API_H