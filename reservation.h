#ifndef RESERVATION_H // Include guard: Prevents the header from being included multiple times
#define RESERVATION_H // in a single compilation unit, avoiding redefinition errors.

class Student;

enum status
{
    FAILED = 1,
    SUCCESS = 2,
    CANCELED = 3
};

enum class Weekday
{
    SATURDAY = 1,
    SUNDAY = 2,
    MONDAY = 3,
    TUESDAY = 4,
    WEDNESDAY = 5,
    THURSDAY = 6,
    FRIDAY = 7
};

class reservation
{
    int reservation_ID;
    diningHall *hall;
    meal *Meal;
    status condition;
    time_t created_at;

public:
    reservation();
    reservation(int ,diningHall *, meal *, status, time_t);

    void reservation_input();
    void reservation_print();
    void reservation_cancel();

    int get_reservation_ID() const;
    diningHall get_reservation_hall() const;
    meal get_reservation_meal() const;
    status get_reservation_condition() const;
    time_t get_reservation_created_at() const;

    void set_reservation_ID(int , const status &);
    void set_reservation_hall(diningHall *);
    void set_reservation_meal(meal *);
    void set_reservation_condition(const status);
    void set_reservation_created_at(const time_t &);
};

#endif