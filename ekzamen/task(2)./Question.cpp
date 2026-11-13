#include "Question.h"

Question::Question()
{
    text = "";
    correctAnswer = 0;
}

Question::Question(string text, vector<string> answers, int correctAnswer)
{
    this->text = text;
    this->answers = answers;
    this->correctAnswer = correctAnswer;
}

string Question::getText() const
{
    return text;
}

vector<string> Question::getAnswers() const
{
    return answers;
}

int Question::getCorrectAnswer() const
{
    return correctAnswer;
}

void Question::setText(string text)
{
    this->text = text;
}

void Question::setAnswers(vector<string> answers)
{
    this->answers = answers;
}

void Question::setCorrectAnswer(int correctAnswer)
{
    this->correctAnswer = correctAnswer;
}

bool Question::checkAnswer(int answer) const
{
    return answer == correctAnswer;
}