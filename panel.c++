#include "panel.h"
#include <iostream>

Panel::Panel(User *user) : currentUser(user) {}

void Panel::setUser(User *user)
{
    currentUser = user;
}

void Panel::showMenu() const
{
    std::cout << "=== System Menu ===" << std::endl;
    std::cout << "1. Show Student Info" << std::endl;
    std::cout << "2. Check Balance" << std::endl;
    std::cout << "3. View Reservations" << std::endl;
    std::cout << "4. Add Reservation" << std::endl;
    std::cout << "5. Add to Shopping Cart" << std::endl;
    std::cout << "6. Confirm Shopping Cart" << std::endl;
    std::cout << "7. Remove Shopping Cart Item" << std::endl;
    std::cout << "8. Increase Balance" << std::endl;
    std::cout << "9. View Recent Transactions" << std::endl;
    std::cout << "10. Cancel Reservation" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "===================" << std::endl;
}

void Panel::action(int choice)
{
    switch (choice)
    {
    case 0:
        exit();
        break;
    case 1:
        showStudentInfo();
        break;
    case 2:
        checkBalance();
        break;
    case 3:
        viewReservations();
        break;
    // ... other cases
    default:
        std::cout << "Invalid choice!" << std::endl;
    }
}

// Functions that need to be defined but not implemented yet
void Panel::showStudentInfo() const
{
    std::cout << "showStudentInfo() called" << std::endl;
}

void Panel::checkBalance() const
{
    std::cout << "checkBalance() called" << std::endl;
}

void Panel::viewReservations() const
{
    std::cout << "viewReservations() called" << std::endl;
}

void Panel::addReservation(const Reservation &reservation)
{
    std::cout << "addReservation() called" << std::endl;
}

void Panel::addToShoppingCart()
{
    std::cout << "addToShoppingCart() called" << std::endl;
}

void Panel::confirmShoppingCart()
{
    std::cout << "confirmShoppingCart() called" << std::endl;
}

void Panel::removeShoppingCartItem()
{
    std::cout << "removeShoppingCartItem() called" << std::endl;
}

void Panel::increaseBalance()
{
    std::cout << "increaseBalance() called" << std::endl;
}

void Panel::viewRecentTransactions()
{
    std::cout << "viewRecentTransactions() called" << std::endl;
}

void Panel::cancelReservation(int reservationID)
{
    std::cout << "cancelReservation() called" << std::endl;
}

void Panel::exit()
{
    std::cout << "Exiting system..." << std::endl;
}