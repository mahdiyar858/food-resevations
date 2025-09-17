#include "diningHall.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string DiningHall::hall_file_1 = "hall_file_1";
std::string DiningHall::hall_file_2 = "hall_file_2";
std::string DiningHall::hall_file_3 = "hall_file_3";
std::string DiningHall::hall_file_4 = "hall_file_4";
std::string DiningHall::hall_file_5 = "hall_file_5";

DiningHall::DiningHall()
{
    hall_id = 1;
    name = "d1";
    address = "the last stop of the bus station";
    capacity = 500;
}

DiningHall::DiningHall(const std::string &filename, const std::string &n, const std::string &a, int c)
{
    set_hall_id(filename);
    set_hall_name(n);
    set_hall_address(a);
    set_hall_capacity(filename);
}

void DiningHall::initilize_hall_files()
{
    std::ofstream hall_1(hall_file_1, std::ios::app);
    std::ofstream hall_2(hall_file_2, std::ios::app);
    std::ofstream hall_3(hall_file_3, std::ios::app);
    std::ofstream hall_4(hall_file_4, std::ios::app);
    std::ofstream hall_5(hall_file_5, std::ios::app);

    if (!hall_1.is_open() || !hall_2.is_open() || !hall_3.is_open() || !hall_4.is_open() || !hall_5.is_open())
    {
        std::cout << "\nfiles can not be open!\n";
    }
    else
    {
        std::cout << "\nhall files checked successfully!\n";
    }

    hall_1.close();
    hall_2.close();
    hall_3.close();
    hall_4.close();
    hall_5.close();
}

int DiningHall::counting_hall_files(const std::string &filename)
{
    std::string person;
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout<<"\nthere is a problem with the file\n";
        return -1;
    }
    std::vector<std::string> count = {};
    while (file >> person)
    {
        count.push_back(person);
    }

    int i = 0;

    for (auto &element : count)
    {
        i++;
    }

    if (i > -1 && i < DiningHall::max_capacity)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

void DiningHall::canceling_capacity(const std::string &filename)
{
    int i = counting_hall_files(filename);

    std::ofstream file(filename);
    
    if(!file.is_open())
    {
        std::cout<<"\nthere is a problem with the file\n";
    }
    i--;
    for (;i>0 ;i--)
    {
        file<<i<<std::endl;
    }
}

void DiningHall::set_hall_id_capacity_name()
{
    int i = 0;
    std::cout << "\nwhich hall do you want to choos ?(hall 1 to 5)\n";
    std::cin >> i;
    switch (i)
    {
    case 1:
    {
        int capa = counting_hall_files(hall_file_1);
        if (capa == -1)
        {
            throw std::invalid_argument("\nthe hall you decide to dine in is full or there is problem with the file!\n");
        }
        else
        {
            std::ofstream file_1(hall_file_1, std::ios::app);
            file_1 << capa++ << std::endl;
            name = "hall one";
            capacity = capa;
            hall_id = 1;
            file_1.close();
            break;
        }
    }
    case 2:
    {
        int capa = counting_hall_files(hall_file_2);
        if (capa == -1)
        {
            throw std::invalid_argument("\nthe hall you decide to dine in is full or there is problem with the file!\n");
        }
        else
        {
            std::ofstream file_2(hall_file_2, std::ios::app);
            file_2 << capa++ << std::endl;
            name = "hall two";
            capacity = capa;
            hall_id = 2;
            file_2.close();
            break;
        }
    }
    case 3:
    {
        int capa = counting_hall_files(hall_file_3);
        if (capa == -1)
        {
            throw std::invalid_argument("\nthe hall you decide to dine in is full or there is problem with the file!\n");
        }
        else
        {
            std::ofstream file_3(hall_file_3, std::ios::app);
            file_3 << capa++ << std::endl;
            name = "hall three";
            capacity = capa;
            hall_id = 3;
            file_3.close();
            break;
        }
    }
    case 4:
    {
        int capa = counting_hall_files(hall_file_4);
        if (capa == -1)
        {
            throw std::invalid_argument("\nthe hall you decide to dine in is full or there is problem with the file!\n");
        }
        else
        {
            std::ofstream file_4(hall_file_4, std::ios::app);
            file_4 << capa++ << std::endl;
            name = "hall four";
            capacity = capa;
            hall_id = 4;
            file_4.close();
            break;
        }
    }
    case 5:
    {
        int capa = counting_hall_files(hall_file_5);
        if (capa == -1)
        {
            throw std::invalid_argument("\nthe hall you decide to dine in is full or there is problem with the file!\n");
        }
        else
        {
            std::ofstream file_5(hall_file_5, std::ios::app);
            file_5 << capa++ << std::endl;
            name = "hall five";
            capacity = capa;
            hall_id = 5;
            file_5.close();
            break;
        }
    }

    default:
        throw std::invalid_argument("\nthe hall you choose doesn't exist!\n");
        break;
    }
}

void DiningHall::set_hall_id(const std::string &filename)
{
    if (filename == "hall_file_1")
    {
        hall_id = 1;
        return;
    }
    else if (filename == "hall_file_2")
    {
        hall_id = 2;
        return;
    }
    else if (filename == "hall_file_3")
    {
        hall_id = 3;
        return;
    }
    else if (filename == "hall_file_4")
    {
        hall_id = 4;
        return;
    }

    hall_id = 5;
}

void DiningHall::set_hall_name(const std::string &n)
{
    name = n;
}

void DiningHall::set_hall_address(const std::string &h)
{
    if (h == "hall one")
        address = "\nnext to the hall two\n";
    else if (h == "hall two")
    {
        address = "\nnext to the hall one\n";
    }
    else if (h == "hall three")
    {
        address = "\nnext to the hall four\n";
    }
    else if (h == "hall four")
    {
        address = "\nif you think this hall still exist you know where it is don't ask for direction\n";
    }
    else if (h == "hall five")
    {
        address = "\nonly elite people can dine here how did you find here !? if you are not an elite then by by!\n";
    }
    else
    {
        address = "\nif you think there is another hall than these five you should go here Ibn sina mental hospital\n";
    }
}

void DiningHall::set_hall_capacity(const std::string &filename)
{
    if(counting_hall_files(filename) == -1)
    {
        std::cout<<"\nthe hall you chose is full!";
        capacity = 500;
    }
    else
    {
        capacity = counting_hall_files(filename)+1;
    }
}

std::string DiningHall::get_hall_file() const
{
    std::string filename = get_hall_name();

    if(filename == "hall one")
    {
        return hall_file_1;
    }
    else if(filename == "hall two")
    {
        return hall_file_2;
    }
    else if(filename == "hall three")
    {
        return hall_file_3;
    }
    else if(filename == "hall four")
    {
        return hall_file_4;
    }
    else
    {
        return hall_file_5;
    }
}

int DiningHall::get_hall_id() const
{
    return hall_id;
}

std::string DiningHall::get_hall_name() const
{
    return name;
}

std::string DiningHall::get_hall_address() const
{
    return address;
}

int DiningHall::get_hall_capacity() const
{
    return capacity;
}

void DiningHall::hall_input()
{
    while (true)
    {
        try
        {
            set_hall_id_capacity_name();
            std::string location = get_hall_name();
            set_hall_address(location);
            std::cout << "\ntevery things is good ID and Capacity and name are good!";
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\nyou have to try again!\n";
    }
}

void DiningHall::hall_print() const
{
    std::cout << "\nhall ID = " << hall_id
              << "\nhall name = " << name
              << "\nhall address = " << address
              << "\nhall capacity = " << capacity;
}