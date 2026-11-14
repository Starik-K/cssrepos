#include "Account.h"

Account::Account()
{
    name = "";
    balance = 0;
}

Account::Account(string name, double balance)
{
    this->name = name;
    this->balance = balance;
}

string Account::getName() const
{
    return name;
}

double Account::getBalance() const
{
    return balance;
}

void Account::setName(string name)
{
    this->name = name;
}

void Account::addMoney(double amount)
{
    if (amount > 0)
    {
        balance += amount;
        cout << "Рахунок поповнено!" << endl;
    }
    else
    {
        cout << "Некоректна сума!" << endl;
    }
}

void Account::showInfo() const
{
    cout << "Назва: " << name << endl;
    cout << "Баланс: " << balance << endl;
}

Account::~Account()
{
}
