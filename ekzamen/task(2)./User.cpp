#include "User.h"
#include "Crypto.h"

User::User()
{
    name = "";
    address = "";
    phone = "";
    loginHash = "";
    passwordSalt = "";
    passwordHash = "";
}

User::User(string name, string address, string phone,
    string loginHash, string passwordSalt, string passwordHash)
{
    this->name = name;
    this->address = address;
    this->phone = phone;
    this->loginHash = loginHash;
    this->passwordSalt = passwordSalt;
    this->passwordHash = passwordHash;
}

void User::showMenu()
{
    cout << "Меню користувача" << endl;
}

bool User::checkLogin(string login) const
{
    return loginHash == Crypto::hashLogin(login);
}

bool User::checkPassword(string password) const
{
    return passwordHash == Crypto::hashPassword(password, passwordSalt);
}

string User::getName() const { return name; }
string User::getAddress() const { return address; }
string User::getPhone() const { return phone; }

string User::getLoginHash() const { return loginHash; }
string User::getPasswordSalt() const { return passwordSalt; }
string User::getPasswordHash() const { return passwordHash; }

void User::setName(string name) { this->name = name; }
void User::setAddress(string address) { this->address = address; }
void User::setPhone(string phone) { this->phone = phone; }

void User::setPassword(string salt, string hash)
{
    passwordSalt = salt;
    passwordHash = hash;
}

User::~User() {}

Guest::Guest(string name, string address, string phone,
    string loginHash, string passwordSalt, string passwordHash)
    : User(name, address, phone, loginHash, passwordSalt, passwordHash)
{
}

void Guest::showMenu()
{
    cout << "\n===== МЕНЮ ТЕСТОВАНОГО =====" << endl;
    cout << "1. Переглянути категорії" << endl;
    cout << "2. Пройти тест" << endl;
    cout << "3. Мої результати" << endl;
    cout << "4. Продовжити тестування" << endl;
    cout << "0. Вийти" << endl;
}

Admin::Admin(string loginHash, string passwordSalt, string passwordHash)
    : User("Адміністратор", "", "", loginHash, passwordSalt, passwordHash)
{
}

void Admin::showMenu()
{
    cout << "\n===== МЕНЮ АДМІНІСТРАТОРА =====" << endl;
    cout << "1. Управління користувачами" << endl;
    cout << "2. Управління категоріями" << endl;
    cout << "3. Управління тестами" << endl;
    cout << "4. Перегляд статистики" << endl;
    cout << "5. Зміна логіна і пароля" << endl;
    cout << "6. Експорт та імпорт тестів" << endl;
    cout << "0. Вийти" << endl;
}