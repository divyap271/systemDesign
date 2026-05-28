#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"

using namespace std;

class Restaurant{
    private:
    static int nextRestaurantId; // static variable to generate unique restaurant IDs
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menuItems; // List of menu items offered by the restaurant

    public:
    Restaurant(const string &name, const string &Location){
        this-> name = name;
        this-> location = location;
        this-> restaurantId = nextRestaurantId++;
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

int Restaurant::nextRestaurantId = 0;

#endif // RESTAURANT_H