#include "Report.h"
#include <fstream>
#include <algorithm>

void Report::showDayReport(vector<Transaction> transactions, string date)
{
    double total = 0;

    cout << "\n-===== ЗВІТ ЗА ДЕНЬ =====-" << endl;

    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i].getDate() == date && !transactions[i].isIncome())
        {
            transactions[i].showInfo();
            total += transactions[i].getAmount();
        }
    }

    cout << "\nВсього витрат: " << total << endl;
}

void Report::showWeekReport(vector<Transaction> transactions, string startDate, string endDate)
{
    double total = 0;

    cout << "\n-===== ЗВІТ ЗА ТИЖДЕНЬ =====-" << endl;

    for (int i = 0; i < transactions.size(); i++)
    {
        string date = transactions[i].getDate();

        if (!transactions[i].isIncome() && date >= startDate && date <= endDate)
        {
            transactions[i].showInfo();
            total += transactions[i].getAmount();
        }
    }

    cout << "\nВсього витрат: " << total << endl;
}

void Report::showMonthReport(vector<Transaction> transactions, string month)
{
    double total = 0;

    cout << "\n===== ЗВІТ ЗА МІСЯЦЬ =====" << endl;

    for (int i = 0; i < transactions.size(); i++)
    {
        string date = transactions[i].getDate();

        if (!transactions[i].isIncome() && date.substr(0, 7) == month)
        {
            transactions[i].showInfo();
            total += transactions[i].getAmount();
        }
    }

    cout << "\nВсього витрат: " << total << endl;
}

void Report::showTopExpenses(vector<Transaction> transactions, string startDate, string endDate)
{
    vector<Transaction> expenses;

    for (int i = 0; i < transactions.size(); i++)
    {
        string date = transactions[i].getDate();

        if (!transactions[i].isIncome() && date >= startDate && date <= endDate)
        {
            expenses.push_back(transactions[i]);
        }
    }

    sort(expenses.begin(), expenses.end(),
        [](Transaction a, Transaction b)
        {
            return a.getAmount() > b.getAmount();
        });

    cout << "\n===== ТОП-3 ВИТРАТ =====" << endl;

    for (int i = 0; i < expenses.size() && i < 3; i++)
    {
        expenses[i].showInfo();
    }
}

void Report::showTopCategories(vector<Transaction> transactions, string startDate, string endDate)
{
    vector<string> names;
    vector<double> sums;

    for (int i = 0; i < transactions.size(); i++)
    {
        string date = transactions[i].getDate();

        if (transactions[i].isIncome() || date < startDate || date > endDate)
            continue;

        string category = transactions[i].getCategory();

        int position = -1;

        for (int j = 0; j < names.size(); j++)
        {
            if (names[j] == category)
            {
                position = j;
                break;
            }
        }

        if (position == -1)
        {
            names.push_back(category);
            sums.push_back(transactions[i].getAmount());
        }
        else
        {
            sums[position] += transactions[i].getAmount();
        }
    }

    for (int i = 0; i < names.size(); i++)
    {
        for (int j = i + 1; j < names.size(); j++)
        {
            if (sums[j] > sums[i])
            {
                swap(sums[i], sums[j]);
                swap(names[i], names[j]);
            }
        }
    }

    cout << "\n-===== ТОП-3 КАТЕГОРІЙ =====-" << endl;

    for (int i = 0; i < names.size() && i < 3; i++)
    {
        cout << i + 1 << ". " << names[i] << " - " << sums[i] << endl;
    }
}

void Report::saveToFile(string text)
{
    ofstream file("reports.txt", ios::app);

    if (file.is_open())
    {
        file << text << endl;
        file.close();

        cout << "Збережено у файл reports.txt" << endl;
    }
}