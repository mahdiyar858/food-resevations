#include <iostream>
#include "panel.h"
#include "student.h"
#include "admin.h"
#include "storage.h"

int main() {
    // Initialize storage
    Storage& storage = Storage::getInstance();
    
    // Create sample data
    Student student(1, "12345678", "John", "Doe", "john.doe@example.com", 100.0f, "123-456-7890", true);
    Admin admin(1, "Admin", "User", "hashed_password");
    
    // Create panel and set user
    Panel panel(&student);
    
    int choice;
    do {
        panel.showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        panel.action(choice);
    } while (choice != 0);
    
    return 0;
}