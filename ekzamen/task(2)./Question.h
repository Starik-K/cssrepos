#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Question
{
private:
    string text;
    vector<string> answers;
    int correctAnswer;

public:
    Question();
    Question(string text, vector<string> answers, int correctAnswer);

    string getText() const;
    vector<string> getAnswers() const;
    int getCorrectAnswer() const;

    void setText(string text);
    void setAnswers(vector<string> answers);
    void setCorrectAnswer(int correctAnswer);

    bool checkAnswer(int answer) const;
};