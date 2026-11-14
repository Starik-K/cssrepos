#include "Wallet.h"

Wallet::Wallet() : Account()
{
}

Wallet::Wallet(string name, double balance)
    : Account(name, balance)
{
}

bool Wallet::spendMoney(double amount)
{
    if (amount <= 0 || amount > balance)
    {
        cout << "Недостатньо коштів!" << endl;
        return false;
    }

    balance -= amount;
    cout << "Витрату виконано!" << endl;

    return true;
}

string Wallet::getType() const
{
    return "Гаманець";
}

void Wallet::showInfo() const
{
    cout << "\nТип: Гаманець" << endl;
    Account::showInfo();
}
