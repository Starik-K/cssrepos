
#include "TestSystem.h"
#include "Crypto.h"

#include <fstream>
#include <iomanip>
#include <limits>

TestSystem::TestSystem()
{
    admin = nullptr;

    usersFile = "users.txt";
    adminFile = "admin.txt";
    testsFile = "tests.txt";
    resultsFile = "results.txt";
    progressFile = "progress.txt";

    loadUsers();
    loadAdmin();
    loadTests();
    loadResults();
}

TestSystem::~TestSystem()
{
    saveUsers();
    saveAdmin();
    saveTests();
    saveResults();

    delete admin;
}

void TestSystem::run()
{
    mainMenu();
}

void TestSystem::mainMenu()
{
    int choice;

    do
    {
        cout << "\n===== СИСТЕМА ТЕСТУВАННЯ =====" << endl;
        cout << "1. Реєстрація" << endl;
        cout << "2. Вхід тестованого" << endl;
        cout << "3. Вхід адміністратора" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registration();
            break;
        case 2:
            guestLogin();
            break;
        case 3:
            adminLogin();
            break;
        case 0:
            cout << "Завершення роботи." << endl;
            break;
        default:
            cout << "Неправильний вибір!" << endl;
        }

    } while (choice != 0);
}

void TestSystem::loadUsers()
{
    ifstream file(usersFile);

    if (!file.is_open())
        return;

    string name, address, phone;
    string login, salt, password;

    while (getline(file, name))
    {
        getline(file, address);
        getline(file, phone);
        getline(file, login);
        getline(file, salt);
        getline(file, password);

        if (!file.fail())
        {
            users.push_back(Guest(
                name, address, phone, login, salt, password
            ));
        }
    }

    file.close();
}

void TestSystem::saveUsers()
{
    ofstream file(usersFile);

    for (int i = 0; i < users.size(); i++)
    {
        file << users[i].getName() << endl;
        file << users[i].getAddress() << endl;
        file << users[i].getPhone() << endl;
        file << users[i].getLoginHash() << endl;
        file << users[i].getPasswordSalt() << endl;
        file << users[i].getPasswordHash() << endl;
    }

    file.close();
}

void TestSystem::loadAdmin()
{
    ifstream file(adminFile);

    string login, salt, password;

    if (file.is_open())
    {
        getline(file, login);
        getline(file, salt);
        getline(file, password);
        file.close();
    }
    else
    {
        cout << "\n===== СТВОРЕННЯ АДМІНІСТРАТОРА =====" << endl;

        string newLogin, newPassword;

        cout << "Створіть логін: ";
        cin >> newLogin;

        cout << "Створіть пароль: ";
        cin >> newPassword;

        login = Crypto::hashLogin(newLogin);
        salt = Crypto::generateSalt();
        password = Crypto::hashPassword(newPassword, salt);
    }

    delete admin;
    admin = new Admin(login, salt, password);

    saveAdmin();
}

void TestSystem::saveAdmin()
{
    if (admin == nullptr)
        return;

    ofstream file(adminFile);

    file << admin->getLoginHash() << endl;
    file << admin->getPasswordSalt() << endl;
    file << admin->getPasswordHash() << endl;

    file.close();
}

void TestSystem::loadTests()
{
    ifstream file(testsFile);

    if (!file.is_open())
        return;

    int categoryCount;
    file >> categoryCount;

    for (int i = 0; i < categoryCount; i++)
    {
        string categoryName;
        int testCount;

        file >> quoted(categoryName);
        file >> testCount;

        Category category(categoryName);

        for (int j = 0; j < testCount; j++)
        {
            string testName;
            int questionCount;

            file >> quoted(testName);
            file >> questionCount;

            Test test(testName);

            for (int k = 0; k < questionCount; k++)
            {
                string questionText;
                int answerCount;
                int correctAnswer;

                file >> quoted(questionText);
                file >> answerCount;

                vector<string> answers;

                for (int a = 0; a < answerCount; a++)
                {
                    string answer;
                    file >> quoted(answer);
                    answers.push_back(answer);
                }

                file >> correctAnswer;

                test.addQuestion(
                    Question(questionText, answers, correctAnswer)
                );
            }

            category.addTest(test);
        }

        categories.push_back(category);
    }

    file.close();
}

