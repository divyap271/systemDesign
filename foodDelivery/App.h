#ifndef APP_H
#define APP_H

#include <vector>
#include <string>
#include <memory>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/OrderManager.h"
#include "managers/RestaurantManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/UpiPaymentStrategy.h"
#include "strategies/CreditCardPaymentStrategy.h"
#include "factories/NowOrderFactory.h"
#include "services/NotificationService.h"

using namespace std;

class FoodDeliverySystem {
private:
    RestaurantManager* restaurantManager;
    OrderManager* orderManager;
    OrderFactory* orderFactory;

public:
    FoodDeliverySystem() {
        restaurantManager = RestaurantManager::getInstance();
        orderManager = OrderManager::getInstance();
        orderFactory = new NowOrderFactory();
    }

    ~FoodDeliverySystem() {
        delete orderFactory;
    }

    void addRestaurant(Restaurant* r) {
        restaurantManager->addRestaurant(r);
    }

    vector<Restaurant*> searchRestaurants(const string& location) {
        return restaurantManager->searchByLocation(location);
    }

    bool placeOrder(User* user, Restaurant* restaurant, PaymentStrategy* paymentMethod, const string& type) {
        Cart* cart = user->getCart();
        if (cart->isEmpty()) {
            cout << "Cannot place order: Cart is empty!" << endl;
            return false;
        }

        Order* order = orderFactory->createOrder(user, cart, restaurant, cart->getItems(), paymentMethod, type);
        
        if (order && order->processPayment()) {
            orderManager->addOrder(order);
            NotificationService::notify(order);
            cart->clear();
            return true;
        }

        return false;
    }

    void showOrders() {
        orderManager->listOrders();
    }
};

#endif // APP_H
