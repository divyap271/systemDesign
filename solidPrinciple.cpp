// S -> A class should have one and only one reason to chang. it should only have one job or responsibility:
// O -> sftware entities should be open for extension, but closed for modification.
// L-> objects of superclass should be replacable with objects of its subclass without breaking the application.
// I-> No client should be forced to depend on methods it does not use. Large intefaces should be split into smaller more specific ones.
// D-> High level modlues should not depend on low level modules. Both should depend on abstrations. abstractions should not depend on details; details should depend on abstraction.

#include <iostream>
#include <string>

using namespace std;

// Single responsibiltiy principle
// bad design:
class Report{
    string content;
    void generateReport(){
        content = "Report Data";
    }

    // violation: handling persistence
    void printReport(){
        cout << content << endl;
    }
};

// good design:
class Report{
    public:
    string content;
    void generateReport(){
        content = "Report Data";
    }
};

class reportSaver{
    public:
    void saveToFile(const Report &report, const string &fileName){
        cout<<report.content<<" saved to "<<fileName<<endl;
    }
};

// Open/closed principle
// bad design:
class Discountcalculator{
    public:
    double calculate(double amout, const string &customerType){
        // We have to modify the discountcalculator every time we add a new coustomer type
        if(customerType == "Regular"){
            return amout * 0.1;
        } else if(customerType == "VIP"){
            return amout * 0.2;
        }
        return 0;
    }
};

// good design
// We use an abstract base class.
class DiscountStrategy{
    public:
    virtual double calculate(double amount) = 0; // pure virtual function
};

class RegularCustomerDiscount : public DiscountStrategy{
    public:
    double calculate(double amount) override {
        return amount * 0.1;
    }
};

class preminumDiscount : public DiscountStrategy{
    public:
    double calculate(double amount) override {
        return amount * 0.2;
    }
};

// Liskov substitution principle
// bad design:
class RectangleBad{
    protected:
    double width;
    double height;
    public:
    void setWidth(double w){
        width = w;
    }
    void setHeight(double h){
        height = h;
    }
    double area(){
        return width * height;
    }
};

class SquareBad : public RectangleBad{
    public:
    void setWidth(double w) {
        width = w;
        height = w; // maintain the invariant of a square
    }
    void setHeight(double h) {
        height = h;
        width = h; // maintain the invariant of a square
    }
};

// good design:
class Shape{
    public:
    virtual double area() = 0; // pure virtual function
    virtual ~Shape() = default; // virtual destructor
};

class Rectangle : public Shape{
    private:
    double width;
    double height;
    public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() override {
        return width * height;
    }
};

class Square : public Shape{
    private:
    double side;
    public:
    Square(double s) : side(s) {}
    double area() override {
        return side * side;
    }
};

// Interface segregation Principle
// bad design:
class Worker{
    public:
    virtual void work() = 0;
    virtual void eat() = 0;
};

class Robot : public Worker{
    public:
    void work() override {
        cout << "Robot is working" << endl;
    }
    void eat() {
        // Robots don't eat, but we are forced to implement this method
        cout << "Robot can't eat" << endl;
    }
};

// good design:
class Worker{
    public:
    virtual void work() = 0;
};

class Eater{
    public:
    virtual void eat() = 0;
};

class Human : public Worker, public Eater{
    public:
    void work() override {
        cout << "Human is working" << endl;
    }
    void eat() override {
        cout << "Human is eating" << endl;
    }
};

class Robot : public Worker{
    public:
    void work() override {
        cout << "Robot is working" << endl;
    }
    // No need to implement eat() method for Robot class, as it doesn't eat.
};

// Dependency inversion principle
// bad design:
class lightbuld{
    public:
    void turnOn(){
        cout << "Lightbulb is on" << endl;
    }
    void turnOff(){
        cout << "Lightbulb is off" << endl;
    }
};

class Button{
    // button dirctly depends on lightbulb, which is a low level module. if we want to change the lightbulb implementation, we have to modify the button class.
    private:
    lightbuld bulb;
    public:
    void press(){
        bulb.turnOn();
    }
};

// good design:
class Switchable{
    public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class Lightbulb : public Switchable{
    public:
    void turnOn() override {
        cout << "Lightbulb is on" << endl;
    }
    void turnOff() override {
        cout << "Lightbulb is off" << endl;
    }
};

class Button{
    // button depends on the abstraction (Switchable) rather than the concrete implementation (Lightbulb). we can easily switch to a different implementation of Switchable without modifying the Button class.
    private:
    Switchable &device;
    public:
    Button(Switchable &dev) : device(dev) {}
    void press(){
        device.turnOn();
    }
};