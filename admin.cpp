#include "admin.h"
#include <iostream>

Admin::Admin(int id, const std::string &n, const std::string &ln, const std::string &pwd)
    : User(id, n, ln, pwd) {}

void Admin::print() const
{
    std::cout << "Admin ID: " << getUserID() << std::endl;
    std::cout << "Name: " << getName() << " " << getLastName() << std::endl;
}

std::string Admin::getType() const
{
    return "Admin";
}