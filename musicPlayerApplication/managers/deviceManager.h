#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "../factories/deviceFactory.h"
#include <map>

class DeviceManager {
private:
    std::map<DeviceType, AudioOutputDevice*> devices;
    AudioOutputDevice* currentDevice;

public:
    DeviceManager() : currentDevice(nullptr) {}

    void selectDevice(DeviceType type) {
        if (devices.find(type) == devices.end()) {
            devices[type] = DeviceFactory::createDevice(type);
        }
        currentDevice = devices[type];
    }

    AudioOutputDevice* getCurrentDevice() {
        return currentDevice;
    }

    ~DeviceManager() {
        for (auto const& [type, device] : devices) {
            delete device;
        }
    }
};

#endif // DEVICE_MANAGER_H