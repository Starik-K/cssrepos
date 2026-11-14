#include "Card.h"
Card::Card() : Account()
{
    credit = false;
    creditLimit = 0;
}

Card::Card(string name, double balance, bool credit, double creditLimit)
    : Account(name, balance)
{
    this->credit = credit;
    this->creditLimit = creditLimit;
}

bool Card::spendMoney(double amount)
{
    if (amount <= 0)
    {
        cout << "Некоректна сума!" << endl;
        return false;
    }

    if (credit)
    {
        if (balance - amount < -creditLimit)
        {
            cout << "Перевищено кредитний ліміт!" << endl;
            return false;
        }
    }
    else
    {
        if (amount > balance)
        {
            cout << "Недостатньо коштів!" << endl;
            return false;
        }
    }

    balance -= amount;

    cout << "Оплату виконано!" << endl;
    return true;
}

string Card::getType() const
{
    if (credit)
        return "Кредитна картка";

    return "Дебетова картка";
}

void Card::showInfo() const
{
    cout << "\nТип: " << getType() << endl;
    Account::showInfo();

    if (credit)
        cout << "Кредитний ліміт: " << creditLimit << endl;
}
