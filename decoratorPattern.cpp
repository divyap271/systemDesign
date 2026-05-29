// The decorator Design pattern is a structural design pattern that allows you to dynamically add new behavious or responsibility to an object at runtime without altering its structure or modifying the original class.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// base inetrface
class Beverage{
    public:
    virtual ~Beverage() = default;
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

// concrete component
class Espresso: public Beverage{
    public:
    string getDescription() const override{
        return "Espresso";
    }
    double cost() const override{
        return 1.99;
    }
};

// decorator base class
class CondimentDecorator: public Beverage{
    protected:
    unique_ptr<Beverage> beverage;

    public:
    CondimentDecorator(unique_ptr<Beverage> bev) : beverage(move(bev)) {}
};

// concrete decorator
class Milk: public CondimentDecorator{
    public:
    Milk(unique_ptr<Beverage> bev) : CondimentDecorator(move(bev)) {}

    string getDescription() const override{
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override{
        return beverage->cost() + 0.5;
    }
};

class Sugar: public CondimentDecorator{
    public:
    Sugar(unique_ptr<Beverage> bev) : CondimentDecorator(move(bev)) {}

    string getDescription() const override{
        return beverage->getDescription() + ", Sugar";
    }

    double cost() const override{
        return beverage->cost() + 0.2;
    }
};

int main(){
    unique_ptr<Beverage> beverage = make_unique<Espresso>();
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;

    beverage = make_unique<Milk>(move(beverage));
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;

    beverage = make_unique<Sugar>(move(beverage));
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;

    return 0;
}