#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <iostream>
#include "../models/Order.h"

using namespace std;

class OrderManager {
    private:
    vector<Order *> orders;
    inline static OrderManager *instance = nullptr;

    OrderManager() {}

    public:
    static OrderManager *getInstance(){
        if(!instance){
            instance = new OrderManager();
        }
        return instance;
    }

    void addOrder(Order *order){
        orders.push_back(order);
    }

    void listOrders(){
        cout << "Orders:" << endl;
        for(const auto &order : orders){
            cout << "Order ID: " << order->getOrderId() << ", Type: "
                    << order->getType() << ", Status: " << order->getStatus() << endl;
        }
    }
};

#endif // ORDER_MANAGER_H