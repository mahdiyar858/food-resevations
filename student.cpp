#include <vector>
#include <iostream>
#include <string>
#include <memory>    //for make_unique and ...
#include <regex>     // for cheking if the name contain only letter
#include <cctype>    // Required for isdigit(), isalpha()
#include <stdexcept> // for invalid arguments
#include <limits>    // for igonor
#include <vector>
#include "student.h"
#include "reservation.h"

bool isAlphaOnly(const std::string &str)
{
    std::regex pattern("^[a-zA-Z]+$");
    return std::regex_match(str, pattern);
}

Student::Student()
{
    u_id = 0;
    s_id = "10000000";
    name = "unknown";
    f_name = "unknown";
    email = "unknown@gmail.com";
    balance = 0.0f;
    activity = false;
}

Student::Student(int id, const std::string &st_id, const std::string &n, const std::string &f, const std::string &e, float b, std::string a)
{
    set_student_user_id(id);
    set_student_id(st_id);
    set_student_name(n);
    set_student_family_name(f);
    set_student_email(e);
    set_student_balance(b);
    set_student_status(a);
}

int Student::get_student_user_id() const
{
    return u_id;
}

std::string Student::get_student_id() const
{
    return s_id;
}

std::string Student::get_student_name() const
{
    return name;
}

std::string Student::get_student_family_name() const
{
    return f_name;
}

std::string Student::get_student_email() const
{
    return email;
}

float Student::get_student_balance() const
{
    return balance;
}

bool Student::get_student_status() const
{
    return activity;
}

void Student::set_student_user_id(int id)
{
    if (id > 10000 || id < 0)
    {
        throw std::invalid_argument("\nThe user ID must be between 0 - 10000\n");
    }
    u_id = id;
}

void Student::set_student_id(const std::string &id)
{
    if (id.length() != 8)
    {
        throw std::invalid_argument("\nStudent ID must be exactly 8 digits\n");
    }
    for (int c = 0; c < 8; c++)
    {
        if (!isdigit(id[c]))
        {
            throw std::invalid_argument("\nThe student ID must contain only numbers\n ");
        }
    }

    s_id = id;
}

void Student::set_student_name(const std::string &n)
{
    if (!isAlphaOnly(n))
    {
        throw std::invalid_argument("\nThe name must contain only letters\n");
    }

    name = n;
}

void Student::set_student_family_name(const std::string &family)
{
    if (!isAlphaOnly(family))
    {
        throw std::invalid_argument("\nThe family name must contain only letters\n");
    }
    f_name = family;
}

void Student::set_student_email(const std::string &email)
{
    std::string gmail = "@gmail.com";

    if (email.length() <= 13 || email.length() > 100)
    {
        throw std::invalid_argument("\nThe email must contains at least 13 characters including @gmail.com and\n and the email charaters must be less than 100 characters\n");
    }
    if (email.compare(email.length() - 10, 10, gmail, 0, 10) == 0)
    {
        this->email = email;
    }
    else
    {
        throw std::invalid_argument("\nYou must enter the @gmail.com at the end of your email !\n");
    }
}

void Student::set_student_balance(float money)
{
    if (money < -555.0f || money > 1000000.00f)
    {
        throw std::invalid_argument("\nbalance connot be less than -555 or more than 1000000\n");
    }
    balance = money;
}

void Student::set_student_status(std::string a)
{
    if (a == "false" || a == "False")
    {
        activity = 0;
    }
    else if (a == "true" || a == "True")
    {
        activity = 1;
    }
    else
    {
        throw std::invalid_argument("\nThe activity must only be false or true or False or True!!\n");
    }
}

void Student::set_student_reservation(std::vector<reservation> reserve, int id)
{
    std::vector<int> check{};

    for (const auto &element : reserve)
    {
        check.push_back(element.get_reservation_ID());
    }

    for (const auto &element : check)
    {
        if (element == id)
        {
            std::cout << "You cannot procced because you already have an reservation for this meal";
            return;
        }
    }
}

