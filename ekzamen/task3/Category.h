#pragma once
#include <iostream>
#include <string>
using namespace std;

class Category
{
private:
    string name;
    bool income;

public:
    Category();
    Category(string name, bool income);

    string getName() const;
    bool isIncome() const;

    void showInfo() const;
};