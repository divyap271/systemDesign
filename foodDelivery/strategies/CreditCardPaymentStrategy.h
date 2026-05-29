#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy{
    private:
    string cardNumber;

    public:
    CreditCardPaymentStrategy(const string &card){
        cardNumber = card;
    }

    void pay(double amount) override{
        cout << "Processing credit card payment of $" << fixed << setprecision(2) << amount
             << " using card number: " << cardNumber << endl;
    }
};

#endif // CREDIT_CARD_PAYMENT_STRATEGY_H