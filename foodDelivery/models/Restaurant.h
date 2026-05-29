#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"

using namespace std;

class Restaurant{
    private:
    inline static int nextRestaurantId = 1;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menuItems; // List of menu items offered by the restaurant

    public:
    Restaurant(const string &name, const string &location){
        this->name = name;
        this->location = location;
        this->restaurantId = nextRestaurantId++;
    }

    ~Restaurant() {
        cout << "Restaurant " << name << " destroyed" << endl;
        menuItems.clear();
    }

    string getName() const{
        return name;
    }

    void setName(const string &n){
        name = n;
    }

    string getLocation() const{
        return location;
    }

    void setLocation(const string &loc){
        location = loc;
    }

    void addMenuItem(const MenuItem &item){
        menuItems.push_back(item);
    }

    const vector<MenuItem>& getMenuItems() const{
        return menuItems;
    }
};

#endif // RESTAURANT_H