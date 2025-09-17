#include "meal.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits> // for igonor
#include <fstream>
#include <cmath> // for NAN

std::string meal::breakfast_File = "breakfast_meals.dat";
std::string meal::lunch_File = "lunch_meals.dat";
std::string meal::dinner_File = "dinner_meal.dat";
std::string meal::side_dish_File = "side_dish.dat";
std::string meal::price_File = "price_file.dat";

meal::meal()
{
    meal_id = 0;
    price = 0.0;
    meal_name = "unknown";
    meal_type = typo::unknown;
    side_item = "unknown";
}

meal::meal(int id, const std::string &m, typo t, const std::string &s)
{
    set_meal_id();
    set_meal_price();
    set_meal_name(m);
    set_meal_type(t);
    set_meal_side_item(s);
}

bool meal::initialize_meal_file()
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

bool meal::default_meal_price()
{
    std::ofstream p_file(price_File, std::ios::out);

    if (!p_file.is_open())
    {
        std::cout << "\nCan not create the price file!\n";
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 3)
        {
            p_file << 5;
        }

        p_file << 15;
    }

    p_file.close();
    return true;
}

int meal::meal_counting_meal(const std::string &filename) // for counting the meal and also for side items!
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << ("\nthere is a problem with the file! (cannot open the file)\n");
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

void meal::meal_adding_meal(const std::string &filename)
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

        if (exists == false)
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

void meal::deleting_meal_side(const std::string &filename)
{
    std::vector<std::string> names = {};
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
    for (int i = 0; i < names.size(); i++)
    {
        if (meal == names[i])
        {
            names[i].erase();
        }
    }
    std::ofstream file(filename, std::ios::out);
    for (auto &element : names)
    {
        file << element << std::endl;
    }
}
void meal::update_meal_price(const std::string &filename)
{
    std::string temp_file = "temp.dat";
    std::string ans;
    std::vector<float> price = {};
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

    std::cout << "\nwhich meal price do you want to update? (enter side dish if you desire to change that)\n";
    std::cin >> ans;

    if (ans == "breakfast")
    {
        current_line = 1;
    }
    else if (ans == "lunch")
    {
        current_line = 2;
    }
    else if (ans == "dinner")
    {
        current_line = 3;
    }
    else if (ans == "side dish")
    {
        current_line = 4;
    }

    if (current_line == 0)
    {
        std::cout << "\nyou entered the wrong entry!\n";
        return;
    }

    while (file >> line)
    {
        if (current_line == temp_line)
        {
            std::cout << "\nThe current price is " << line << "\nEnter the the new price\n";
            std::cin >> line;
        }
        price.push_back(line);
        temp_line++;
    }

    if (price.empty())
    {
        file.close();
        t_file.close();
        std::remove(temp_file.c_str()); // Delete the temp file
        std::cout << "\nthe file is empty!\n";
        default_meal_price();
    }

    for (auto &element : price)
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

void meal::adding_meal_side_items(const std::string &filename)
{
    int count = meal_counting_meal(filename);
    if (count >= maximum_side_dish || count == -1)
    {
        std::cout << "\nyou can not add any side dish!copacity error !\n";
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
        if (count >= 9 || count == 0)
        {
            std::cout << "\nyou can not add any side dish!copacity error or file erro!\n";
            return;
        }
        std::cout << "\enter the side dish you want to add!\n";
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
        if (exist == false)
        {
            file << side_dish << std::endl;
            std::cout << "\nside " << side_dish << "added successfully!\n";
        }
        else
        {
            std::cout << "\nYou can not add to the side dish because the side dish is already exist!\n";
        }

        std::string ans;
        std::cout << "\nif you want to continue enter yes!\n";
        std::cin >> ans;
        if (ans != "yes")
        {
            file.close();
            break;
        }
    }
    file.close();
}

void meal::set_meal_id()
{
    std::string food_name = get_meal_name();
    std::string side_name = get_meal_side_item();
    std::string fs_temp;
    int ID = 0000;
    int side = 0;
    typo temp = get_meal_type();
    switch (temp)
    {
    case typo::breakfast:
    {
        std::ifstream count(breakfast_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == food_name)
            {
                ID = (ID * 10) + 1000;
                count.close();
                break;
            }

            ID++;
        }
        std::ifstream count(side_dish_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == side_name)
            {
                ID = ID + side;
                count.close();
                break;
            }
            side++;
        }
    }
    case typo::lunch:
    {
        std::ifstream count(lunch_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == food_name)
            {
                ID = (ID * 10) + 1000;
                count.close();
                break;
            }

            ID++;
        }
        std::ifstream count(side_dish_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == side_name)
            {
                ID = ID + side;
                count.close();
                break;
            }
            side++;
        }
    }
    case typo::dinner:
    {
        std::ifstream count(lunch_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == food_name)
            {
                ID = (ID * 10) + 1000;
                count.close();
                break;
            }

            ID++;
        }
        std::ifstream count(side_dish_File, std::ios::in);
        while (count >> fs_temp)
        {
            if (fs_temp == side_name)
            {
                ID = ID + side;
                count.close();
                break;
            }
            side++;
        }
    }
    default:
    {
        meal_id = 0000;
        return;
    }
    }

    if (ID % 10 == 100 || ID % 10 == 200 || ID % 10 == 300)
    {
        meal_id = 0000;
    }
    else if (ID == 3000 || ID == 2000 || ID == 1000)
    {
        meal_id = 0000;
    }
    else
    {
        meal_id == ID;
    }
}

