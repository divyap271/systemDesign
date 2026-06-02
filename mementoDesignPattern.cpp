// a behavioral design pattern that allows you to capture and externalize an object's internal state without violating encapsulation, so that the object can be restored to this state later.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Memento class
class Memento{
private:
    string state;
public:
    Memento(const string &s) : state(s) {}
    string getState() const { return state; }
};

// Originator class
class Originator{
private:
    string state;
public:
    Originator(const string &s) : state(s) {}
    void setState(const string &s) { state = s; }
    string getState() const { return state; }
    unique_ptr<Memento> createMemento() {
        return make_unique<Memento>(state);
    }
    void restoreMemento(Memento *memento) {
        state = memento->getState();
    }
};

// Caretaker class
class Caretaker{
private:
    vector<unique_ptr<Memento>> mementos;
public:
    void addMemento(unique_ptr<Memento> memento) {
        mementos.push_back(move(memento));
    }
    unique_ptr<Memento> getMemento(size_t index) {
        return move(mementos[index]);
    }
};

int main(){
    Originator originator("Initial State");
    Caretaker caretaker;

    cout << "Originator State: " << originator.getState() << endl;

    // Create and store a memento
    caretaker.addMemento(originator.createMemento());

    // Change the originator's state
    originator.setState("Modified State");
    cout << "Originator State: " << originator.getState() << endl;

    // Restore the originator's state from the memento
    originator.restoreMemento(caretaker.getMemento(0).get());
    cout << "Originator State: " << originator.getState() << endl;

    return 0;
}