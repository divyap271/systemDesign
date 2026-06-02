# Food Delivery System

A robust C++ implementation of a food delivery system demonstrating several key design patterns and software engineering principles.

## Design Patterns Implemented

### 1. Singleton Pattern
Used in `OrderManager` and `RestaurantManager`. 
- **Purpose**: Ensures that only one instance of these manager classes exists throughout the application's lifecycle.
- **Benefit**: Provides a global point of access to order and restaurant data, preventing synchronization issues and ensuring data consistency.

### 2. Factory Method Pattern
Implemented via `OrderFactory` (abstract interface) and `NowOrderFactory` (concrete implementation).
- **Purpose**: Decouples the client code from the specific classes being instantiated (`DeliveryOrder` vs. `PickupOrder`).
- **Benefit**: Makes the system easily extensible. Adding a new order type only requires a new class and a small update to a factory, without changing the core ordering logic.

### 3. Strategy Pattern
Used for the payment system (`PaymentStrategy`, `CreditCardPaymentStrategy`, `UpiPaymentStrategy`).
- **Purpose**: Defines a family of algorithms (payment methods), encapsulates each one, and makes them interchangeable.
- **Benefit**: Allows the payment method to be selected at runtime. The `Order` class doesn't need to know the details of how a payment is processed; it just calls the `pay()` method on the injected strategy.

### 4. Facade Pattern
The `FoodDeliverySystem` class (in `App.h`) acts as a Facade.
- **Purpose**: Provides a simplified, high-level interface to a complex set of subsystems (Managers, Factories, Strategies, and Services).
- **Benefit**: The client (`main.cpp`) only interacts with the `FoodDeliverySystem` instead of having to coordinate multiple objects manually, reducing complexity and coupling.

### 5. Notification Service
Implemented in `NotificationService.h`.
- **Purpose**: Decouples the order processing logic from the notification delivery logic.
- **Benefit**: Allows the system to easily change how notifications are sent (e.g., adding Email or SMS support) without modifying the `Order` or `FoodDeliverySystem` classes.

### 6. Polymorphism & Inheritance
The core `Order` class serves as a base for `DeliveryOrder` and `PickupOrder`.
- **Purpose**: Allows the system to treat different types of orders uniformly while still maintaining specific behaviors (like delivery addresses vs. pickup locations).
- **Benefit**: Simplifies the codebase by using a common interface for all order types.

### 7. Mediator Pattern
The `FoodDeliverySystem` class acts as a central coordinator between different components.
- **Purpose**: Encapsulates how a set of objects (User, Restaurant, OrderManager, RestaurantManager) interact.
- **Benefit**: Prevents direct coupling between components, allowing them to communicate through the mediator, which simplifies maintenance and enhances reusability.

### 8. Memento Pattern
Conceptually used for state management within the ordering flow.
- **Purpose**: Captures and externalizes an object's internal state (like a `Cart` or `Order` status) to allow it to be restored later if needed.
- **Benefit**: Enables features like "undoing" item additions to a cart or tracking historical changes to an order's lifecycle.

### 9. Null Object Pattern
Can be applied to handle missing resources (e.g., when a restaurant or menu item is not found).
- **Purpose**: Provides a surrogate object that implements the same interface as the real object but performs no action.
- **Benefit**: Simplifies client code by removing the need for repetitive null checks and preventing potential runtime crashes.

### 10. Prototype Pattern
Applicable for the creation of `MenuItem` or `Order` objects.
- **Purpose**: Creates new objects by cloning an existing prototypical instance.
- **Benefit**: Improves efficiency when creating complex objects that are mostly similar to existing ones, reducing the overhead of full initialization.

### 11. State Design Pattern
Used to manage the lifecycle of an `Order`.
- **Purpose**: Allows an object to change its behavior based on its current state (e.g., `Placed`, `Preparing`, `Out for Delivery`, `Delivered`).
- **Benefit**: Simplifies state-specific logic by encapsulating state-dependent behaviors into separate transitions rather than complex conditional blocks.

### 12. Visitor Pattern
Useful for extending operations on the `Order` or `MenuItem` hierarchies.
- **Purpose**: Separates an algorithm from the object structure on which it operates.
- **Benefit**: Allows adding new operations (like tax calculation, discount application, or reporting) to existing classes without modifying them.

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
- `models/`: Core data structures (User, Restaurant, MenuItem, and Order hierarchies).
- `managers/`: Singleton managers for centralized state handling.
- `factories/`: Factory classes for object creation.
- `strategies/`: Interchangeable algorithms for payment processing.
- `services/`: Supporting services like notifications.
- `utils/`: Common utility functions.
