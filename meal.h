#ifndef MEAL_H // Include guard: Prevents the header from being included multiple times
#define MEAL_H // in a single compilation unit, avoiding redefinition errors.
#include <string>
#include <vector>

enum typo
{
    lunch = 1,
    breakfast = 2,
    dinner = 3,
    unknown = 4
};

class meal
{
private:
    int meal_id;
    std::string name;
    float price;
    typo meal_type;
    std::vector<std::string> side_items;

public:
    meal(int, const std::string &, float, typo , const std::vector<std::string> &);
    meal();
    void update_price(float);
    void add_side_items(const std::string &);
    void set_meal_id(int);
    void set_name(const std::string &);
    void set_price(float);
    void set_meal_type(typo);
    void set_side_items(const std::vector<std::string> &);
    void print()const;
    int get_meal_id()const;
    std::string get_name()const;
    float get_price()const;
    typo get_meal_type()const;
    std::vector<std::string> get_side_items()const;
};
#endif // End of include guard