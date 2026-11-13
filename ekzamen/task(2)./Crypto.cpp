#include "Crypto.h"

string Crypto::hashLogin(string login)
{
    return login;
}

string Crypto::generateSalt()
{
    return "12345";
}

string Crypto::hashPassword(string password, string salt)
{
    return salt + password;
}