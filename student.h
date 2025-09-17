#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include <vector>
#include <string>
#include <memory>

class Reservation;

class Student : public User {
private:
    std::string studentID;
    std::string email;
    std::string phone;
    float balance;
    bool isActive;
    std::vector<std::unique_ptr<Reservation>> reserves;

public:
    Student(int u_id = 0, const std::string& s_id = "", const std::string& n = "",
            const std::string& f = "", const std::string& e = "", 
            float b = 0.0f, const std::string& phone = "", bool active = true);
    
    void student_input();
    void print() const override;
    void add_Reservation();
    
    // New methods for Phase 2
    bool getIsActive() const;
    void activate();
    void deactivate();
    void reserveMeal();
    void cancelReservation(int reservationID);
    
    // Getters and setters
    std::string getStudentID() const;
    void setStudentID(const std::string& id);
    std::string getEmail() const;
    void setEmail(const std::string& e);
    std::string getPhone() const;
    void setPhone(const std::string& p);
    float getBalance() const;
    void setBalance(float b);
    void setIsActive(bool active);
    std::vector<std::unique_ptr<Reservation>>& getReserves();
    
    std::string getType() const override;
};

#endif