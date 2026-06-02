// the command design pattern is a behavioral design pattern that turns a request into a stand-alone object containing all information about the request

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

// receiver
class Light{
public:
    void on(){
        cout << "Light is ON" << endl;
    }
    void off(){
        cout << "Light is OFF" << endl;
    }
};

// command interface
class Command{
public:    
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// concrete command
class LightOnCommand : public Command{
private:
    Light *light;
public:
    LightOnCommand(Light *l) : light(l) {}
    void execute() override {
        light->on();
    }
    
    void undo() override {
        light->off();
    }
};

class LightOffCommand : public Command{
private:
    Light *light;
public:    
    LightOffCommand(Light *l) : light(l) {}
    void execute() override {
        light->off();
    }
    void undo() override {
        light->on();
    }
};

// invoker
class RemoteControl{
private:
    vector<Command *> onCommands;
    vector<Command *> offCommands;
public:
    void setCommand(int slot, Command *onCommand, Command *offCommand){
        if(slot >= onCommands.size()){
            onCommands.resize(slot + 1, nullptr);
            offCommands.resize(slot + 1, nullptr);
        }
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void pressOn(int slot){
        if(onCommands[slot]){
            onCommands[slot]->execute();
        }
    }
    void pressOff(int slot){
        if(offCommands[slot]){
            offCommands[slot]->execute();
        }
    }
    void pressUndo(int slot){
        if(onCommands[slot]){   
            onCommands[slot]->undo();
        }
    }
};

int main(){
    Light livingRoomLight;
    Light kitchenLight;

    LightOnCommand livingRoomLightOn(&livingRoomLight);
    LightOffCommand livingRoomLightOff(&livingRoomLight);
    LightOnCommand kitchenLightOn(&kitchenLight);
    LightOffCommand kitchenLightOff(&kitchenLight);

    RemoteControl remote;
    remote.setCommand(0, &livingRoomLightOn, &livingRoomLightOff);
    remote.setCommand(1, &kitchenLightOn, &kitchenLightOff);

    remote.pressOn(0); // Living Room Light is ON
    remote.pressOff(0); // Living Room Light is OFF
    remote.pressUndo(0); // Living Room Light is ON

    remote.pressOn(1); // Kitchen Light is ON
    remote.pressOff(1); // Kitchen Light is OFF
    remote.pressUndo(1); // Kitchen Light is ON

    return 0;
}