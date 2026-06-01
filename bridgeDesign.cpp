// It is a structural design pattern that splits a massive class into two separate hierarchies: Abstraction (the control layer) and Implementation (the actual working layer). there two hierarchies can then be developed and sawpped out independently of each other.

#include <iostream>
#include <string>
#include <memory>

//Implementation interface
class Device{
public:
    virtual ~Device() = default;
    virtual bool isEnabled() const = 0;
    virtual void disabled() =0;
    virtual void setVolume(int percent) = 0;
};

//Concrete implementation 1
class Tv: public Device{
private:
    bool on = false;
    int volume = 30;
public:
    bool isEnabled() const override{
        return on;
    }

    void disabled() override{
        on = false;
        std::cout<<"[Tv] TV is now OFF."<<std::endl;
    }

    void setVolume(int percent) override{
        volume = percent;
        std::cout<<"[Tv] TV volume set to "<<volume<<"%."<<std::endl;
    }
};

// concrete implementation 2
class Radio: public Device{
private:
    bool on = false;
    int volume = 50;
public:
    bool isEnabled() const override{
        return on;
    }

    void disabled() override{
        on = false;
        std::cout<<"[Radio] Radio is now OFF."<<std::endl;
    }

    void setVolume(int percent) override{
        volume = percent;
        std::cout<<"[Radio] Radio volume set to "<<volume<<"%."<<std::endl;
    }
};

// base abstraction
class RemoteControl{
protected:    
    std::shared_ptr<Device> device;
public:
    explicit RemoteControl(std::shared_ptr<Device> dev): device(std::move(dev)){}
    virtual ~RemoteControl() = default;

    virtual void togglePower(){
        if(device->isEnabled()){
            device->disabled();
        }
        else{
            std::cout<<"[Remote] Powering on the device..."<<std::endl;
            // Assuming we have a method to enable the device, which is not defined in the Device interface for simplicity
        }
    }

    virtual void volumeUp(){
        std::cout<<"[Remote] Increasing volume..."<<std::endl;
        // Assuming we have a method to get current volume and set new volume, which is not defined in the Device interface for simplicity
    }
};

// refined abstraction
class AdvancedRemoteControl: public RemoteControl{
public:    
    explicit AdvancedRemoteControl(std::shared_ptr<Device> dev): RemoteControl(std::move(dev)){}
    void mute(){
        std::cout<<"[Advanced Remote] Muting the device..."<<std::endl;
        device->setVolume(0);
    }
};

int main(){
    std::cout<<"---Testing TV with Remote Control---"<<std::endl;
    std::shared_ptr<Device> tv = std::make_shared<Tv>();
    RemoteControl remote(tv);
    remote.togglePower();
    remote.volumeUp();

    std::cout<<"\n---Testing Radio with Advanced Remote Control---"<<std::endl;
    std::shared_ptr<Device> radio = std::make_shared<Radio>();
    AdvancedRemoteControl advRemote(radio);
    advRemote.togglePower();
    advRemote.volumeUp();
    advRemote.mute();

    return 0;
}