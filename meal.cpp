#include "meal.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <fstream>
#include <cmath>

std::string Meal::breakfast_File = "breakfast_meals.dat";
std::string Meal::lunch_File = "lunch_meals.dat";
std::string Meal::dinner_File = "dinner_meal.dat";
std::string Meal::side_dish_File = "side_dish.dat";
std::string Meal::price_File = "price_file.dat";

Meal::Meal(int id, const std::string& n, float p, bool active, MealType type, ReserveDay day)
    : mealID(id), name(n), price(p), isActive(active), mealType(type), reserveDay(day) {}

bool Meal::initialize_meal_file()
{
    std::ofstream b_file(breakfast_File, std::ios::app);
    std::ofstream l_file(lunch_File, std::ios::app);
    std::ofstream d_file(dinner_File, std::ios::app);
    std::ofstream s_file(side_dish_File, std::ios::app);
    std::ofstream p_file(price_File, std::ios::app);

    if (!b_file.is_open() || !l_file.is_open() || !d_file.is_open() || !s_file.is_open() || !p_file.is_open())
    {
        std::cerr << "\nError creating meal files!\n";
        return false;
    }

    b_file.close();
    l_file.close();
    d_file.close();
    s_file.close();
    p_file.close();

    std::cout << "\nMeal files and price file are checked successfully!\n";
    return true;
}

bool Meal::default_meal_price()
{
    std::ofstream p_file(price_File, std::ios::out);

    if (!p_file.is_open())
    {
        std::cout << "\nCan not create the price file!\n";
        return false;
    }

    p_file << "15\n"; // Breakfast price
    p_file << "20\n"; // Lunch price
    p_file << "25\n"; // Dinner price
    p_file << "5\n";  // Side dish price

    p_file.close();
    return true;
}

int Meal::meal_counting_meal(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "\nthere is a problem with the file! (cannot open the file)\n";
        return -1;
    }

    int count = 0;
    std::string line;
    while (getline(file, line))
    {
        if (!line.empty() && line.find_first_not_of("\t\n\r") != std::string::npos)
        {
            count++;
        }
    }

    file.close();
    return count;
}

void Meal::meal_adding_meal(const std::string &filename)
{
    int meal_count = meal_counting_meal(filename);
    if (meal_count >= maximum_food || meal_count == -1)
    {
        std::cout << "\nyou cannot add more than " << maximum_food << " meals!\n";
        return;
    }

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "\nCan't open the file for writing\n";
        return;
    }

    std::vector<std::string> meals;
    std::ifstream search(filename);
    if (search.is_open())
    {
        std::string meal;
        while (search >> meal)
        {
            meals.push_back(meal);
        }
        search.close();
    }

    while (true)
    {
        if (meal_count >= maximum_food || meal_count == -1)
        {
            std::cout << "\nyou cannot add more than " << maximum_food << " meals!\n";
            file.close();
            break;
        }

        std::string food;
        std::cout << "\nwrite the food name you want to add to the food list: ";
        std::cin >> food;

        bool exists = false;
        for (const auto &element : meals)
        {
            if (element == food)
            {
                std::cout << "\nThe food already exists in your list\n";
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            file << food << std::endl;
            meals.push_back(food);
            std::cout << "Added: " << food << std::endl;
            meal_count++;
        }

        std::string answer;
        std::cout << "\ndo you want to continue? (yes/no): ";
        std::cin >> answer;

        if (answer != "yes")
        {
            break;
        }
    }

    file.close();
}

void Meal::deleting_meal_side(const std::string &filename)
{
    std::vector<std::string> names;
    std::string meal;
    std::ifstream temp_file(filename, std::ios::in);
    if (!temp_file.is_open())
    {
        std::cout << "\nCannot open the file\n";
        return;
    }
    
    while (temp_file >> meal)
    {
        names.push_back(meal);
    }
    temp_file.close();
    
    std::cout << "\nenter which meal do you want to delete!\n";
    std::cin >> meal;
    
    for (size_t i = 0; i < names.size(); i++)
    {
        if (meal == names[i])
        {
            names.erase(names.begin() + i);
            break;
        }
    }
    
    std::ofstream file(filename, std::ios::out);
    for (auto &element : names)
    {
        file << element << std::endl;
    }
    file.close();
}

