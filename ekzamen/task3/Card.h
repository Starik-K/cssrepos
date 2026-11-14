#pragma once
#include "Account.h"

class Card : public Account
{
private:
    bool credit;
    double creditLimit;

public:
    Card();
    Card(string name, double balance, bool credit, double creditLimit);

    bool spendMoney(double amount) override;
    string getType() const override;

    void showInfo() const override;
};
