#include "TestResult.h"
#include <iomanip>

TestResult::TestResult()
{
    userLogin = "";
    categoryName = "";
    testName = "";
    totalQuestions = 0;
    correctAnswers = 0;
    percentage = 0;
    grade = 0;
}

TestResult::TestResult(string userLogin, string categoryName,
    string testName, int totalQuestions, int correctAnswers)
{
    this->userLogin = userLogin;
    this->categoryName = categoryName;
    this->testName = testName;
    this->totalQuestions = totalQuestions;
    this->correctAnswers = correctAnswers;
    calculateResult();
}

string TestResult::getUserLogin() const { return userLogin; }
string TestResult::getCategoryName() const { return categoryName; }
string TestResult::getTestName() const { return testName; }

int TestResult::getTotalQuestions() const { return totalQuestions; }
int TestResult::getCorrectAnswers() const { return correctAnswers; }
double TestResult::getPercentage() const { return percentage; }
int TestResult::getGrade() const { return grade; }

void TestResult::calculateResult()
{
    if (totalQuestions <= 0)
    {
        percentage = 0;
        grade = 0;
        return;
    }

    percentage = (double)correctAnswers / totalQuestions * 100;
    grade = (int)(percentage * 12 / 100 + 0.5);

    if (grade > 12)
        grade = 12;

    if (grade < 0)
        grade = 0;
}

void TestResult::showResult() const
{
    cout << "\n===== РЕЗУЛЬТАТ ТЕСТУ =====" << endl;
    cout << "Категорія: " << categoryName << endl;
    cout << "Тест: " << testName << endl;
    cout << "Кількість питань: " << totalQuestions << endl;
    cout << "Правильних відповідей: " << correctAnswers << endl;
    cout << "Відсоток: " << fixed << setprecision(2)
        << percentage << "%" << endl;
    cout << "Оцінка: " << grade << " / 12" << endl;
}