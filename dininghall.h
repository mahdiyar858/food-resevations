#ifndef DININGHAL_H 
#define DININGHAL_H
#include <string>

class diningHall
{
    private:
    int hall_id;
    std::string name;
    std::string address;
    int capacity;
    public:
    diningHall();
    diningHall(int ,const std::string &,const std::string & , int);
    void set_hall_id(int);
    void set_name(const std::string &);
    void set_address(const std::string &);
    void set_capacity(int);
    int get_id()const;
    std::string get_name()const;
    std::string get_address()const;
    int get_capacity()const;
    void print()const;
};


#endif