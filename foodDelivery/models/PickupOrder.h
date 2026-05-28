#ifdef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include "Order.h"

using namespace std;

class PickupOrder : public Order{
    private:
    string resturantAddress;

    public:
    PickupOrder(){
        resturantAddress = "";
    }
    string getType() const override{
        return "Pickup";
    }

    void setResturantAddress(const string &address){
        resturantAddress = address;
    }

    string getResturantAddress() const{
        return resturantAddress;
    }
};

#endif // PICKUP_ORDER_H