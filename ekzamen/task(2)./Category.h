#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Test.h"
using namespace std;

class Category
{
private:
    string name;
    vector<Test> tests;

public:
    Category();
    Category(string name);

    string getName() const;
    vector<Test> getTests() const;

    void setName(string name);

    void addTest(Test test);
    void removeTest(int index);
    void editTest(int index, Test test);

    int getTestsCount() const;
    Test getTest(int index) const;
};