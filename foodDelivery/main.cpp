#include "App.h"
#include <iostream>

using namespace std;

int main() {
    // 1. Initialize the Central System (Facade)
    FoodDeliverySystem system;

    // 2. Add some restaurants
    Restaurant* r1 = new Restaurant("Pizza Hut", "Downtown");
    r1->addMenuItem(MenuItem("P1", "Margherita Pizza", 12));
    r1->addMenuItem(MenuItem("P2", "Pepperoni Pizza", 15));
    system.addRestaurant(r1);

    Restaurant* r2 = new Restaurant("Burger King", "Uptown");
    r2->addMenuItem(MenuItem("B1", "Whopper", 8));
    system.addRestaurant(r2);

    // 3. Setup User
    User* user = new User(1, "John Doe", "123 Main St");

    // 4. User Interaction Flow
    cout << "--- Customer Searching for Food ---" << endl;
    vector<Restaurant*> results = system.searchRestaurants("downtown");
    
    if (!results.empty()) {
        Restaurant* selected = results[0];
        cout << "Found Restaurant: " << selected->getName() << endl;

        // 5. Add to Cart
        user->getCart()->setRestaurant(selected);
        user->getCart()->addItem(selected->getMenuItems()[0]);
        
        // 6. Place Order via System
        cout << "\n--- Placing Order ---" << endl;
        system.placeOrder(user, selected, new UpiPaymentStrategy("9876543210@upi"), "Delivery");
    }

    // 7. Show all orders in the system
    cout << "\n--- System Audit: Order History ---" << endl;
    system.showOrders();

    // Cleanup
    delete user;
    delete r1;
    delete r2;

    return 0;
}
