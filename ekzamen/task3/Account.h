#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account
{
protected:
    string name;
    double balance;

public:
    Account();
    Account(string name, double balance);

    string getName() const;
    double getBalance() const;

    void setName(string name);
    void addMoney(double amount);

    virtual bool spendMoney(double amount) = 0;
    virtual string getType() const = 0;

    virtual void showInfo() const;

    virtual ~Account();
};
