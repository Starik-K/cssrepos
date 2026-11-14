#include "FinanceManager.h"
#include <fstream>
#include <sstream>

FinanceManager::FinanceManager()
{
    addDefaultCategories();
}

FinanceManager::~FinanceManager()
{
    for (int i = 0; i < accounts.size(); i++)
    {
        delete accounts[i];
    }
}

void FinanceManager::addDefaultCategories()
{
    categories.push_back(Category("Їжа", false));
    categories.push_back(Category("Транспорт", false));
    categories.push_back(Category("Розваги", false));
    categories.push_back(Category("Покупки", false));
    categories.push_back(Category("Благодійність", false));
    categories.push_back(Category("Зарплата", true));
    categories.push_back(Category("Подарунки", true));
}

void FinanceManager::showAccounts()
{
    cout << "\n===== МОЇ РАХУНКИ =====" << endl;

    if (accounts.empty())
    {
        cout << "Рахунків поки немає." << endl;
        return;
    }

    for (int i = 0; i < accounts.size(); i++)
    {
        cout << "\n" << i + 1 << ". ";
        accounts[i]->showInfo();
    }
}

void FinanceManager::showCategories()
{
    cout << "\n===== КАТЕГОРІЇ =====" << endl;

    for (int i = 0; i < categories.size(); i++)
    {
        cout << i + 1 << ". ";
        categories[i].showInfo();
        cout << endl;
    }
}

void FinanceManager::addAccount()
{
    int choice;
    string name;

    cout << "\n1. Гаманець" << endl;
    cout << "2. Дебетова картка" << endl;
    cout << "3. Кредитна картка" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;

    cout << "Назва рахунку: ";
    cin >> ws;
    getline(cin, name);

    if (choice == 1)
    {
        accounts.push_back(new Wallet(name, 0));
    }
    else if (choice == 2)
    {
        accounts.push_back(new Card(name, 0, false, 0));
    }
    else if (choice == 3)
    {
        double limit;

        cout << "Кредитний ліміт: ";
        cin >> limit;

        if (limit <= 0)
        {
            cout << "Некоректний ліміт!" << endl;
            return;
        }

        accounts.push_back(new Card(name, 0, true, limit));
    }
    else
    {
        cout << "Невірний вибір!" << endl;
        return;
    }

    cout << "Рахунок створено!" << endl;
}

void FinanceManager::refillAccount()
{
    if (accounts.empty())
    {
        cout << "Спочатку створіть рахунок!" << endl;
        return;
    }

    showAccounts();

    int number;
    double amount;

    cout << "\nНомер рахунку: ";
    cin >> number;

    if (number < 1 || number > accounts.size())
    {
        cout << "Невірний номер!" << endl;
        return;
    }

    cout << "Сума поповнення: ";
    cin >> amount;

    accounts[number - 1]->addMoney(amount);
}

void FinanceManager::addTransaction()
{
    if (accounts.empty())
    {
        cout << "Спочатку створіть рахунок!" << endl;
        return;
    }

    int type;

    cout << "\n1. Витрата" << endl;
    cout << "2. Прибуток" << endl;
    cout << "Ваш вибір: ";
    cin >> type;

    if (type != 1 && type != 2)
    {
        cout << "Невірний вибір!" << endl;
        return;
    }

    bool income = (type == 2);

    cout << "\nОберіть рахунок:" << endl;
    showAccounts();

    int accountNumber;

    cout << "Номер рахунку: ";
    cin >> accountNumber;

    if (accountNumber < 1 || accountNumber > accounts.size())
    {
        cout << "Невірний номер!" << endl;
        return;
    }

    cout << "\nОберіть категорію:" << endl;

    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].isIncome() == income)
        {
            cout << i + 1 << ". ";
            categories[i].showInfo();
            cout << endl;
        }
    }

    int categoryNumber;

    cout << "Номер категорії: ";
    cin >> categoryNumber;

    if (categoryNumber < 1 || categoryNumber > categories.size())
    {
        cout << "Невірний номер!" << endl;
        return;
    }

    if (categories[categoryNumber - 1].isIncome() != income)
    {
        cout << "Ця категорія не підходить для операції!" << endl;
        return;
    }

    string name;
    string date;
    double amount;

    cout << "Назва операції: ";
    cin >> ws;
    getline(cin, name);

    cout << "Сума: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Некоректна сума!" << endl;
        return;
    }

    cout << "Дата (РРРР-ММ-ДД): ";
    cin >> date;

    if (income)
    {
        accounts[accountNumber - 1]->addMoney(amount);
    }
    else
    {
        if (!accounts[accountNumber - 1]->spendMoney(amount))
        {
            return;
        }
    }

    transactions.push_back(Transaction(
        name,
        categories[categoryNumber - 1].getName(),
        accounts[accountNumber - 1]->getName(),
        amount,
        income,
        date
    ));

    cout << "Операцію додано!" << endl;
}

