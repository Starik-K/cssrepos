#include "Category.h"

Category::Category()
{
    name = "";
}

Category::Category(string name)
{
    this->name = name;
}

string Category::getName() const
{
    return name;
}

vector<Test> Category::getTests() const
{
    return tests;
}

void Category::setName(string name)
{
    this->name = name;
}

void Category::addTest(Test test)
{
    tests.push_back(test);
}

void Category::removeTest(int index)
{
    if (index >= 0 && index < tests.size())
    {
        tests.erase(tests.begin() + index);
    }
}

void Category::editTest(int index, Test test)
{
    if (index >= 0 && index < tests.size())
    {
        tests[index] = test;
    }
}

int Category::getTestsCount() const
{
    return tests.size();
}

Test Category::getTest(int index) const
{
    if (index >= 0 && index < tests.size())
    {
        return tests[index];
    }

    return Test();
}