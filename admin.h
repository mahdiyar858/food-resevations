#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
public:
    Admin(int id = 0, const std::string& n = "", const std::string& ln = "", 
          const std::string& pwd = "");
    
    void print() const override;
    std::string getType() const override;
};

#endif