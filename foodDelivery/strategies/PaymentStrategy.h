#ifndef PAYMENT_STRATEGY_H
#define PAYMENT_STRATEGY_H

#include <iostream>
#include <string>

using namespace std;
class PaymentStrategy {
    public:
    virtual ~PaymentStrategy() {}
    virtual void pay(double amount) = 0;
};

#endif // PAYMENT_STRATEGY_H