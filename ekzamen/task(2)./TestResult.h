#pragma once
#include <iostream>
#include <string>
using namespace std;

class TestResult
{
private:
    string userLogin;
    string categoryName;
    string testName;
    int totalQuestions;
    int correctAnswers;
    double percentage;
    int grade;

public:
    TestResult();

    TestResult(string userLogin, string categoryName,
        string testName, int totalQuestions, int correctAnswers);

    string getUserLogin() const;
    string getCategoryName() const;
    string getTestName() const;

    int getTotalQuestions() const;
    int getCorrectAnswers() const;
    double getPercentage() const;
    int getGrade() const;

    void calculateResult();
    void showResult() const;
};