// the adapter design pattern is a structural design pattern that allows objects with incompatible interface to collaborate by converting the interface of one class into another interface that clients expect.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// target interface
class TypeCPhone {
public:
    virtual ~TypeCPhone() = default;
    virtual void chargeWithTypeC() = 0;
};

// Adaptee
class OldMicroUsbPhone {
public:
    void chargeWithMicroUsb() {
        std::cout << "Charging via legacy Micro-USB port... 5V standard power.\n";
    }
};

// Adapter
class MicroUsbToTypeCAdapter : public TypeCPhone {
private:
    std::unique_ptr<OldMicroUsbPhone> legacyPhone; // Holding the incompatible object

public:
    explicit MicroUsbToTypeCAdapter(std::unique_ptr<OldMicroUsbPhone> phone) 
        : legacyPhone(move(phone)) {}

    void chargeWithTypeC() override {
        std::cout << "[Adapter] Translating Type-C fast charge request to Micro-USB pins...\n";
        // Convert the call to the old method
        legacyPhone->chargeWithMicroUsb();
    }
};

// Modern charging station that only accepts Type-C interfaces
void plugIntoChargingStation(TypeCPhone* phone) {
    std::cout << "Plugging phone into wall charger...\n";
    phone->chargeWithTypeC();
    std::cout << "Charging successful!\n\n";
}

int main() {
    // 1. We have a legacy phone
    auto legacyPhone = std::make_unique<OldMicroUsbPhone>();

    // This line would cause a compiler error because interfaces don't match:
    // plugIntoChargingStation(legacyPhone.get()); 

    // 2. Wrap the legacy phone inside our adapter
    auto adapter = std::make_unique<MicroUsbToTypeCAdapter>(std::move(legacyPhone));

    // 3. The modern charging station can now charge the old phone seamlessly
    plugIntoChargingStation(adapter.get());

    return 0;
}