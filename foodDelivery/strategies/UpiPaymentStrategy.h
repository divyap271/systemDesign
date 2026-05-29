#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include<iostream>
#include <string>
#include <iomanip>

using namespace std;

class UpiPaymentStrategy : public PaymentStrategy{
    private:
    string mobile;
    public:
    UpiPaymentStrategy(const string &mob){
        mobile = mob;
    }
    void pay(double amount) override{
        cout << "Processing UPI payment of Rs. " << fixed << setprecision(2) << amount
             << " from mobile number: " << mobile << endl;
    }
};

#endif // UPI_PAYMENT_STRATEGY_H