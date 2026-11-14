#include "Category.h"

Category::Category()
{
    name = "";
    income = false;
}

Category::Category(string name, bool income)
{
    this->name = name;
    this->income = income;
}

string Category::getName() const
{
    return name;
}

bool Category::isIncome() const
{
    return income;
}

void Category::showInfo() const
{
    cout << name;

    if (income)
        cout << " (прибуток)";
    else
        cout << " (витрата)";
}