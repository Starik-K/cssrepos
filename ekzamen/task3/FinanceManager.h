#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Account.h"
#include "Wallet.h"
#include "Card.h"
#include "Category.h"
#include "Transaction.h"
#include "Report.h"
using namespace std;

class FinanceManager
{
private:
    vector<Account*> accounts;
    vector<Category> categories;
    vector<Transaction> transactions;

    void addDefaultCategories();
    void showAccounts();
    void showCategories();
    void addAccount();
    void refillAccount();
    void addTransaction();
    void makeDonation();
    void showTransactions();
    void reportsMenu();
    void saveReport(int type, string first, string second);

public:
    FinanceManager();
    ~FinanceManager();

    void menu();
};