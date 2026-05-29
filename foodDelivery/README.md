# Food Delivery System

A simple C++ implementation of a food delivery system demonstrating various design patterns:
- **Singleton Pattern**: `OrderManager`, `RestaurantManager`
- **Factory Pattern**: `OrderFactory`, `NowOrderFactory`
- **Strategy Pattern**: `PaymentStrategy`, `CreditCardPaymentStrategy`, `UpiPaymentStrategy`
- **Observer/Notification Service**: `NotificationService`

## Prerequisites
- C++17 compatible compiler (e.g., g++, clang++)

## How to Run

1. Compile the application:
   ```bash
   g++ -std=c++17 main.cpp -o app
   ```

2. Run the executable:
   ```bash
   ./app
   ```

## Directory Structure
- `models/`: Contains the core data structures (User, Restaurant, Order, etc.)
- `managers/`: Contains singleton managers for orders and restaurants.
- `factories/`: Contains order creation factories.
- `strategies/`: Contains payment method strategies.
- `services/`: Contains notification services.
- `utils/`: Contains utility functions (e.g., TimeUtils).
