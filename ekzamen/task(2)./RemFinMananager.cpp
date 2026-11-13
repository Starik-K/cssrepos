#include <iostream>
#include <Windows.h>
#include "TestSystem.h"

using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    TestSystem system;
    system.run();

    return 0;
}