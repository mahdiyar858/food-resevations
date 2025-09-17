#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <string>
#include <memory>
#include <vector>

class reservation;

class Student
{
    int u_id;
    std::string s_id;
    std::string name;
    std::string f_name;
    std::string email;
    float balance;
    bool activity;
    std::vector<std::unique_ptr<reservation>> reservations;

public:
    Student();
    Student(int, const std::string &, const std::string &,
            const std::string &, const std::string &, float , std::string);

    void student_input();
    void student_print() const;
    void add_Reservation();

    int get_student_user_id() const;
    std::string get_student_id()const;
    std::string get_student_name()const;
    std::string get_student_family_name()const;
    std::string get_student_email()const;
    float get_student_balance()const;
    bool get_student_status()const;

    void set_student_user_id(int);
    void set_student_id(const std::string &);
    void set_student_name(const std::string &);
    void set_student_family_name(const std::string &);
    void set_student_email(const std::string &);
    void set_student_balance(float);
    void set_student_status(std::string);
    void set_student_reservation(std::vector <reservation> , int);
    
};

#endif