void TestSystem::saveTests()
{
    ofstream file(testsFile);

    file << categories.size() << endl;

    for (int i = 0; i < categories.size(); i++)
    {
        file << quoted(categories[i].getName()) << endl;

        vector<Test> tests = categories[i].getTests();

        file << tests.size() << endl;

        for (int j = 0; j < tests.size(); j++)
        {
            file << quoted(tests[j].getName()) << endl;

            vector<Question> questions = tests[j].getQuestions();

            file << questions.size() << endl;

            for (int k = 0; k < questions.size(); k++)
            {
                file << quoted(questions[k].getText()) << endl;

                vector<string> answers = questions[k].getAnswers();

                file << answers.size() << endl;

                for (int a = 0; a < answers.size(); a++)
                    file << quoted(answers[a]) << endl;

                file << questions[k].getCorrectAnswer() << endl;
            }
        }
    }

    file.close();
}

void TestSystem::loadResults()
{
    ifstream file(resultsFile);

    if (!file.is_open())
        return;

    string login, category, test;
    int total, correct;

    while (file >> quoted(login)
        >> quoted(category)
        >> quoted(test)
        >> total >> correct)
    {
        results.push_back(
            TestResult(login, category, test, total, correct)
        );
    }

    file.close();
}

void TestSystem::saveResults()
{
    ofstream file(resultsFile);

    for (int i = 0; i < results.size(); i++)
    {
        file << quoted(results[i].getUserLogin()) << " "
            << quoted(results[i].getCategoryName()) << " "
            << quoted(results[i].getTestName()) << " "
            << results[i].getTotalQuestions() << " "
            << results[i].getCorrectAnswers() << endl;
    }

    file.close();
}

int TestSystem::findUser(string login)
{
    string hash = Crypto::hashLogin(login);

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getLoginHash() == hash)
            return i;
    }

    return -1;
}

int TestSystem::findCategory(string name)
{
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].getName() == name)
            return i;
    }

    return -1;
}

void TestSystem::registration()
{
    string name, address, phone, login, password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n===== РЕЄСТРАЦІЯ =====" << endl;

    cout << "ПІБ: ";
    getline(cin, name);

    cout << "Домашня адреса: ";
    getline(cin, address);

    cout << "Телефон: ";
    getline(cin, phone);

    cout << "Логін: ";
    getline(cin, login);

    if (name.empty() || address.empty() || phone.empty() || login.empty())
    {
        cout << "\nПомилка: заповніть усі поля!" << endl;
        cout << "Статус реєстрації: НЕ ЗАРЕЄСТРОВАНІ" << endl;
        return;
    }

    if (findUser(login) != -1)
    {
        cout << "\nПомилка: такий логін уже існує!" << endl;
        cout << "Статус реєстрації: НЕ ЗАРЕЄСТРОВАНІ" << endl;
        return;
    }

    cout << "Пароль (мінімум 8 символів): ";
    getline(cin, password);

    if (password.length() < 8)
    {
        cout << "\nПомилка: пароль повинен містити мінімум 8 символів!" << endl;
        cout << "Статус реєстрації: НЕ ЗАРЕЄСТРОВАНІ" << endl;
        return;
    }

    string salt = Crypto::generateSalt();

    users.push_back(Guest(
        name,
        address,
        phone,
        Crypto::hashLogin(login),
        salt,
        Crypto::hashPassword(password, salt)
    ));

    saveUsers();

    cout << "\n====================================" << endl;
    cout << "Ви успішно зареєструвалися!" << endl;
    cout << "Статус реєстрації: ЗАРЕЄСТРОВАНІ" << endl;
    cout << "====================================" << endl;
}

void TestSystem::guestLogin()
{
    string login, password;

    cout << "\nЛогін: ";
    cin >> login;

    cout << "Пароль: ";
    cin >> password;

    int index = findUser(login);

    if (index == -1 || !users[index].checkPassword(password))
    {
        cout << "Неправильний логін або пароль!" << endl;
        return;
    }

    currentLogin = login;
    guestMenu();
}

void TestSystem::adminLogin()
{
    string login, password;

    cout << "\nЛогін адміністратора: ";
    cin >> login;

    cout << "Пароль: ";
    cin >> password;

    if (admin == nullptr ||
        !admin->checkLogin(login) ||
        !admin->checkPassword(password))
    {
        cout << "Неправильний логін або пароль!" << endl;
        return;
    }

    adminMenu();
}

