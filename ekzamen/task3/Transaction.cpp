#include "Transaction.h"

Transaction::Transaction()
{
    name = "";
    category = "";
    account = "";
    amount = 0;
    income = false;
    date = "";
}

Transaction::Transaction(string name, string category, string account,
    double amount, bool income, string date)
{
    this->name = name;
    this->category = category;
    this->account = account;
    this->amount = amount;
    this->income = income;
    this->date = date;
}

string Transaction::getName() const
{
    return name;
}

string Transaction::getCategory() const
{
    return category;
}

string Transaction::getAccount() const
{
    return account;
}

double Transaction::getAmount() const
{
    return amount;
}

bool Transaction::isIncome() const
{
    return income;
}

string Transaction::getDate() const
{
    return date;
}

void Transaction::showInfo() const
{
    cout << "\nНазва: " << name << endl;
    cout << "Категорія: " << category << endl;
    cout << "Рахунок: " << account << endl;
    cout << "Сума: " << amount << endl;
    cout << "Дата: " << date << endl;

    if (income)
        cout << "Тип: Прибуток" << endl;
    else
        cout << "Тип: Витрата" << endl;
}