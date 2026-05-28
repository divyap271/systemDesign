#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include "Order.h"
#include <string>

using namespace std;

class DeliveryOrder : public Order{
    private:
    string userAddress;
    
    public:
    DeliveryOrder() {
        userAddress = "";
    }

    string getType() const override {
        return "Delivery";
    }

    void setUserAddress(const string &address){
        userAddress = address;
    }

    string getUserAddress() const{
        return userAddress;
    }
};

#endif // DELIVERY_ORDER_H