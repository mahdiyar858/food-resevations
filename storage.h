#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "meal.h"
#include "diningHall.h"

class Storage {
private:
    static Storage* instance;
    int mealIDCounter;
    int diningHallIDCounter;
    
    // Private constructor for singleton pattern
    Storage();
    
public:
    std::vector<Meal> allMeals;
    std::vector<DiningHall> allDiningHalls;
    
    // Delete copy constructor and assignment operator
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    
    static Storage& getInstance();
    
    int getNextMealID();
    int getNextDiningHallID();
    
    void addMeal(const Meal& meal);
    void addDiningHall(const DiningHall& hall);
};

#endif