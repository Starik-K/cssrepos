#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"
using namespace std;

class Report
{
public:
    static void showDayReport(vector<Transaction> transactions, string date);
    static void showWeekReport(vector<Transaction> transactions, string startDate, string endDate);
    static void showMonthReport(vector<Transaction> transactions, string month);

    static void showTopExpenses(vector<Transaction> transactions, string startDate, string endDate);
    static void showTopCategories(vector<Transaction> transactions, string startDate, string endDate);

    static void saveToFile(string text);
};