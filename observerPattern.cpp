// The observer pattern is a behavorial design pattern that defines a one to many dependency between objacts. When one object changes its state all of its dependents are notified and updated automatically.
// Generic Observer

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// observer interface
class IObserver{
    public:
    virtual ~IObserver() = default;
    virtual void update(float temperature) = 0;
};

// subject interface
class ISubject{
    public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify() = 0;
};

// concrete subject
class WeatherStation : public ISubject{
    vector<IObserver *> observers;
    float temperature;

    public:
    void attach(IObserver *observer) override {
        observers.push_back(observer);
    }

    void detach(IObserver *observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for(auto observer : observers){
            observer->update(temperature);
        }
    }

    void setTemperature(float temp){
        temperature = temp;
        notify();
    }
};

// concrete observer

class PhoneDisplay: public IObserver{
    public:
    void update(float temperature) override {
        cout << "Phone Display: Current temperature is " << temperature << " degrees." << endl;
    }
};

class WindowDisplay: public IObserver{
    public:
    void update(float temperature) override {
        cout << "Window Display: Current temperature is " << temperature << " degrees." << endl;
    }
};

int main(){
    WeatherStation station;
    PhoneDisplay phoneDisplay;
    WindowDisplay windowDisplay;

    station.attach(&phoneDisplay);
    station.attach(&windowDisplay);

    station.setTemperature(25.5);
    station.setTemperature(30.0);

    return 0;
}