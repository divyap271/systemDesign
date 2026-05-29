#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "MenuItem.h"

using namespace std;

class Restaurant;

class Cart{
    private:
    Restaurant* restaurant;
    vector<MenuItem> items;

    public:
    Cart(){
        restaurant = nullptr;
    }

    void addItem(const MenuItem &item){
        if(!restaurant){
            cerr<<"No restaurant selected for the cart!"<<endl;
            return;
        }
        items.push_back(item);
    }

    double getTotalPrice() const{
        double total = 0;
        for(const auto &item : items){
            total += item.getPrice();
        }
        return total;
    }

    bool isEmpty() const{
        return items.empty();
    }

    void clear(){
        items.clear();
        restaurant = nullptr;
    }

    void setRestaurant(Restaurant* r){
        restaurant = r;
    }

    Restaurant* getRestaurant() const{
        return restaurant;
    }

    vector<MenuItem> getItems() const{
        return items;
    }
};

#endif // CART_H