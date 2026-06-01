// It is a creational design pattern that lets you cotruct complex objects step by step. The pattern allows you to produce different types and representations of an object using the same construction code by extracting the object contruction logic out of its own class and moving it to seprate objects called builders.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// product class
class Computer{
public:
    string cpu;
    string gpu;
    string ram;
    string storage;
    bool hsWifi = false;

    void displaySpecs() const{
        cout<<"Computer Specifications:"<<endl;
        cout<<"CPU: "<<cpu<<endl;
        cout<<"GPU: "<<gpu<<endl;
        cout<<"RAM: "<<ram<<endl;
        cout<<"Storage: "<<storage<<endl;
        cout<<"Has WiFi: "<<(hsWifi ? "Yes" : "No")<<endl;
    }
};

// builder interface
class ComputerBuilder{
private:
    unique_ptr<Computer> computer;
public:
    ComputerBuilder(){
        reset();
    }

    void reset(){
        computer = make_unique<Computer>();
    }

    ComputerBuilder& setCpu(const string &cpu){
        computer->cpu = cpu;
        return *this;
    }

    ComputerBuilder& setGpu(const string &gpu){
        computer->gpu = gpu;
        return *this;
    }

    ComputerBuilder& setRam(const string &ram){
        computer->ram = ram;
        return *this;
    }

    ComputerBuilder& setStorage(const string &storage){
        computer->storage = storage;
        return *this;
    }

    ComputerBuilder& setHasWifi(bool hasWifi){
        computer->hsWifi = hasWifi;
        return *this;
    }

    unique_ptr<Computer> build(){
        unique_ptr<Computer> result = std::move(computer);
        reset();
        return result;
    }
};

int main(){
    ComputerBuilder builder;
    unique_ptr<Computer> myComputer = builder.setCpu("Intel i9")
                                .setGpu("NVIDIA RTX 3080")
                                .setRam("32GB")
                                .setStorage("1TB SSD")
                                .setHasWifi(true)
                                .build();
    myComputer->displaySpecs();
}