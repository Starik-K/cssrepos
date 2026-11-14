#pragma once
#include "Account.h"

class Wallet : public Account
{
public:
    Wallet();
    Wallet(string name, double balance);

    bool spendMoney(double amount) override;
    string getType() const override;

    void showInfo() const override;
};
