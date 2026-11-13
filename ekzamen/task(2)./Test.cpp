#include "Test.h"

Test::Test()
{
    name = "";
}

Test::Test(string name)
{
    this->name = name;
}

string Test::getName() const
{
    return name;
}

vector<Question> Test::getQuestions() const
{
    return questions;
}

void Test::setName(string name)
{
    this->name = name;
}

void Test::addQuestion(Question question)
{
    questions.push_back(question);
}

void Test::removeQuestion(int index)
{
    if (index >= 0 && index < questions.size())
    {
        questions.erase(questions.begin() + index);
    }
}

void Test::editQuestion(int index, Question question)
{
    if (index >= 0 && index < questions.size())
    {
        questions[index] = question;
    }
}

int Test::getQuestionsCount() const
{
    return questions.size();
}

Question Test::getQuestion(int index) const
{
    if (index >= 0 && index < questions.size())
    {
        return questions[index];
    }

    return Question();
}