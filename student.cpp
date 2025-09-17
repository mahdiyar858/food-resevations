#include "student.h"
#include "reservation.h"
#include <iostream>
#include <string>
#include <memory>
#include <regex>
#include <cctype>
#include <stdexcept>
#include <limits>
#include <vector>

bool isAlphaOnly(const std::string &str)
{
    std::regex pattern("^[a-zA-Z]+$");
    return std::regex_match(str, pattern);
}

Student::Student(int u_id, const std::string& s_id, const std::string& n,
                 const std::string& f, const std::string& e, float b, 
                 const std::string& phone, bool active)
    : User(u_id, n, f, ""), studentID(s_id), email(e), phone(phone), 
      balance(b), isActive(active) {}

// New methods for Phase 2
bool Student::getIsActive() const
{
    return isActive;
}

void Student::activate()
{
    isActive = true;
    std::cout << "\nStudent account activated successfully!\n";
}

void Student::deactivate()
{
    isActive = false;
    std::cout << "\nStudent account deactivated successfully!\n";
}

void Student::reserveMeal()
{
    if (!isActive)
    {
        std::cout << "\nCannot reserve meal. Student account is deactivated.\n";
        return;
    }
    
    add_Reservation();
}

void Student::cancelReservation(int reservationID)
{
    for (auto it = reserves.begin(); it != reserves.end(); ++it)
    {
        if ((*it)->get_reservation_ID() == reservationID)
        {
            (*it)->reservation_cancel();
            reserves.erase(it);
            std::cout << "\nReservation " << reservationID << " canceled successfully!\n";
            return;
        }
    }
    std::cout << "\nReservation " << reservationID << " not found!\n";
}

// Getters and setters
std::string Student::getStudentID() const { return studentID; }
void Student::setStudentID(const std::string& id) { studentID = id; }

std::string Student::getEmail() const { return email; }
void Student::setEmail(const std::string& e) { email = e; }

std::string Student::getPhone() const { return phone; }
void Student::setPhone(const std::string& p) { phone = p; }

float Student::getBalance() const { return balance; }
void Student::setBalance(float b) { balance = b; }

bool Student::getIsActive() const { return isActive; }
void Student::setIsActive(bool active) { isActive = active; }

std::vector<std::unique_ptr<Reservation>>& Student::getReserves() { return reserves; }

std::string Student::getType() const
{
    return "Student";
}

#include "student.h"
#include "reservation.h"
#include <iostream>
#include <limits>
#include <stdexcept>

// ----------------- Student Input -----------------
void Student::student_input()
{
    auto getInt = [](const std::string &prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter numbers only.\n";
            }
        }
    };

    auto getFloat = [](const std::string &prompt) {
        float value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid number.\n";
            }
        }
    };

    auto getString = [](const std::string &prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    };

    // --- Gather inputs ---
    int uid = getInt("\nEnter the user ID: ");
    std::string sid = getString("\nEnter the student ID: ");
    std::string name = getString("\nEnter the student name: ");
    std::string family = getString("\nEnter the student family name: ");
    std::string mail = getString("\nEnter the student email: ");

    // Phone with validation
    std::string ph;
    while (true) {
        ph = getString("\nEnter the student phone number (10–15 digits): ");
        if (ph.length() >= 10 && ph.length() <= 15) {
            break;
        } else {
            std::cout << "Phone number must be between 10–15 characters.\n";
        }
    }

    float bal = getFloat("\nEnter the student balance: ");

    // Active status
    bool active;
    while (true) {
        std::string activeStr = getString("\nIs the student active? (true/false): ");
        if (activeStr == "true" || activeStr == "True" || activeStr == "1") {
            active = true;
            break;
        } else if (activeStr == "false" || activeStr == "False" || activeStr == "0") {
            active = false;
            break;
        } else {
            std::cout << "Please enter 'true' or 'false'.\n";
        }
    }

    // Now assign values using setters
    setUserID(uid);
    setStudentID(sid);
    setName(name);
    setLastName(family);
    setEmail(mail);
    setPhone(ph);
    setBalance(bal);
    setIsActive(active);

    // Reservations
    while (true) {
        std::string answer = getString("\nWould you like to add a reservation? (yes/no): ");
        if (answer == "yes" || answer == "Yes") {
            add_Reservation();
        } else {
            break;
        }
    }
}

void Student::print() const
{
    std::cout << std::endl
              << "Student Type: " << getType()
              << "\nUser ID: " << getUserID()
              << "\nStudent ID: " << studentID
              << "\nName: " << getName() << " " << getLastName()
              << "\nEmail: " << email
              << "\nPhone: " << phone
              << "\nBalance: $" << balance
              << "\nStatus: " << (isActive ? "Active" : "Inactive")
              << "\nNumber of reservations: " << reserves.size()
              << std::endl;
              
    if (reserves.empty())
    {
        std::cout << "No reservations found!\n";
    }
    else
    {
        std::cout << "\nReservations:\n";
        for (auto &res : reserves)
        {
            std::cout << "------------------------\n";
            res->print();
            std::cout << std::endl;
        }
    }
}