void Meal::update_meal_price(const std::string &filename)
{
    std::string temp_file = "temp.dat";
    std::string ans;
    std::vector<float> prices;
    float line;
    int current_line = 0;
    int temp_line = 1;
    
    std::ifstream file(filename);
    std::ofstream t_file(temp_file, std::ios::out);

    if (!file.is_open() || !t_file.is_open())
    {
        std::cerr << "Cannot open the file!";
        return;
    }

    std::cout << "\nwhich meal price do you want to update? (breakfast/lunch/dinner/side dish)\n";
    std::cin >> ans;

    if (ans == "breakfast") current_line = 1;
    else if (ans == "lunch") current_line = 2;
    else if (ans == "dinner") current_line = 3;
    else if (ans == "side dish") current_line = 4;

    if (current_line == 0)
    {
        std::cout << "\nyou entered the wrong entry!\n";
        return;
    }

    while (file >> line)
    {
        if (current_line == temp_line)
        {
            std::cout << "\nThe current price is " << line << "\nEnter the new price\n";
            std::cin >> line;
        }
        prices.push_back(line);
        temp_line++;
    }

    if (prices.empty())
    {
        file.close();
        t_file.close();
        std::remove(temp_file.c_str());
        std::cout << "\nthe file is empty!\n";
        default_meal_price();
        return;
    }

    for (auto &element : prices)
    {
        t_file << element << std::endl;
    }

    file.close();
    t_file.close();

    if (std::remove(filename.c_str()) != 0)
    {
        std::cout << "\nCan not remove the file!\n";
        return;
    }

    if (std::rename(temp_file.c_str(), filename.c_str()) != 0)
    {
        std::cout << "\nCan not update the prices!\n";
        return;
    }

    std::cout << "\nPrice successfully updated!\n";
}

void Meal::adding_meal_side_items(const std::string &filename)
{
    int count = meal_counting_meal(filename);
    if (count >= maximum_side_dish || count == -1)
    {
        std::cout << "\nyou can not add any side dish! capacity error!\n";
        return;
    }

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "\nCan't open the file for writing\n";
        return;
    }

    std::string side_dish;
    std::vector<std::string> sides;
    std::ifstream search(filename);

    while (search >> side_dish)
    {
        sides.push_back(side_dish);
    }
    search.close();

    while (true)
    {
        if (count >= maximum_side_dish)
        {
            std::cout << "\nyou can not add any side dish! capacity error!\n";
            break;
        }
        
        std::cout << "\nenter the side dish you want to add!\n";
        std::cin >> side_dish;
        
        bool exist = false;
        for (const auto &element : sides)
        {
            if (element == side_dish)
            {
                exist = true;
                break;
            }
        }
        
        if (!exist)
        {
            file << side_dish << std::endl;
            sides.push_back(side_dish);
            std::cout << "\nside " << side_dish << " added successfully!\n";
            count++;
        }
        else
        {
            std::cout << "\nYou can not add to the side dish because the side dish already exists!\n";
        }

        std::string ans;
        std::cout << "\nif you want to continue enter yes!\n";
        std::cin >> ans;
        if (ans != "yes")
        {
            break;
        }
    }
    file.close();
}

// Phase 2 New Methods
bool Meal::getIsActive() const
{
    return isActive;
}

void Meal::activate()
{
    isActive = true;
}

void Meal::deactivate()
{
    isActive = false;
}

MealType Meal::getMealType() const
{
    return mealType;
}

ReserveDay Meal::getReserveDay() const
{
    return reserveDay;
}

void Meal::setMealType(MealType type)
{
    mealType = type;
}

void Meal::setReserveDay(ReserveDay day)
{
    reserveDay = day;
}

void Meal::addSideItem(const std::string& item)
{
    if (sideItems.size() < maximum_side_dish)
    {
        sideItems.push_back(item);
    }
    else
    {
        std::cout << "\nCannot add more side items. Maximum limit reached.\n";
    }
}

void Meal::addPrice(float newPrice)
{
    price = newPrice;
}

