#ifdef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "../models/MenuItem.h"
#include "../models/Order.h"

using namespace std;

class Cart{
    private:
    Restaurant* restaurant;
    vector<MenuItem> items;

    public:
    Cart(){
        restaurant = nullptr;
    }

    void addIteem(const MenuItem &item){
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
    }

    void setRestaurant(Restaurant* r){
        restaurant = r;
    }

    Restaurant* getRestaurant() const{
        return restaurant;
    }

    void vector<MenuItem> getItems() const{
        return items;
    }
}

#endif // CART_H