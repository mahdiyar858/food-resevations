#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <vector>

enum class MealType {
    BREAKFAST = 1,
    LUNCH = 2,
    DINNER = 3,
    SIDE_DISH = 4,
    UNKNOWN = 5
};

enum class ReserveDay {
    SATURDAY = 1,
    SUNDAY = 2,
    MONDAY = 3,
    TUESDAY = 4,
    WEDNESDAY = 5,
    THURSDAY = 6,
    FRIDAY = 7
};

class Meal {
private:
    int mealID;
    std::string name;
    float price;
    bool isActive;
    MealType mealType;
    ReserveDay reserveDay;
    std::vector<std::string> sideItems;

    static const int maximum_food = 99;
    static const int maximum_side_dish = 9;
    static std::string breakfast_File;
    static std::string lunch_File;
    static std::string dinner_File;
    static std::string side_dish_File;
    static std::string price_File;

public:
    Meal(int id = 0, const std::string& n = "", float p = 0.0f, 
         bool active = true, MealType type = MealType::UNKNOWN, 
         ReserveDay day = ReserveDay::SATURDAY);
    
    static bool initialize_meal_file();
    static bool default_meal_price();
    static int meal_counting_meal(const std::string&);
    static void meal_adding_meal(const std::string&);
    static void deleting_meal_side(const std::string&);
    static void update_meal_price(const std::string&);
    static void adding_meal_side_items(const std::string&);

    // New methods for Phase 2
    bool getIsActive() const;
    void activate();
    void deactivate();
    MealType getMealType() const;
    ReserveDay getReserveDay() const;
    void setMealType(MealType type);
    void setReserveDay(ReserveDay day);
    void addSideItem(const std::string& item);
    void addPrice(float newPrice);

    void set_meal_id();
    void set_meal_price();
    void set_meal_name(const std::string&);
    void set_meal_type(MealType);
    void set_meal_side_item(const std::string&);

    int meal_input();
    void print() const;

    int get_meal_id() const;
    float get_meal_price() const;
    std::string get_meal_name() const;
    MealType get_meal_type() const;
    std::string get_meal_side_item() const;
    std::vector<std::string> get_side_items() const;
};

#endif