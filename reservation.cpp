#include "reservation.h"
#include "diningHall.h"
#include "meal.h"
#include <stdexcept>
#include <limits>
#include <iostream>
#include <ctime>

reservation::reservation()
{
    reservation_ID = 000000; // first 0 for hall , second for day , third for meal type
    // forth and fifth for food name and the last one is for sidedish
    condition = status::FAILED;
    created_at = time(nullptr);
}

reservation::reservation(int day, diningHall *h, meal *m, status c, time_t t)
{
    set_reservation_ID(day, status::SUCCESS);
    set_reservation_hall(h);
    set_reservation_meal(m);
    set_reservation_condition(c);
    set_reservation_created_at(t);
}

int reservation::get_reservation_ID() const
{
    return reservation_ID;
}

diningHall reservation::get_reservation_hall() const
{
    return *hall;
}

meal reservation::get_reservation_meal() const
{
    return *Meal;
}

status reservation::get_reservation_condition() const
{
    return condition;
}

time_t reservation::get_reservation_created_at() const
{
    return created_at;
}

void reservation::set_reservation_ID(int day, const status &a)
{

    if (a == status::SUCCESS)
    {
        int ID = hall->get_hall_id() * 100000 +
                 day * 10000 + Meal->get_meal_id();

        reservation_ID = ID;
    }
    else
    {
        reservation_ID = 000000;
    }
}

void reservation::set_reservation_hall(diningHall *h)
{
    hall = h;
}

void reservation::set_reservation_meal(meal *m)
{
    Meal = m;
}

void reservation::set_reservation_condition(const status c)
{
    if (Meal->get_meal_type() == typo::unknown)
    {
        condition = status::FAILED;
    }
    else
    {
        condition = c;
    }
}

void reservation::set_reservation_created_at(const time_t &t)
{
    created_at = t;
}

int day_to_number(const std::string &day)
{
    if (day == "Saturday")
    {
        return 0;
    }
    else if (day == "Sunday")
    {
        return 1;
    }
    else if (day == "Monday")
    {
        return 2;
    }
    else if (day == "Tuesday")
    {
        return 3;
    }
    else if (day == "Wednesday")
    {
        return 4;
    }
    else if (day == "Thursday")
    {
        return 5;
    }
    else if (day == "Friday")
    {
        return 6;
    }
    else
    {
        throw std::invalid_argument("\nSir you can not invent a new calender for your self the day with the first letter in capital\n");
    }
}

void reservation::reservation_input()
{
    while (true)
    {
        Meal->meal_input();
        hall->hall_input();
        set_reservation_condition(status::SUCCESS);
        std::string day;
        std::cout << "\nfor which day you want to reserve enter the day name!\n";
        std::cin >> day;
        try
        {
            set_reservation_ID(day_to_number(day), status::SUCCESS);
            std::cout << "\nthe reservaiton ID is" << get_reservation_ID();
            break;
        }
        catch (const std::exception &e)
        {
            hall->canceling_capacity(hall->get_hall_file());
            std::cerr << e.what() << '\n';
        }

        std::cout << "\nresrevation is a complete disaster try again the status is " << get_reservation_condition();

        std::string ans;
        std::cout << "\nif you want to add another reservatoin press yes\n";
        std::cin >> ans;
        if (ans != "yes")
        {
            break;
        }
    }
}

void reservation::reservation_print()
{
    Meal->meal_print();
    hall->hall_print();
    std::cout << "\nreservation ID " << get_reservation_ID();
    std::cout << "\nreservation condition " << get_reservation_condition();
    std::cout << "\nreservation created at " << get_reservation_created_at();
}

void reservation::reservation_cancel()
{
    set_reservation_condition(status::CANCELED);
    std::cout << "\nthe reservation canceled successfully\n";
    set_reservation_ID(0, status ::CANCELED);
}