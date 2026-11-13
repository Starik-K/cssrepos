#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "User.h"
#include "Category.h"
#include "TestResult.h"

using namespace std;

class TestSystem
{
private:
    vector<Guest> users;
    vector<Category> categories;
    vector<TestResult> results;

    Admin* admin;
    string currentLogin;

    string usersFile;
    string adminFile;
    string testsFile;
    string resultsFile;
    string progressFile;

    void loadUsers();
    void saveUsers();

    void loadAdmin();
    void saveAdmin();

    void loadTests();
    void saveTests();

    void loadResults();
    void saveResults();

    void mainMenu();

    void registration();
    void guestLogin();
    void adminLogin();

    void guestMenu();
    void adminMenu();

    void showCategories();
    void startTest();
    void continueTest();
    void showMyResults();

    void saveProgress(string login, int categoryIndex,
        int testIndex, int questionIndex, int correctAnswers);

    bool loadProgress(string login, int& categoryIndex,
        int& testIndex, int& questionIndex, int& correctAnswers);

    void deleteProgress(string login);

    void userManagement();
    void addUser();
    void deleteUser();
    void editUser();

    void categoryManagement();
    void addCategory();
    void deleteCategory();

    void testManagement();
    void addTest();
    void editTest();
    void deleteTest();
    void addQuestion();
    void editQuestion();
    void deleteQuestion();

    void showStatistics();
    void showCategoryStatistics();
    void showTestStatistics();
    void showUserStatistics();
    void exportStatistics();

    void changeAdminData();

    void exportTests();
    void importTests();

    int findUser(string login);
    int findCategory(string name);

public:
    TestSystem();
    ~TestSystem();

    void run();
};