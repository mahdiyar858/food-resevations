#ifndef MEAL_H // Include guard: Prevents the header from being included multiple times
#define MEAL_H // in a single compilation unit, avoiding redefinition errors.

#include <string>
#include <vector>

enum class typo
{
    lunch = 1,
    breakfast = 2,
    dinner = 3,
    side_dish = 4,
    unknown =5
};

class meal
{
private:
    int meal_id;
    float price;
    std::string meal_name;
    typo meal_type;
    std::string side_item;

    static const int maximum_food = 99;
    static const int maximum_side_dish = 9;
    static std::string  breakfast_File;
    static std::string lunch_File;
    static std::string dinner_File;
    static std::string side_dish_File;
    static std::string price_File;

public:
    meal(int, const std::string &, typo, const std::string &);
    meal();

    static bool initialize_meal_file();
    static bool default_meal_price();
    static int meal_counting_meal(const std::string &);
    static void meal_adding_meal(const std::string &);
    static void deleting_meal_side(const std::string &);
    static void update_meal_price(const std::string &);
    static void adding_meal_side_items(const std::string &);


    void set_meal_id();
    void set_meal_price();
    void set_meal_name(const std::string &);
    void set_meal_type(typo);
    void set_meal_side_item(const std::string &);

    int meal_input();
    void meal_print() const;

    int get_meal_id() const;
    float get_meal_price() const;
    std::string get_meal_name() const;
    typo get_meal_type() const;
    std::string get_meal_side_item() const;
};

#endif // End of include guard