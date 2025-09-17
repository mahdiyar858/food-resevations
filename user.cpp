#include "user.h"
#include <iostream>

User::User(int id, const std::string &n, const std::string &ln, const std::string &pwd)
    : userID(id), name(n), lastName(ln), hashedPassword(pwd) {}

void User::print() const
{
    std::cout << "User ID: " << userID << std::endl;
    std::cout << "Name: " << name << " " << lastName << std::endl;
}

std::string User::getType() const
{
    return "User";
}

int User::getUserID() const
{
    return userID;
}
void User::setUserID(int id)
{
    userID = id;
}
std::string User::getName() const
{
    return name;
}
void User::setName(const std::string &n)
{
    name = n;
}
std::string User::getLastName() const
{
    return lastName;
}
void User::setLastName(const std::string &ln)
{
    lastName = ln;
}
std::string User::getHashedPassword() const
{
    return hashedPassword;
}
void User::setHashedPassword(const std::string &pwd)
{
    hashedPassword = pwd;
}