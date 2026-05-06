#include <iostream>
using namespace std;

int main() {

    //Завдання 1
    {
        int seconds;
        cout << "\n[1] Введіть секунди: ";
        cin >> seconds;

        int hour = seconds / 3600;
        int minut = (seconds % 3600) / 60;
        int sec = seconds % 60;

        cout << hour << " год " << minut << " хв " << sec << " сек\n";
    }


    //Завдання2
    {
        double num;
        cout << "\n[2] Введіть число: ";
        cin >> num;
        int grivn = (int)num;
        int kopiyk = (num - grivn) * 100;

        cout << grivn << " грн " << kopiyk << " коп.\n";
    }


    //Завдання 3
    {
        int distance, min, sec;
        cout << "\n[3] Введіть дистанцію (м): ";
        cin >> distance;
        cout << "Введіть час (хв сек): ";
        cin >> min >> sec;
        int totalSec = min * 60 + sec;
        double speed = (distance / 1000.0) / (totalSec / 3600.0);

        cout << "Час: " << min << " хв " << sec << " сек = " << totalSec << " сек\n";
        cout << "Швидкість: " << speed << " км/год\n";
    }


    //Завдання 4
    {
        int days;
        cout << "\n[4] Введіть кількість днів: ";
        cin >> days;
        int week = days / 7;

        int remain = days % 7;

        cout << week << " тижні(в) і " << remain << " дні(в)\n";
    }


    //Завдання 5
    {
        double distance, time;
        cout << "\n[5] Введіть відстань (км): ";
        cin >> distance;

        cout << "Введіть час (год): ";
        cin >> time;

        double speed = distance / time;

        cout << "Потрібна швидкість: " << speed << " км/год\n";
    }


    //Завдання 6
    {
        double distance, consumption;
        double price1, price2, price3;

        cout << "\n[6] Введіть відстань (км): ";
        cin >> distance;

        cout << "Витрата (л/100км): ";
        cin >> consumption;

        cout << "Ціна бензину 1: ";
        cin >> price1;

        cout << "Ціна бензину 2: ";
        cin >> price2;

        cout << "Ціна бензину 3: ";
        cin >> price3;

        double liters = distance * consumption / 100;
        cout << "\nВартість поїздки:\n";
        cout << "Бензин 1: " << liters * price1 << " грн\n";
        cout << "Бензин 2: " << liters * price2 << " грн\n";
        cout << "Бензин 3: " << liters * price3 << " грн\n";
    }


 

    //Завдання 8
    {
        int seconds;
        cout << "\n[8] Введіть секунди з початку робочого дня: ";
        cin >> seconds;
        int workDay = 8 * 3600;
        int remain = workDay - seconds;
        int hoursLeft = remaining / 3600;
        cout << "Залишилось повних годин: " << hoursLeft << endl;
    }

    return 0;
}