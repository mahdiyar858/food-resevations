#include <meal.h>
#include <iostream>
#include <vector>
#include <stdexcept>

meal::meal()
{
    meal_id = 0;
    name = "food";
    price = 0.0;
    meal_type = unknown;
    side_items = {"dough" , "salad"};
}

meal::meal(int id , const std::string &n , float p , typo t , const std::vector<std::string> &s_i )
{
    set_meal_id(id);
    set_name(n);
    set_price(p);
    set_meal_type(t);
    set_side_items(s_i);
}

void meal::update_price(float p)
{
    set_price(p);
    price = p ;
}

void meal::add_side_items(const std::string &s)
{
    side_items.push_back(s);
}

void meal::set_meal_id(int id)
{
    if(id<0)
    {
        id = 0;
    }

    meal_id =id;
}

void meal::set_name(const std::string &n)
{
    name = n;
}

void meal::set_meal_type(typo t)
{
    if (t < typo::lunch || t > typo::unknown)
    {
        t = typo::unknown;
    }
    meal_type = t;
}

void meal::set_price(float p)
{
    if (p<0)
    {
        p =15;
    }
    price = p;
}

void meal::set_side_items(const std::vector<std::string> &s)
{
    side_items = s;
}

int meal::get_meal_id()const
{
    return meal_id;
}

float meal::get_price()const
{
    return price;
}

std::string meal::get_name()const
{
    return name;
}

typo meal::get_meal_type()const 
{
    return meal_type;
}

std::vector<std::string> meal::get_side_items()const
{
    return side_items;
}
