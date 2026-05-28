// The strategy design pattern is a behavioral design pattern that allows you to define a family of algorithms, encapsulate each one into a seprate class, and make their objects interchangable at runtime.
// Instead of having a single class that handle multiple variations of a behavior with massive if-else or switch statements the strtegy patern lets the class delegate that behavior to a seprate strategy object.

// A Real-World Analogy
// Imagine you need to get to the airport. You could drive your car, take a taxi, or ride the bus.
// Your goal is the same: reach the airport.
// Your strategy changes based on context (budget, time constraints, luggage).

// How it Works
// The pattern consists of three main parts:
// The Context: The object that needs something done. It maintains a reference to a Strategy object and doesn't know exactly how the strategy is implemented.
// The Strategy Interface: A common interface that all concrete strategies must implement.
// Concrete Strategies: The specific implementations of the algorithm.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// The strategy Interface
// We define a common interface for all payment methods
class PaymentStrategy{
    public:
    virtual void pay(double amount) = 0;
};

// Concrete Strategies
// We create specific classes for each payment method. Notice how we can add new payment methods later without touching existing code (following the Open/Closed Principle).
class CreditCardPayment : public PaymentStrategy{
    private:
    string cardNumber;
    string cardHolderName;
    string expiryDate;
    public:
    CreditCardPayment(const string &number, const string &holder, const string &expiry) : cardNumber(number), cardHolderName(holder), expiryDate(expiry) {}
    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card." << endl;
    }
};

class PayPalPayment : public PaymentStrategy{
    private:
    string email;
    public:
    PayPalPayment(const string &email) : email(email) {}
    void pay(double amount) override {
        cout << "Paid " << amount << " using PayPal." << endl;
    }
};

// The Context
// The ShoppingCart doesn't care how the payment is processed. It just knows it has a PaymentStrategy that it can call.

class ShoppingCart{
    private:
    unique_ptr<PaymentStrategy> paymentMethod;
    public:
    void setPaymentMethod(unique_ptr<PaymentStrategy> method){
        paymentMethod = move(method);
    }
    void checkout(double amount){
        if(paymentMethod){
            paymentMethod->pay(amount);
        } else {
            cout << "No payment method selected!" << endl;
        }
    }
};

// usage in action
int main(){
    ShoppingCart cart;
    cart.setPaymentMethod(make_unique<CreditCardPayment>("1234-5678-9012-3456", "John Doe", "12/25"));
    cart.checkout(100.0);

    cart.setPaymentMethod(make_unique<PayPalPayment>("john.doe@example.com"));
    cart.checkout(200.0);

    return 0;
}