void TestSystem::guestMenu()
{
    int choice;

    do
    {
        cout << "\n===== МЕНЮ ТЕСТОВАНОГО =====" << endl;
        cout << "1. Переглянути категорії" << endl;
        cout << "2. Пройти тест" << endl;
        cout << "3. Мої результати" << endl;
        cout << "4. Продовжити тестування" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            showCategories();
            break;
        case 2:
            startTest();
            break;
        case 3:
            showMyResults();
            break;
        case 4:
            continueTest();
            break;
        case 0:
            break;
        default:
            cout << "Неправильний вибір!" << endl;
        }

    } while (choice != 0);
}

void TestSystem::adminMenu()
{
    int choice;

    do
    {
        cout << "\n===== МЕНЮ АДМІНІСТРАТОРА =====" << endl;
        cout << "1. Управління користувачами" << endl;
        cout << "2. Управління категоріями" << endl;
        cout << "3. Управління тестами" << endl;
        cout << "4. Статистика" << endl;
        cout << "5. Змінити логін і пароль" << endl;
        cout << "6. Експорт тестів" << endl;
        cout << "7. Імпорт тестів" << endl;
        cout << "8. Експорт статистики" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            userManagement();
            break;
        case 2:
            categoryManagement();
            break;
        case 3:
            testManagement();
            break;
        case 4:
            showStatistics();
            break;
        case 5:
            changeAdminData();
            break;
        case 6:
            exportTests();
            break;
        case 7:
            importTests();
            break;
        case 8:
            exportStatistics();
            break;
        case 0:
            break;
        default:
            cout << "Неправильний вибір!" << endl;
        }

    } while (choice != 0);
}

void TestSystem::showCategories()
{
    cout << "\n===== КАТЕГОРІЇ =====" << endl;

    if (categories.empty())
    {
        cout << "Категорій поки немає." << endl;
        return;
    }

    for (int i = 0; i < categories.size(); i++)
    {
        cout << i + 1 << ". " << categories[i].getName() << endl;

        vector<Test> tests = categories[i].getTests();

        for (int j = 0; j < tests.size(); j++)
            cout << "   " << j + 1 << ". " << tests[j].getName() << endl;
    }
}

