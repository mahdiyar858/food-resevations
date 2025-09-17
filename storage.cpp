#include "storage.h"

Storage *Storage::instance = nullptr;

Storage::Storage() : mealIDCounter(0), diningHallIDCounter(0) {}

Storage &Storage::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Storage();
    }
    return *instance;
}
int Storage::getNextMealID()
{
    return ++mealIDCounter;
}

int Storage::getNextDiningHallID()
{
    return ++diningHallIDCounter;
}

void Storage::addMeal(const Meal &meal)
{
    allMeals.push_back(meal);
}

void Storage::addDiningHall(const DiningHall &hall)
{
    allDiningHalls.push_back(hall);
}