void FinanceManager::makeDonation()
{
    if (accounts.empty())
    {
        cout << "Спочатку створіть рахунок!" << endl;
        return;
    }

    string organization;
    string date;
    double amount;
    int number;

    cout << "\n===== ДОПОМОГА ДОНАТОМ =====" << endl;

    cout << "Назва організації або фонду: ";
    cin >> ws;
    getline(cin, organization);

    showAccounts();

    cout << "\nОберіть рахунок: ";
    cin >> number;

    if (number < 1 || number > accounts.size())
    {
        cout << "Невірний номер рахунку!" << endl;
        return;
    }

    cout << "Сума донату: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Некоректна сума!" << endl;
        return;
    }

    cout << "Дата (РРРР-ММ-ДД): ";
    cin >> date;

    if (!accounts[number - 1]->spendMoney(amount))
    {
        return;
    }

    transactions.push_back(Transaction(
        organization,
        "Благодійність",
        accounts[number - 1]->getName(),
        amount,
        false,
        date
    ));

    cout << "\nДякуємо за вашу допомогу!" << endl;
    cout << "Донат додано до історії операцій!" << endl;
}

void FinanceManager::showTransactions()
{
    cout << "\n===== ІСТОРІЯ ОПЕРАЦІЙ =====" << endl;

    if (transactions.empty())
    {
        cout << "Операцій поки немає." << endl;
        return;
    }

    for (int i = 0; i < transactions.size(); i++)
    {
        transactions[i].showInfo();
    }
}

void FinanceManager::saveReport(int type, string first, string second)
{
    ostringstream output;
    streambuf* oldBuffer = cout.rdbuf();

    cout.rdbuf(output.rdbuf());

    if (type == 1)
        Report::showDayReport(transactions, first);
    else if (type == 2)
        Report::showWeekReport(transactions, first, second);
    else if (type == 3)
        Report::showMonthReport(transactions, first);
    else if (type == 4)
        Report::showTopExpenses(transactions, first, second);
    else if (type == 5)
        Report::showTopCategories(transactions, first, second);

    cout.rdbuf(oldBuffer);

    string reportText = output.str();

    cout << reportText;
    Report::saveToFile(reportText);
}

void FinanceManager::reportsMenu()
{
    int choice;
    string first, second;

    cout << "\n===== ЗВІТИ ТА РЕЙТИНГИ =====" << endl;
    cout << "1. Звіт за день" << endl;
    cout << "2. Звіт за тиждень" << endl;
    cout << "3. Звіт за місяць" << endl;
    cout << "4. ТОП-3 витрат за тиждень" << endl;
    cout << "5. ТОП-3 витрат за місяць" << endl;
    cout << "6. ТОП-3 категорій за тиждень" << endl;
    cout << "7. ТОП-3 категорій за місяць" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Дата (РРРР-ММ-ДД): ";
        cin >> first;

        saveReport(1, first, "");
    }
    else if (choice == 2 || choice == 4 || choice == 6)
    {
        cout << "Початкова дата (РРРР-ММ-ДД): ";
        cin >> first;

        cout << "Кінцева дата (РРРР-ММ-ДД): ";
        cin >> second;

        if (choice == 2)
            saveReport(2, first, second);
        else if (choice == 4)
            saveReport(4, first, second);
        else
            saveReport(5, first, second);
    }
    else if (choice == 3)
    {
        cout << "Місяць (РРРР-ММ): ";
        cin >> first;

        saveReport(3, first, "");
    }
    else if (choice == 5 || choice == 7)
    {
        cout << "Початкова дата місяця (РРРР-ММ-ДД): ";
        cin >> first;

        cout << "Кінцева дата місяця (РРРР-ММ-ДД): ";
        cin >> second;

        if (choice == 5)
            saveReport(4, first, second);
        else
            saveReport(5, first, second);
    }
    else
    {
        cout << "Невірний вибір!" << endl;
    }
}

void FinanceManager::menu()
{
    int choice;

    do
    {
        cout << "\n========== УПРАВЛІННЯ ФІНАНСАМИ ==========" << endl;
        cout << "1. Створити гаманець або картку" << endl;
        cout << "2. Поповнити рахунок" << endl;
        cout << "3. Додати витрату або прибуток" << endl;
        cout << "4. Переглянути рахунки" << endl;
        cout << "5. Переглянути категорії" << endl;
        cout << "6. Історія операцій" << endl;
        cout << "7. Звіти та рейтинги" << endl;
        cout << "8. Допомогти донатом" << endl;
        cout << "0. Вихід" << endl;

        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addAccount();
            break;

        case 2:
            refillAccount();
            break;

        case 3:
            addTransaction();
            break;

        case 4:
            showAccounts();
            break;

        case 5:
            showCategories();
            break;

        case 6:
            showTransactions();
            break;

        case 7:
            reportsMenu();
            break;

        case 8:
            makeDonation();
            break;

        case 0:
            cout << "До побачення!" << endl;
            break;

        default:
            cout << "Невірний вибір!" << endl;
        }

    } while (choice != 0);
}