void TestSystem::startTest()
{
    if (categories.empty())
    {
        cout << "Тестів поки немає." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;

    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
    {
        cout << "Неправильна категорія!" << endl;
        return;
    }

    vector<Test> tests = categories[categoryIndex].getTests();

    if (tests.empty())
    {
        cout << "У цій категорії немає тестів." << endl;
        return;
    }

    cout << "\nТести:" << endl;

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;

    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
    {
        cout << "Неправильний тест!" << endl;
        return;
    }

    if (tests[testIndex].getQuestionsCount() == 0)
    {
        cout << "У тесті немає питань." << endl;
        return;
    }

    int questionIndex = 0;
    int correctAnswers = 0;

    vector<Question> questions = tests[testIndex].getQuestions();

    for (int i = 0; i < questions.size(); i++)
    {
        cout << "\nПитання " << i + 1 << ": "
            << questions[i].getText() << endl;

        vector<string> answers = questions[i].getAnswers();

        for (int j = 0; j < answers.size(); j++)
            cout << j + 1 << ". " << answers[j] << endl;

        cout << "0. Зберегти прогрес і вийти" << endl;

        int answer;
        cout << "Ваша відповідь: ";
        cin >> answer;

        if (answer == 0)
        {
            saveProgress(currentLogin, categoryIndex,
                testIndex, i, correctAnswers);

            cout << "Прогрес збережено." << endl;
            return;
        }

        if (answer - 1 == questions[i].getCorrectAnswer())
            correctAnswers++;
    }

    TestResult result(
        currentLogin,
        categories[categoryIndex].getName(),
        tests[testIndex].getName(),
        questions.size(),
        correctAnswers
    );

    result.showResult();

    results.push_back(result);
    saveResults();
    deleteProgress(currentLogin);
}

void TestSystem::continueTest()
{
    int categoryIndex, testIndex, questionIndex, correctAnswers;

    if (!loadProgress(currentLogin, categoryIndex,
        testIndex, questionIndex, correctAnswers))
    {
        cout << "Збереженого тестування немає." << endl;
        return;
    }

    if (categoryIndex < 0 || categoryIndex >= categories.size())
        return;

    vector<Test> tests = categories[categoryIndex].getTests();

    if (testIndex < 0 || testIndex >= tests.size())
        return;

    vector<Question> questions = tests[testIndex].getQuestions();

    for (int i = questionIndex; i < questions.size(); i++)
    {
        cout << "\nПитання " << i + 1 << ": "
            << questions[i].getText() << endl;

        vector<string> answers = questions[i].getAnswers();

        for (int j = 0; j < answers.size(); j++)
            cout << j + 1 << ". " << answers[j] << endl;

        cout << "0. Зберегти і вийти" << endl;

        int answer;
        cout << "Ваша відповідь: ";
        cin >> answer;

        if (answer == 0)
        {
            saveProgress(currentLogin, categoryIndex,
                testIndex, i, correctAnswers);

            cout << "Прогрес збережено." << endl;
            return;
        }

        if (answer - 1 == questions[i].getCorrectAnswer())
            correctAnswers++;
    }

    TestResult result(
        currentLogin,
        categories[categoryIndex].getName(),
        tests[testIndex].getName(),
        questions.size(),
        correctAnswers
    );

    result.showResult();

    results.push_back(result);
    saveResults();
    deleteProgress(currentLogin);
}

void TestSystem::saveProgress(string login, int categoryIndex,
    int testIndex, int questionIndex, int correctAnswers)
{
    ofstream file(progressFile);

    file << quoted(login) << " "
        << categoryIndex << " "
        << testIndex << " "
        << questionIndex << " "
        << correctAnswers << endl;

    file.close();
}

bool TestSystem::loadProgress(string login, int& categoryIndex,
    int& testIndex, int& questionIndex, int& correctAnswers)
{
    ifstream file(progressFile);

    if (!file.is_open())
        return false;

    string savedLogin;

    file >> quoted(savedLogin)
        >> categoryIndex
        >> testIndex
        >> questionIndex
        >> correctAnswers;

    file.close();

    return savedLogin == login;
}

void TestSystem::deleteProgress(string login)
{
    ifstream file(progressFile);

    if (!file.is_open())
        return;

    string savedLogin;
    file >> quoted(savedLogin);

    file.close();

    if (savedLogin == login)
    {
        ofstream clearFile(progressFile);
        clearFile.close();
    }
}

void TestSystem::showMyResults()
{
    bool found = false;

    cout << "\n===== МОЇ РЕЗУЛЬТАТИ =====" << endl;

    for (int i = 0; i < results.size(); i++)
    {
        if (results[i].getUserLogin() == currentLogin)
        {
            results[i].showResult();
            found = true;
        }
    }

    if (!found)
        cout << "Результатів поки немає." << endl;
}

void TestSystem::userManagement()
{
    int choice;

    do
    {
        cout << "\n===== КОРИСТУВАЧІ =====" << endl;
        cout << "1. Додати користувача" << endl;
        cout << "2. Видалити користувача" << endl;
        cout << "3. Змінити дані користувача" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addUser(); break;
        case 2: deleteUser(); break;
        case 3: editUser(); break;
        }

    } while (choice != 0);
}

void TestSystem::addUser()
{
    registration();
}

void TestSystem::deleteUser()
{
    string login;

    cout << "Логін користувача: ";
    cin >> login;

    int index = findUser(login);

    if (index == -1)
    {
        cout << "Користувача не знайдено." << endl;
        return;
    }

    users.erase(users.begin() + index);
    saveUsers();

    cout << "Користувача видалено." << endl;
}

void TestSystem::editUser()
{
    string login;

    cout << "Логін користувача: ";
    cin >> login;

    int index = findUser(login);

    if (index == -1)
    {
        cout << "Користувача не знайдено." << endl;
        return;
    }

    string name, address, phone;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Нове ПІБ: ";
    getline(cin, name);

    cout << "Нова адреса: ";
    getline(cin, address);

    cout << "Новий телефон: ";
    getline(cin, phone);

    users[index].setName(name);
    users[index].setAddress(address);
    users[index].setPhone(phone);

    saveUsers();

    cout << "Дані змінено." << endl;
}

void TestSystem::categoryManagement()
{
    int choice;

    do
    {
        cout << "\n===== КАТЕГОРІЇ =====" << endl;
        cout << "1. Додати категорію" << endl;
        cout << "2. Видалити категорію" << endl;
        cout << "3. Переглянути категорії" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addCategory(); break;
        case 2: deleteCategory(); break;
        case 3: showCategories(); break;
        }

    } while (choice != 0);
}

