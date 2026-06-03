#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "../enum/deviceType.h"
#include "../device/audioOutputDevice.h"
#include "../device/bluetoothSpeakerAdapter.h"
#include "../device/wiredSpeakerAdapter.h"
#include "../device/headphoneAdapter.h"
#include "../external/bluetoothSpeakerApi.h"
#include "../external/wiredSpeakerApi.h"
#include "../external/headPhoneApi.h"

class DeviceFactory {
public:
    static AudioOutputDevice* createDevice(DeviceType type) {
        switch (type) {
            case BLUETOOTH:
                return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
            case WIRED:
                return new WiredSpeakerAdapter(new WiredSpeakerAPI());
            case HEADPHONES:
                return new HeadPhoneAdapter(new HeadPhoneAPI());
            default:
                return nullptr;
        }
    }
};

#endif // DEVICE_FACTORY_H