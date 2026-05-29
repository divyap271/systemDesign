#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include "../models/Order.h"

using namespace std;

class NotificationService{
    public:
    static void notify(Order *order){
        cout << "Notification: Order ID " << order->getOrderId() << " is now " << order->getStatus() << endl;
        cout << "Order Type: " << order->getType() << endl;
        cout << "Total Amount: $" << order->getTotalAmount() << endl;
        cout << "Items:" << endl;
        for(const auto &item : order->getItems()){
            cout << "- " << item.getName() << " ($" << item.getPrice() << ")" << endl;
        }
        cout << "-----------------------------" << endl;
        cout << "Thank you for using our food delivery service!" << endl;
    }
};

#endif // NOTIFICATION_SERVICE_H