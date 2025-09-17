#include "reservation.h"
#include "diningHall.h"
#include "meal.h"
#include <stdexcept>
#include <limits>
#include <iostream>
#include <ctime>

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


Reservation::Reservation(std::string day, DiningHall *h, Meal *m, RStatus s, time_t t)
    : hall(h), meal(m), status(s), createdAT(t) { set_reservation_ID(day); }

int Reservation::get_reservation_ID() const
{
    return reservationID;
}

DiningHall *Reservation::get_reservation_hall() const
{
    return hall;
}

Meal *Reservation::get_reservation_meal() const
{
    return meal;
}

RStatus Reservation::get_status() const
{
    return status;
}

time_t Reservation::get_created_at() const
{
    return createdAT;
}

void Reservation::set_reservation_ID(std::string day)
{
                int ID = hall->get_hall_id() * 100000 +
                     day_to_number(day) * 10000 + meal->get_meal_id();
    reservationID = ID;
}

void Reservation::set_reservation_hall(DiningHall *h)
{
    hall = h;
}

void Reservation::set_reservation_meal(Meal *m)
{
    meal = m;
}

void Reservation::set_status(RStatus s)
{
    status = s;
}

void Reservation::set_created_at(time_t t)
{
    createdAT = t;
}

void Reservation::reservation_input()
{
    while (true)
    {
        meal->meal_input();
        hall->hall_input();
        set_status(RStatus::SUCCESS);
        std::string day;
        std::cout << "\nfor which day you want to reserve enter the day name!\n";
        std::cin >> day;
        try
        {
            set_reservation_ID(day);
            std::cout << "\nthe reservation ID is " << get_reservation_ID();
            break;
        }
        catch (const std::exception &e)
        {
            hall->canceling_capacity(hall->get_hall_file());
            std::cerr << e.what() << '\n';
        }

        std::cout << "\nreservation is a complete disaster try again the status is "
                  << static_cast<int>(get_status());

        std::string ans;
        std::cout << "\nif you want to add another reservation press yes\n";
        std::cin >> ans;
        if (ans != "yes")
        {
            break;
        }
    }
}

void Reservation::print() const
{
    meal->print();
    hall->hall_print();
    std::cout << "\nreservation ID " << get_reservation_ID();
    std::cout << "\nreservation condition " << static_cast<int>(get_status());
    std::cout << "\nreservation created at " << get_created_at();
}

void Reservation::reservation_cancel()
{
    set_status(RStatus::CANCELED);
    std::cout << "\nthe reservation canceled successfully\n";
    set_reservation_ID(0);
}