void meal::set_meal_name(const std::string &name)
{
    std::vector<std::string> foods = {};
    std::string food;
    typo temp = get_meal_type();
    switch (temp)
    {
    case typo::breakfast:
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

        for (const auto &element : foods)
        {
            if (element == food)
            {
                meal_name = food;
                return;
            }
        }

        throw std::invalid_argument("\nyou can not choose a meal because it's not in the list!\n");
    }
    case typo::lunch:
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

        for (const auto &element : foods)
        {
            if (element == food)
            {
                meal_name = food;
                return;
            }
        }

        throw std::invalid_argument("\nyou can not choose a meal because it's not in the list!\n");
    }
    case typo::dinner:
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

        for (const auto &element : foods)
        {
            if (element == food)
            {
                meal_name = food;
                return;
            }
        }

        throw std::invalid_argument("\nyou can not choose a meal because it's not in the list!\n");
    }
    default:
    {
        throw std::invalid_argument("\nyou can not choose a meal because it's not in the list!\n");
    }
    }
}

void meal::set_meal_type(typo t)
{
    switch (t)
    {
    case typo::breakfast:
        meal_type = t;
        break;
    case typo::lunch:
        meal_type = t;
        break;
    case typo::dinner:
        meal_type = t;
        break;
    default:
        meal_type = typo::unknown;
        break;
    }
}

void meal::set_meal_price()
{
    std::vector<float> prices;
    std::ifstream p_file(price_File);
    if (!p_file.is_open())
    {
        std::cout << "\ncan not open the price file!\n";
        price = 15;
        return;
    }
    else
    {
        int temp_p;
        while (p_file >> temp_p)
        {
            prices.push_back(temp_p);
        }
        p_file.close();
    }

    typo temp = get_meal_type();

    switch (temp)
    {
    case typo::breakfast:
    {
        price = prices[0];
        break;
    }
    case typo::lunch:
    {
        price = prices[1];
        break;
    }
    case typo::dinner:
    {
        price = prices[2];
        break;
    }
    case typo::side_dish:
    {
        price = prices[3];
        break;
    }

    default:
        price = 0.0;
        break;
    }
}

void meal::set_meal_side_item(const std::string &s)
{
    std::vector<std::string> side_dishes;
    std::string side;
    std::ifstream side_file(side_dish_File);

    if (!side_file.is_open())
    {
        std::cout << "\ncannot open the file\n";
        side_item = "unknown";
        return;
    }
    else
    {
        while (side_file >> side)
        {
            side_dishes.push_back(side);
        }
        side_file.close();
    }

    for (const auto &element : side_dishes)
    {
        if (element == s)
        {
            side_item = s;
            break;
        }
    }

    throw std::invalid_argument("\nthe side dish you chose doesn't exist in the list\n!");
}

int meal::get_meal_id() const
{
    return meal_id;
}

float meal::get_meal_price() const
{
    return price;
}

std::string meal::get_meal_name() const
{
    return meal_name;
}

typo meal::get_meal_type() const
{
    return meal_type;
}
std::string meal::get_meal_side_item() const
{
    return side_item;
}

