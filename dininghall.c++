#include <diningHall.h>
#include <iostream>

diningHall::diningHall()
{
    hall_id = 1;
    name = "d1";
    address = "the last stop of the bus station";
    capacity = 500;
}

diningHall::diningHall(int id, const std::string &n, const std::string &a, int c)
{
    set_hall_id(id);
    set_name(n);
    set_address(a);
    set_capacity(c);
}

void diningHall::set_hall_id(int id)
{
    if(id > 5 || id <0)
    {
        id = 1;
    }
    hall_id = id;
}

void diningHall::set_name(const std::string &n)
{
    name = n;
}

void diningHall::set_address(const std::string &a)
{
    address = a;
}

void diningHall::set_capacity(int c)
{
    if(c>1000 || c<200)
    {
         c = 250;
    }
    capacity =c;
}

int diningHall::get_id()const
{
    return hall_id;
}

std::string diningHall::get_name()const
{
    return name;
}

std::string diningHall::get_address()const
{
    return address;
}

int diningHall::get_capacity()const
{
    return capacity;
}

void diningHall::print()const
{
    std::cout<<"\nhall ID = "<<hall_id
        <<"\nhall name = "<<name
        <<"\nhall address = "<<address
        <<"\nhall capacity = "<<capacity;

}