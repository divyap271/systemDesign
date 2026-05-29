#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/TimeUtils.h"

using namespace std;

class Order{
    protected:
    inline static int nextOrderId = 1;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStrategy;
    double total;
    string schedule;
    string status;

    public:
    Order(){
        user = nullptr;
        restaurant = nullptr;
        paymentStrategy = nullptr;
        total = 0.0;
        schedule = "";
        status = "Placed";
        orderId = nextOrderId++;
    }

    virtual ~Order() {
        delete paymentStrategy;
    }

    bool processPayment(){
        if(paymentStrategy){
            paymentStrategy->pay(total);
            return true;
        } else {
            cout<<"Please select a payment method!"<<endl;
            return false;
        }
    }

    virtual string getType() const = 0;

    int getOrderId() const{
        return orderId;
    }

    void setUser(User* u){
        user = u;
    }

    User* getUser() const{
        return user;
    }

    void setRestaurant(Restaurant* r){
        restaurant = r;
    }

    Restaurant* getRestaurant() const{
        return restaurant;
    }

    void setItems(const vector<MenuItem> &items){
        this->items = items;
        total = 0.0;
        for(const auto &item : items){
            total += item.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const{
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* strategy){
        paymentStrategy = strategy;
    }

    string getStatus() const {
        return status;
    }

    void setStatus(const string &s) {
        status = s;
    }

    double getTotalAmount() const {
        return total;
    }

    void setTotal(double t) {
        total = t;
    }

    void setScheduled(const string &s) {
        schedule = s;
    }

    string getScheduled() const {
        return schedule;
    }
};

#endif // ORDER_H