#pragma once
#include <string>
using namespace std;

class Crypto
{
public:
    static string hashLogin(string login);
    static string generateSalt();
    static string hashPassword(string password, string salt);
};