void TestSystem::addCategory()
{
    string name;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Назва категорії: ";
    getline(cin, name);

    if (name.empty() || findCategory(name) != -1)
    {
        cout << "Назва порожня або така категорія вже існує." << endl;
        return;
    }

    categories.push_back(Category(name));
    saveTests();

    cout << "Категорію додано." << endl;
}

void TestSystem::deleteCategory()
{
    showCategories();

    int number;

    cout << "Номер категорії: ";
    cin >> number;

    number--;

    if (number < 0 || number >= categories.size())
    {
        cout << "Неправильний номер." << endl;
        return;
    }

    categories.erase(categories.begin() + number);
    saveTests();

    cout << "Категорію видалено." << endl;
}

void TestSystem::testManagement()
{
    int choice;

    do
    {
        cout << "\n===== УПРАВЛІННЯ ТЕСТАМИ =====" << endl;
        cout << "1. Додати тест" << endl;
        cout << "2. Змінити назву тесту" << endl;
        cout << "3. Видалити тест" << endl;
        cout << "4. Додати питання" << endl;
        cout << "5. Змінити питання" << endl;
        cout << "6. Видалити питання" << endl;
        cout << "7. Додати категорію" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addTest(); break;
        case 2: editTest(); break;
        case 3: deleteTest(); break;
        case 4: addQuestion(); break;
        case 5: editQuestion(); break;
        case 6: deleteQuestion(); break;
        case 7: addCategory(); break;
        case 0: break;
        default:
            cout << "Неправильний вибір!" << endl;
        }

    } while (choice != 0);
}
void TestSystem::addTest()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію (пункт 7)." << endl;
        return;
    }

    showCategories();

    int categoryIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
    {
        cout << "Неправильний номер категорії." << endl;
        return;
    }

    string name;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Назва тесту: ";
    getline(cin, name);

    if (name.empty())
    {
        cout << "Назва тесту не може бути порожньою." << endl;
        return;
    }

    Category category = categories[categoryIndex];
    category.addTest(Test(name));
    categories[categoryIndex] = category;

    saveTests();

    cout << "Тест додано." << endl;
}
void TestSystem::editTest()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
        return;

    vector<Test> tests = categories[categoryIndex].getTests();

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;
    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
        return;

    string name;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Нова назва: ";
    getline(cin, name);

    tests[testIndex].setName(name);

    Category category = categories[categoryIndex];

    category.editTest(testIndex, tests[testIndex]);
    categories[categoryIndex] = category;

    saveTests();

    cout << "Назву змінено." << endl;
}

void TestSystem::deleteTest()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
        return;

    vector<Test> tests = categories[categoryIndex].getTests();

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;
    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
        return;

    Category category = categories[categoryIndex];
    category.removeTest(testIndex);
    categories[categoryIndex] = category;

    saveTests();

    cout << "Тест видалено." << endl;
}

void TestSystem::addQuestion()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію (пункт 7)." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
    {
        cout << "Неправильний номер категорії." << endl;
        return;
    }

    vector<Test> tests = categories[categoryIndex].getTests();

    if (tests.empty())
    {
        cout << "У цій категорії ще немає тестів. Спочатку додайте тест." << endl;
        return;
    }

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;
    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
    {
        cout << "Неправильний номер тесту." << endl;
        return;
    }

    string questionText;
    int answerCount, correctAnswer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Текст питання: ";
    getline(cin, questionText);

    if (questionText.empty())
    {
        cout << "Питання не може бути порожнім." << endl;
        return;
    }

    cout << "Кількість відповідей: ";
    cin >> answerCount;

    if (answerCount < 2 || answerCount > 10)
    {
        cout << "Кількість відповідей має бути від 2 до 10." << endl;
        return;
    }

    vector<string> answers;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < answerCount; i++)
    {
        string answer;

        cout << "Відповідь " << i + 1 << ": ";
        getline(cin, answer);

        if (answer.empty())
        {
            cout << "Відповідь не може бути порожньою." << endl;
            return;
        }

        answers.push_back(answer);
    }

    cout << "Номер правильної відповіді (1-" << answerCount << "): ";
    cin >> correctAnswer;

    if (correctAnswer < 1 || correctAnswer > answerCount)
    {
        cout << "Неправильний номер відповіді." << endl;
        return;
    }

    tests[testIndex].addQuestion(
        Question(questionText, answers, correctAnswer - 1)
    );

    Category category = categories[categoryIndex];
    category.editTest(testIndex, tests[testIndex]);
    categories[categoryIndex] = category;

    saveTests();

    cout << "Питання додано." << endl;
}
void TestSystem::editQuestion()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex, questionIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
        return;

    vector<Test> tests = categories[categoryIndex].getTests();

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;
    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
        return;

    vector<Question> questions = tests[testIndex].getQuestions();

    for (int i = 0; i < questions.size(); i++)
        cout << i + 1 << ". " << questions[i].getText() << endl;

    cout << "Номер питання: ";
    cin >> questionIndex;
    questionIndex--;

    if (questionIndex < 0 || questionIndex >= questions.size())
        return;

    string questionText;
    int answerCount, correctAnswer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Новий текст питання: ";
    getline(cin, questionText);

    cout << "Кількість відповідей: ";
    cin >> answerCount;

    if (answerCount < 2)
        return;

    vector<string> answers;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < answerCount; i++)
    {
        string answer;

        cout << "Відповідь " << i + 1 << ": ";
        getline(cin, answer);

        answers.push_back(answer);
    }

    cout << "Номер правильної відповіді: ";
    cin >> correctAnswer;

    if (correctAnswer < 1 || correctAnswer > answerCount)
        return;

    tests[testIndex].editQuestion(
        questionIndex,
        Question(questionText, answers, correctAnswer - 1)
    );

    Category category = categories[categoryIndex];
    category.editTest(testIndex, tests[testIndex]);
    categories[categoryIndex] = category;

    saveTests();

    cout << "Питання змінено." << endl;
}

