#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    int userID;
    std::string name;
    std::string lastName;
    std::string hashedPassword;

public:
    User(int id = 0, const std::string& n = "", const std::string& ln = "", 
         const std::string& pwd = "");
    virtual ~User() = default;
    
    virtual void print() const;
    virtual std::string getType() const;
    
    // Getters and setters
    int getUserID() const;
    void setUserID(int id);
    std::string getName() const;
    void setName(const std::string& n);
    std::string getLastName() const;
    void setLastName(const std::string& ln);
    std::string getHashedPassword() const;
    void setHashedPassword(const std::string& pwd);
};

#endif