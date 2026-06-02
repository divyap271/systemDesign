// A behavorial design pattern that allows an object to completely alter its behavior when its internal state changes. It achieves this by extracting state specific behaviors into seprate independent state classes. It appears as through the object changed its entire class at runtime.

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class VendingMachine;

// state interface
class State{
    public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine *machine) = 0;
    virtual void dispenseItem(VendingMachine *machine) = 0;
};

// the context
class VendingMachine{
    private:
    unique_ptr<State> currentState;

    public:
    VendingMachine(unique_ptr<State> initialState) : currentState(move(initialState)) {}

    void setState(unique_ptr<State> newState){
        currentState = move(newState);
    }

    void insertCoin(){
        currentState->insertCoin(this);
    }

    void dispenseItem(){
        currentState->dispenseItem(this);
    }
};

// concrete states
class NoCoinState : public State{
    public:
    void insertCoin(VendingMachine *machine) override {
        cout << "Coin inserted. You can now select an item." << endl;
        machine->setState(make_unique<HasCoinState>());
    }
    void dispenseItem(VendingMachine *machine) override {
        cout << "Please insert a coin first." << endl;
    }
};

class HasCoinState : public State{
    public:
    void insertCoin(VendingMachine *machine) override {
        cout << "You already inserted a coin. Please select an item." << endl;
    }
    void dispenseItem(VendingMachine *machine) override {
        cout << "Dispensing item... Enjoy!" << endl;
        machine->setState(make_unique<NoCoinState>());
    }
};

int main(){
    VendingMachine machine(make_unique<NoCoinState>());

    machine.insertCoin(); // Coin inserted. You can now select an item.
    machine.dispenseItem(); // Dispensing item... Enjoy!
    machine.dispenseItem(); // Please insert a coin first.

    return 0;
}