int meal::meal_input()
{
    while (true) // meal_name and meal_type and also side_items
    {
        std::cout << "\nwhich typeo of food you want to chose?\nbreakfast\nlunch\ndinner\nside item\n?\n";
        std::string ans;
        std::cin >> ans;
        if (ans == "breakfast")
        {
            set_meal_type(typo::breakfast);
            std::cout << "\nif you want to see the list of the food press yes else press no!";
            std::cin >> ans;
            if (ans == "yes" || ans == "Yes")
            {
                std::string choise;
                std::ifstream file(breakfast_File, std::ios::in);
                std::cout << "\nthe list of food you can choose from is : \n";
                while (std::cin >> choise)
                {
                    std::cout << std::endl
                              << choise << std::endl;
                }
                std::cout << "\nplease enter the name of the food you want to pick\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your breakfast!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::string choise;
                std::cout << "\nenter the food you desire to have for your breakfast!\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your breakfast!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        else if (ans == "lunch")
        {
            set_meal_type(typo::lunch);
            std::cout << "\nif you want to see the list of the food press yes else press no!\n";
            std::cin >> ans;
            if (ans == "yes" || ans == "Yes")
            {
                std::string choise;
                std::ifstream file(breakfast_File, std::ios::in);
                std::cout << "\nthe list of food you can choose from is : \n";
                while (std::cin >> choise)
                {
                    std::cout << std::endl
                              << choise << std::endl;
                }
                std::cout << "\nplease enter the name of the food you want to pick\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "you successfully chose " << choise << "for your lunch!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::string choise;
                std::cout << "\nenter the food you desire to have for your lunch!\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your lunch!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        else if (ans == "dinner")
        {
            set_meal_type(typo::dinner);
            std::cout << "\nif you want to see the list of the food press yes else press no!\n";
            std::cin >> ans;
            if (ans == "yes" || ans == "Yes")
            {
                std::string choise;
                std::ifstream file(breakfast_File, std::ios::in);
                std::cout << "\nthe list of food you can choose from is : \n";
                while (std::cin >> choise)
                {
                    std::cout << std::endl
                              << choise << std::endl;
                }
                std::cout << "\nplease enter the name of the food you want to pick\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "you successfully chose " << choise << "for your dinner!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::string choise;
                std::cout << "\nenter the food you desire to have for your dinner!\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your dinner!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        else if (ans == "side item")
        {
            set_meal_type(typo::side_dish);
            std::cout << "\nif you want to see the list of the side dishes press yes else press no!\n";
            std::cin >> ans;
            if (ans == "yes" || ans == "Yes")
            {
                std::string choise;
                std::ifstream file(breakfast_File, std::ios::in);
                std::cout << "\nthe list of items you can choose from is : \n";
                while (std::cin >> choise)
                {
                    std::cout << std::endl
                              << choise << std::endl;
                }
                std::cout << "\nplease enter the name of the sides you want to pick\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your side dish!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::string choise;
                std::cout << "\nenter the food you desire to have for your side dish!\n";
                std::cin >> choise;
                try
                {
                    set_meal_name(choise);
                    std::cout << "\nyou successfully chose " << choise << "for your side dish!\n";
                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        else
        {
            set_meal_type(typo::unknown);
            std::cout << "the type you chose doesn't exist!";
        }
        if (get_meal_name() != "unkown")
        {
            std::cout << "\nif you want change your reserve for the meal or you want to chose another type instead of the old one press yse!";
            std::cin >> ans;
            if (ans == "yes" || ans == "Yes")
            {
                std::cout << "\nyou chose to chnage!\n";
            }
            else
            {
                std::cout << "\nyou decide to end the process!\n";
                break;
            }
        }
        else
        {
            std::cout<<"\nbecause you didn't enter the correct food you have to try agian and nothing is reserved for you!\n";
        }
    }

    set_meal_id(); // creating meal_id
}

std::string meal_typo_to_string(typo t)
{
    switch (t)
    {
    case typo::breakfast:
        return "breakfast";
    case typo::lunch:
        return "lunch";
    case typo::dinner:
        return "dinner";
    case typo::side_dish:
        return "side dish";
    default:
        return "unknown";
    }
}

void meal::meal_print() const
{
    std::cout << "\nmeal ID = " << get_meal_id()
              << "\nprice = " << get_meal_price()
              << "\nmeal name =" << get_meal_name()
              << "\nmeal type = " << meal_typo_to_string(meal_type)
              << "\nside items = " << get_meal_side_item();
}
