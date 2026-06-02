// it is a creational design pattern that allows you to copy xisting object without maing your code dependent on their specific classes. It delegates the cloning process to the actual objects that are beign cloned via a common interfac.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// prototype interface
class Monster{
public:
    virtual ~Monster() = default;
    virtual unique_ptr<Monster> clone() const = 0;
    virtual void printState() const = 0;
};

// concrete prototypes
class Goblin : public Monster{
private:
    int health;
    int speed;
    string weapon;
public:
    Goblin(int h, int s, const string &w) : health(h), speed(s), weapon(w) {}
    unique_ptr<Monster> clone() const override {
        return make_unique<Goblin>(*this);
    }
    void printState() const override {
        cout << "Goblin - Health: " << health << ", Speed: " << speed << ", Weapon: " << weapon << endl;
    }

    void setWeapon(const string &w){
        weapon = w;
    }
};

class BossDragon : public Monster{
private:
    int health;
    string element;
public:
    BossDragon(int h, const string &e) : health(h), element(e) {}
    unique_ptr<Monster> clone() const override {
        return make_unique<BossDragon>(*this);
    }
    void printState() const override {
        cout << "BossDragon - Health: " << health << ", Element: " << element << endl;
    }
};

int main(){
    // create original monsters
    Goblin originalGoblin(100, 10, "Sword");
    BossDragon originalDragon(500, "Fire");

    cout << "Original Monsters:" << endl;
    originalGoblin.printState();
    originalDragon.printState();

    // clone the monsters
    auto clonedGoblin = originalGoblin.clone();
    auto clonedDragon = originalDragon.clone();

    cout << "\nCloned Monsters:" << endl;
    clonedGoblin->printState();
    clonedDragon->printState();

    // modify the cloned goblin's weapon
    static_cast<Goblin*>(clonedGoblin.get())->setWeapon("Axe");

    cout << "\nAfter modifying the cloned Goblin's weapon:" << endl;
    cout << "Original Goblin: ";
    originalGoblin.printState();
    cout << "Cloned Goblin: ";
    clonedGoblin->printState();

    return 0;
}