void Meal::set_meal_id()
{
    int ID = 0;
    std::string food_name = get_meal_name();
    std::string fs_temp;
    
    switch (mealType)
    {
    case MealType::BREAKFAST:
    {
        std::ifstream count(breakfast_File, std::ios::in);
        while (count >> fs_temp)
        {
            ID++;
            if (fs_temp == food_name)
            {
                break;
            }
        }
        count.close();
        break;
    }
    case MealType::LUNCH:
    {
        std::ifstream count(lunch_File, std::ios::in);
        while (count >> fs_temp)
        {
            ID++;
            if (fs_temp == food_name)
            {
                break;
            }
        }
        count.close();
        break;
    }
    case MealType::DINNER:
    {
        std::ifstream count(dinner_File, std::ios::in);
        while (count >> fs_temp)
        {
            ID++;
            if (fs_temp == food_name)
            {
                break;
            }
        }
        count.close();
        break;
    }
    default:
        mealID = 0;
        return;
    }

    // Add side item code if needed
    mealID = ID;
}

void Meal::set_meal_name(const std::string &n)
{
    std::vector<std::string> foods;
    std::string food;
    
    switch (mealType)
    {
    case MealType::BREAKFAST:
    {
        std::ifstream search(breakfast_File);
        if (!search.is_open())
        {
            std::cout << "\nCan not open the file\n!";
            return;
        }

        while (search >> food)
        {
            foods.push_back(food);
        }
        search.close();
        break;
    }
    case MealType::LUNCH:
    {
        std::ifstream search(lunch_File);
        if (!search.is_open())
        {
            std::cout << "\nCan not open the file\n!";
            return;
        }

        while (search >> food)
        {
            foods.push_back(food);
        }
        search.close();
        break;
    }
    case MealType::DINNER:
    {
        std::ifstream search(dinner_File);
        if (!search.is_open())
        {
            std::cout << "\nCan not open the file\n!";
            return;
        }

        while (search >> food)
        {
            foods.push_back(food);
        }
        search.close();
        break;
    }
    default:
        throw std::invalid_argument("\nInvalid meal type!\n");
    }

    for (const auto &element : foods)
    {
        if (element == n)
        {
            name = n;
            return;
        }
    }

    throw std::invalid_argument("\nyou can not choose a meal because it's not in the list!\n");
}

void Meal::set_meal_type(MealType t)
{
    mealType = t;
}

void Meal::set_meal_price()
{
    std::vector<float> prices;
    std::ifstream p_file(price_File);
    if (!p_file.is_open())
    {
        std::cout << "\ncan not open the price file!\n";
        price = 15;
        return;
    }
    
    float temp_p;
    while (p_file >> temp_p)
    {
        prices.push_back(temp_p);
    }
    p_file.close();

    switch (mealType)
    {
    case MealType::BREAKFAST:
        price = prices.size() > 0 ? prices[0] : 15;
        break;
    case MealType::LUNCH:
        price = prices.size() > 1 ? prices[1] : 20;
        break;
    case MealType::DINNER:
        price = prices.size() > 2 ? prices[2] : 25;
        break;
    case MealType::SIDE_DISH:
        price = prices.size() > 3 ? prices[3] : 5;
        break;
    default:
        price = 0.0;
        break;
    }
}

void Meal::set_meal_side_item(const std::string &s)
{
    std::vector<std::string> side_dishes;
    std::string side;
    std::ifstream side_file(side_dish_File);

    if (!side_file.is_open())
    {
        std::cout << "\ncannot open the file\n";
        return;
    }
    
    while (side_file >> side)
    {
        side_dishes.push_back(side);
    }
    side_file.close();

    for (const auto &element : side_dishes)
    {
        if (element == s)
        {
            sideItems.push_back(s);
            return;
        }
    }

    throw std::invalid_argument("\nthe side dish you chose doesn't exist in the list\n!");
}

int Meal::get_meal_id() const
{
    return mealID;
}

float Meal::get_meal_price() const
{
    return price;
}

std::string Meal::get_meal_name() const
{
    return name;
}

MealType Meal::get_meal_type() const
{
    return mealType;
}

std::string Meal::get_meal_side_item() const
{
    if (sideItems.empty())
    {
        return "unknown";
    }
    return sideItems[0];
}

std::vector<std::string> Meal::get_side_items() const
{
    return sideItems;
}

