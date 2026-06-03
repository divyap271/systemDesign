#ifndef HEADPHONE_API_H
#define HEADPHONE_API_H

#include <iostream>

using namespace std;

class HeadPhoneAPI {
public:
    void connect() {
        cout << "Headphones connected." << endl;
    }
    void disconnect() {
        cout << "Headphones disconnected." << endl;
    }
    void play() {
        cout << "Playing music through headphones." << endl;
    }
    void stop() {
        cout << "Stopped music on headphones." << endl;
    }
};

#endif // HEADPHONE_API_H