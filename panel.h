#ifndef PANEL_H
#define PANEL_H

#include "user.h"
#include "student.h"
#include "reservation.h"

class Panel {
private:
    User* currentUser;
    
public:
    Panel(User* user = nullptr);
    void setUser(User* user);
    
    void showMenu() const;
    void action(int choice);
    
    // Functions that need to be defined but not implemented yet
    void showStudentInfo() const;
    void checkBalance() const;
    void viewReservations() const;
    void addReservation(const Reservation& Reservation);
    void addToShoppingCart();
    void confirmShoppingCart();
    void removeShoppingCartItem();
    void increaseBalance();
    void viewRecentTransactions();
    void cancelReservation(int reservationID);
    void exit();
};

#endif