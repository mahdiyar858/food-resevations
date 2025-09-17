#ifndef DININGHALL_H
#define DININGHALL_H

#include <string>

class DiningHall
{
private:
    int hall_id;
    std::string name;
    std::string address;
    int capacity;

    static const int max_capacity = 1000;
    static std::string hall_file_1;
    static std::string hall_file_2;
    static std::string hall_file_3;
    static std::string hall_file_4;
    static std::string hall_file_5;

public:
    DiningHall();
    DiningHall(const std::string &, const std::string &, const std::string &, int);

    static void initilize_hall_files();
    static int counting_hall_files(const std::string &);
    static void canceling_capacity(const std::string &);
    
    void set_hall_id_capacity_name();
    
    void set_hall_id(const std::string &);
    void set_hall_name(const std::string &);
    void set_hall_address(const std::string &);
    void set_hall_capacity(const std::string &);

    std::string get_hall_file() const;
    int get_hall_id() const;
    std::string get_hall_name() const;
    std::string get_hall_address() const;
    int get_hall_capacity() const;

    void hall_print() const;
    void hall_input();
};

#endif