void Student::student_input()
{
    while (true) // ID
    {
        std::cout << "\nEnter the user ID\n";
        if (std::cin >> u_id)
        {
            try
            {
                set_student_user_id(u_id);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clean all inside the cin
                break;
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "\nError\n"
                          << e.what() << std::endl;
            }
        }
        else
        {
            std::cin.clear(); // remove the failed flag but doesn't clean inside the cin!!
            std::cout << "Invalid input. Please enter numbers only.\n";
        }
    }
    while (true) // STUDENT ID
    {
        std::cout << "\nEnter the student ID\n";
        std::getline(std::cin, s_id); // read a line of text from cin and store it as a string
        try
        {
            set_student_id(s_id);
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "\nError\n"
                      << e.what() << std::endl;
        }
    }

    while (true) // STUDENT NAME
    {
        std::cout << "\nEnter the student name\n";
        std::getline(std::cin, name);
        try
        {
            set_student_name(name);
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "\nError\n"
                      << e.what() << std::endl;
        }
    }

    while (true) // STUDENT FAMILY NAME
    {
        std::cout << "\nEnter the student family\n";
        std::getline(std::cin, f_name);
        try
        {
            set_student_family_name(f_name);
            break;
        }

        catch (const std::invalid_argument &e)
        {
            std::cout << "\nError\n"
                      << e.what() << std::endl;
        }
    }

    while (true) // STUDENT EAMIAL
    {
        std::cout << "\nEnter the student email\n";
        std::getline(std::cin, email);
        try
        {
            set_student_email(email);
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "\nError\n"
                      << e.what() << std::endl;
        }
    }

    while (true) // STUDENT BALANCE
    {
        std::cout << "\nEnter the student balance\n";
        if (std::cin >> balance)
        {
            try
            {
                set_student_balance(balance);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "\nError\n"
                          << e.what() << std::endl;
            }
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter numbers only.\n";
        }
    }

    while (true) // STUDENT ACTIVITY
    {
        std::string a = {};
        std::cout << "\nIs the student still active? (false or true): ";
        std::getline(std::cin, a);
        try
        {
            set_student_status(a);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cin.clear();
            std::cout << "\nError\n"
                      << e.what() << std::endl;
        }
    }

    while (true) // inputing reservations
    {
        std::string answer;
        std::cout<<"\nwould you like to add reservation (ofcourse / ofcourse not)?";
        std::getline(std::cin , answer);
        if (answer == "ofcourse" || answer == "yes")
        {
            this->add_Reservation();
        }
        else
        {
            break;
        }
    }
}

void Student::add_Reservation()
{
    while (true)
    {
        int i = 0;
        std::string answer;
        auto res = std::make_unique<reservation>();
        std::cout << "\nEnter your reservation\n";
        res->reservation_input();
        for (auto &element : reservations)
        {
            if (element->get_reservation_ID() == res->get_reservation_ID())
            {
                i = 1;
                break;
            }
        }
        if (i == 1)
        {
            std::cout << "\nyou have a reserve for this meal\n";
            std::cout << "\nif you want to stop enter stop or any other thing to continue\n";
            std::cin >> answer;
            if (answer == "stop")
                break;
        }
        else
        {
            if(res->get_reservation_condition() == SUCCESS)
            {reservations.push_back(std::move(res));
            std::cout << "\nThe reservation was added to the list of your reserve\nnow if you want to stop enter stop or any other key to continue!\n";
            std::cin >> answer;
            if (answer == "stop")
                break;
            }
            else
            {
                std::cout<<"\nthe reservation is good\n";
            }
        }
    }
}

void Student::student_print() const
{
    std::cout << std::endl
              << "student user ID = " << get_student_user_id()
              << std::endl
              << "student ID = " << get_student_id()
              << std::endl
              << "student name = " << get_student_name()
              << std::endl
              << "student family name = " << get_student_family_name()
              << std::endl
              << "student email = " << get_student_email()
              << std::endl
              << "student balance = " << get_student_balance()
              << std::endl
              << "student status = " << get_student_status()
              << std::endl
              << "student reservations = ";
    if (reservations.empty())
    {
        std::cout << "the reservation is empty!\n";
    }
    else
    {
        for (auto &res : reservations)
        {
            std::cout << std::endl;
            res->reservation_print();
            std::cout << std::endl;
        }
    }
}