int Meal::meal_input()
{
    while (true)
    {
        std::cout << "\nwhich type of food you want to choose?\nbreakfast\nlunch\ndinner\nside item\n?\n";
        std::string ans;
        std::cin >> ans;
        
        if (ans == "breakfast")
        {
            set_meal_type(MealType::BREAKFAST);
        }
        else if (ans == "lunch")
        {
            set_meal_type(MealType::LUNCH);
        }
        else if (ans == "dinner")
        {
            set_meal_type(MealType::DINNER);
        }
        else if (ans == "side item")
        {
            set_meal_type(MealType::SIDE_DISH);
        }
        else
        {
            set_meal_type(MealType::UNKNOWN);
            std::cout << "the type you chose doesn't exist!";
            continue;
        }

        std::cout << "\nif you want to see the list of the food press yes else press no!";
        std::cin >> ans;
        
        std::string filename;
        switch (get_meal_type())
        {
        case MealType::BREAKFAST:
            filename = breakfast_File;
            break;
        case MealType::LUNCH:
            filename = lunch_File;
            break;
        case MealType::DINNER:
            filename = dinner_File;
            break;
        case MealType::SIDE_DISH:
            filename = side_dish_File;
            break;
        default:
            filename = "";
        }

        if (ans == "yes" || ans == "Yes")
        {
            std::string choice;
            std::ifstream file(filename, std::ios::in);
            std::cout << "\nthe list of food you can choose from is : \n";
            while (file >> choice)
            {
                std::cout << choice << std::endl;
            }
            file.close();
        }

        std::string choice;
        std::cout << "\nplease enter the name of the food you want to pick\n";
        std::cin >> choice;
        
        try
        {
            set_meal_name(choice);
            std::cout << "\nyou successfully chose " << choice << "!\n";
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    // Set reserve day
    std::cout << "\nWhich day is this meal for? (saturday/sunday/monday/tuesday/wednesday/thursday/friday)\n";
    std::string day_str;
    std::cin >> day_str;
    
    if (day_str == "saturday") setReserveDay(ReserveDay::SATURDAY);
    else if (day_str == "sunday") setReserveDay(ReserveDay::SUNDAY);
    else if (day_str == "monday") setReserveDay(ReserveDay::MONDAY);
    else if (day_str == "tuesday") setReserveDay(ReserveDay::TUESDAY);
    else if (day_str == "wednesday") setReserveDay(ReserveDay::WEDNESDAY);
    else if (day_str == "thursday") setReserveDay(ReserveDay::THURSDAY);
    else if (day_str == "friday") setReserveDay(ReserveDay::FRIDAY);
    else setReserveDay(ReserveDay::SATURDAY);

    set_meal_id();
    set_meal_price();
    
    // Add side items
    std::cout << "\nDo you want to add side items? (yes/no)\n";
    std::string add_sides;
    std::cin >> add_sides;
    
    if (add_sides == "yes" || add_sides == "Yes")
    {
        std::string side_item;
        std::cout << "\nEnter side items (one at a time, type 'done' when finished):\n";
        while (true)
        {
            std::cin >> side_item;
            if (side_item == "done") break;
            try
            {
                set_meal_side_item(side_item);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    return 0;
}

std::string meal_type_to_string(MealType t)
{
    switch (t)
    {
    case MealType::BREAKFAST:
        return "breakfast";
    case MealType::LUNCH:
        return "lunch";
    case MealType::DINNER:
        return "dinner";
    case MealType::SIDE_DISH:
        return "side dish";
    default:
        return "unknown";
    }
}

std::string reserve_day_to_string(ReserveDay d)
{
    switch (d)
    {
    case ReserveDay::SATURDAY:
        return "saturday";
    case ReserveDay::SUNDAY:
        return "sunday";
    case ReserveDay::MONDAY:
        return "monday";
    case ReserveDay::TUESDAY:
        return "tuesday";
    case ReserveDay::WEDNESDAY:
        return "wednesday";
    case ReserveDay::THURSDAY:
        return "thursday";
    case ReserveDay::FRIDAY:
        return "friday";
    default:
        return "unknown";
    }
}

void Meal::print() const
{
    std::cout << "\nmeal ID = " << get_meal_id()
              << "\nprice = " << get_meal_price()
              << "\nmeal name = " << get_meal_name()
              << "\nmeal type = " << meal_type_to_string(mealType)
              << "\nreserve day = " << reserve_day_to_string(reserveDay)
              << "\nactive = " << (isActive ? "yes" : "no")
              << "\nside items = ";
    
    if (sideItems.empty())
    {
        std::cout << "none";
    }
    else
    {
        for (size_t i = 0; i < sideItems.size(); i++)
        {
            std::cout << sideItems[i];
            if (i < sideItems.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}