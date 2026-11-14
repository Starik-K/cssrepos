#pragma once
#include <iostream>
#include <string>
using namespace std;

class Transaction
{
private:
    string name;
    string category;
    string account;
    double amount;
    bool income;
    string date;

public:
    Transaction();
    Transaction(string name, string category, string account,
        double amount, bool income, string date);

    string getName() const;
    string getCategory() const;
    string getAccount() const;
    double getAmount() const;
    bool isIncome() const;
    string getDate() const;

    void showInfo() const;
};