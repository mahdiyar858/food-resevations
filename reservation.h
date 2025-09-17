#ifndef RESERVATION_H
#define RESERVATION_H

#include "diningHall.h"
#include "meal.h"
#include <ctime>

enum class RStatus
{
    FAILED = 1,
    SUCCESS = 2,
    CANCELED = 3
};

class Reservation
{
private:
    int reservationID;
    DiningHall *hall;
    Meal *meal;
    RStatus status;
    time_t createdAT;

public:
    Reservation(std::string = nullptr, DiningHall *h = nullptr, Meal *m = nullptr,
                RStatus s = RStatus::FAILED, time_t t = 0);
                
    void reservation_input();
    void print() const;
    void reservation_cancel();

    // Getters and setters
    int get_reservation_ID() const;
    DiningHall *get_reservation_hall() const;
    Meal *get_reservation_meal() const;
    RStatus get_status() const;
    time_t get_created_at() const;

    void set_reservation_ID(std::string);
    void set_reservation_hall(DiningHall *h);
    void set_reservation_meal(Meal *m);
    void set_status(RStatus s);
    void set_created_at(time_t t);
};

#endif