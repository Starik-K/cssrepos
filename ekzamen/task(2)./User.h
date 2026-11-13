#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
protected:
    string name;
    string address;
    string phone;
    string loginHash;
    string passwordSalt;
    string passwordHash;

public:
    User();
    User(string name, string address, string phone,
        string loginHash, string passwordSalt, string passwordHash);

    virtual void showMenu();

    bool checkLogin(string login) const;
    bool checkPassword(string password) const;

    string getName() const;
    string getAddress() const;
    string getPhone() const;

    string getLoginHash() const;
    string getPasswordSalt() const;
    string getPasswordHash() const;

    void setName(string name);
    void setAddress(string address);
    void setPhone(string phone);
    void setPassword(string salt, string hash);

    virtual ~User();
};

class Guest : public User
{
public:
    Guest(string name, string address, string phone,
        string loginHash, string passwordSalt, string passwordHash);

    void showMenu() override;
};

class Admin : public User
{
public:
    Admin(string loginHash, string passwordSalt, string passwordHash);

    void showMenu() override;
};