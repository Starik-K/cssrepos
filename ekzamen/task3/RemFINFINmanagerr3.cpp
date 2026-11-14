#include <iostream>
#include <windows.h>
#include <clocale>
#include "FinanceManager.h"

using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    FinanceManager manager;

    manager.menu();

    return 0;
}