void TestSystem::deleteQuestion()
{
    if (categories.empty())
    {
        cout << "Спочатку створіть категорію." << endl;
        return;
    }

    showCategories();

    int categoryIndex, testIndex, questionIndex;

    cout << "Номер категорії: ";
    cin >> categoryIndex;
    categoryIndex--;

    if (categoryIndex < 0 || categoryIndex >= categories.size())
        return;

    vector<Test> tests = categories[categoryIndex].getTests();

    for (int i = 0; i < tests.size(); i++)
        cout << i + 1 << ". " << tests[i].getName() << endl;

    cout << "Номер тесту: ";
    cin >> testIndex;
    testIndex--;

    if (testIndex < 0 || testIndex >= tests.size())
        return;

    vector<Question> questions = tests[testIndex].getQuestions();

    for (int i = 0; i < questions.size(); i++)
        cout << i + 1 << ". " << questions[i].getText() << endl;

    cout << "Номер питання: ";
    cin >> questionIndex;
    questionIndex--;

    if (questionIndex < 0 || questionIndex >= questions.size())
        return;

    tests[testIndex].removeQuestion(questionIndex);

    Category category = categories[categoryIndex];
    category.editTest(testIndex, tests[testIndex]);
    categories[categoryIndex] = category;

    saveTests();

    cout << "Питання видалено." << endl;
}

void TestSystem::showStatistics()
{
    int choice;

    do
    {
        cout << "\n===== СТАТИСТИКА =====" << endl;
        cout << "1. За категоріями" << endl;
        cout << "2. За тестами" << endl;
        cout << "3. За користувачами" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1: showCategoryStatistics(); break;
        case 2: showTestStatistics(); break;
        case 3: showUserStatistics(); break;
        }

    } while (choice != 0);
}

void TestSystem::showCategoryStatistics()
{
    for (int i = 0; i < categories.size(); i++)
    {
        int count = 0;
        double sum = 0;

        for (int j = 0; j < results.size(); j++)
        {
            if (results[j].getCategoryName() == categories[i].getName())
            {
                count++;
                sum += results[j].getPercentage();
            }
        }

        cout << categories[i].getName()
            << ": тестувань " << count;

        if (count > 0)
            cout << ", середній результат " << sum / count << "%";

        cout << endl;
    }
}

void TestSystem::showTestStatistics()
{
    for (int i = 0; i < categories.size(); i++)
    {
        vector<Test> tests = categories[i].getTests();

        for (int j = 0; j < tests.size(); j++)
        {
            int count = 0;
            double sum = 0;

            for (int k = 0; k < results.size(); k++)
            {
                if (results[k].getCategoryName() == categories[i].getName()
                    && results[k].getTestName() == tests[j].getName())
                {
                    count++;
                    sum += results[k].getPercentage();
                }
            }

            cout << tests[j].getName()
                << ": тестувань " << count;

            if (count > 0)
                cout << ", середній результат " << sum / count << "%";

            cout << endl;
        }
    }
}

void TestSystem::showUserStatistics()
{
    for (int i = 0; i < users.size(); i++)
    {
        cout << "\nКористувач: " << users[i].getName() << endl;

        for (int j = 0; j < results.size(); j++)
        {
            if (Crypto::hashLogin(results[j].getUserLogin()) == users[i].getLoginHash())
            {
                results[j].showResult();
            }
        }
    }
}

void TestSystem::exportStatistics()
{
    ofstream file("statistics.txt");

    if (!file.is_open())
    {
        cout << "Не вдалося створити файл." << endl;
        return;
    }

    for (int i = 0; i < results.size(); i++)
    {
        file << "Користувач: " << results[i].getUserLogin() << endl;
        file << "Категорія: " << results[i].getCategoryName() << endl;
        file << "Тест: " << results[i].getTestName() << endl;
        file << "Правильних відповідей: "
            << results[i].getCorrectAnswers() << endl;
        file << "Відсоток: " << results[i].getPercentage() << "%" << endl;
        file << "Оцінка: " << results[i].getGrade() << "/12" << endl;
        file << "------------------------" << endl;
    }

    file.close();

    cout << "Статистику збережено у statistics.txt" << endl;
}

void TestSystem::changeAdminData()
{
    string login, password;

    cout << "Новий логін адміністратора: ";
    cin >> login;

    cout << "Новий пароль адміністратора: ";
    cin >> password;

    string salt = Crypto::generateSalt();

    delete admin;

    admin = new Admin(
        Crypto::hashLogin(login),
        salt,
        Crypto::hashPassword(password, salt)
    );

    saveAdmin();

    cout << "Дані адміністратора змінено." << endl;
}

void TestSystem::exportTests()
{
    string fileName;

    cout << "Назва файлу для експорту: ";
    cin >> fileName;

    ofstream file(fileName);

    if (!file.is_open())
    {
        cout << "Не вдалося створити файл." << endl;
        return;
    }

    file << categories.size() << endl;

    for (int i = 0; i < categories.size(); i++)
    {
        file << quoted(categories[i].getName()) << endl;

        vector<Test> tests = categories[i].getTests();

        file << tests.size() << endl;

        for (int j = 0; j < tests.size(); j++)
        {
            file << quoted(tests[j].getName()) << endl;

            vector<Question> questions = tests[j].getQuestions();

            file << questions.size() << endl;

            for (int k = 0; k < questions.size(); k++)
            {
                file << quoted(questions[k].getText()) << endl;

                vector<string> answers = questions[k].getAnswers();

                file << answers.size() << endl;

                for (int a = 0; a < answers.size(); a++)
                    file << quoted(answers[a]) << endl;

                file << questions[k].getCorrectAnswer() << endl;
            }
        }
    }

    file.close();

    cout << "Тести експортовано." << endl;
}

void TestSystem::importTests()
{
    string fileName;

    cout << "Назва файлу для імпорту: ";
    cin >> fileName;

    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Файл не знайдено." << endl;
        return;
    }

    int categoryCount;
    file >> categoryCount;

    if (!file || categoryCount < 0)
    {
        cout << "Неправильний формат файлу." << endl;
        return;
    }

    for (int i = 0; i < categoryCount; i++)
    {
        string categoryName;
        int testCount;

        file >> quoted(categoryName) >> testCount;

        if (!file || testCount < 0)
            break;

        Category category(categoryName);

        for (int j = 0; j < testCount; j++)
        {
            string testName;
            int questionCount;

            file >> quoted(testName) >> questionCount;

            if (!file || questionCount < 0)
                break;

            Test test(testName);

            for (int k = 0; k < questionCount; k++)
            {
                string questionText;
                int answerCount, correctAnswer;

                file >> quoted(questionText) >> answerCount;

                if (!file || answerCount < 0)
                    break;

                vector<string> answers;

                for (int a = 0; a < answerCount; a++)
                {
                    string answer;
                    file >> quoted(answer);
                    answers.push_back(answer);
                }

                file >> correctAnswer;

                if (!file || correctAnswer < 0
                    || correctAnswer >= answerCount)
                    break;

                test.addQuestion(
                    Question(questionText, answers, correctAnswer)
                );
            }

            category.addTest(test);
        }

        categories.push_back(category);
    }

    file.close();
    saveTests();

    cout << "Імпорт завершено." << endl;
}
