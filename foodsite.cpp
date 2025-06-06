#include <iostream>
#include <string>
#include <iomanip>
#include <regex>     // for cheking if the name contain only letter
#include <cctype>    // Required for isdigit(), isalpha()
#include <stdexcept> // for invalid arguments
#include <limits>    // for igonor
#include <ctime>    // for time

using namespace std;

class reservation;
class meal;
class student;
class diningHall;

bool isAlphaOnly(const string &str)
{
    regex pattern("^[a-zA-Z]+$");
    return regex_match(str, pattern);
}

enum class status
{
    FAILED = 1,
    SUCCESS = 2,
    CANCELED = 3
};

class student
{
    int u_id; // user id
    string s_id;
    string name;
    string f_name;
    string email;
    float balance;
    bool active;

public:
    student()
    {
        u_id = 0;
        s_id = "10000000";
        name = "unknown";
        f_name = "unknown";
        email = "unknown@gmail.com";
        balance = 0.0f;
        active = true;
    }
    student(int id, const string &st_id, const string &n, const string &f, const string &e, float b, bool activity)
    {
        set_u_id(id);
        set_s_id(st_id);
        set_n(n);
        set_f(f);
        set_e(e);
        set_b(b);
        set_active(activity);
    }

    string get_s() const
    {
        return s_id;
    }

    string get_n() const
    {
        return name;
    }

    string get_f() const
    {
        return f_name;
    }

    string get_e() const
    {
        return email;
    }

    int get_u() const
    {
        return u_id;
    }

    float get_b() const
    {
        return balance;
    }

    bool get_active() const
    {
        return active;
    }

    void set_u_id(int id)
    {
        if (id > 10000 || id < 0)
        {
            throw invalid_argument("\nThe user ID must be between 0 - 10000\n");
        }
        u_id = id;
    }

    void set_s_id(const string &st_id)
    {
        if (st_id.length() != 8)
        {
            throw invalid_argument("\nStudent ID must be exactly 8 digits\n");
        }
        for (int c = 0; c < 8; c++)
        {
            if (!isdigit(st_id[c]))
            {
                throw invalid_argument("\nThe student ID must contain only numbers\n ");
            }
        }

        s_id = st_id;
    }

    void set_n(const string &n)
    {
        if (!isAlphaOnly(n))
        {
            throw invalid_argument("\nThe name must contain only letters\n");
        }

        name = n;
    }

    void set_f(const string &family)
    {
        if (!isAlphaOnly(family))
        {
            throw invalid_argument("\nThe family name must contain only letters\n");
        }
        f_name = family;
    }

    void set_e(const string &email)
    {
        string gmail = "@gmail.com";

        if (email.length() <= 13 || email.length() > 100)
        {
            throw invalid_argument("\nThe email must contains at least 13 characters including @gmail.com and\n and the email charaters must be less than 100 characters\n");
        }
        if (email.compare(email.length() - 10, 10, gmail, 0, 10) == 0)
        {
            this->email = email;
        }
        else
        {
            throw invalid_argument("\nYou must enter the @gmail.com at the end of your email !\n");
        }
    }

    void set_b(const float money)
    {
        if (money < -555.0f || money > 1000000.00f)
        {
            throw invalid_argument("\nbalance connot be less than -555 or more than 1000000\n");
        }
        balance = money;
    }

    void set_active(const bool a)
    {
        active = a;
    }

    void input()
    {
        while (true) // ID
        {
            cout << "\nEnter the user ID\n";
            if (cin >> u_id)
            {
                try
                {
                    set_u_id(u_id);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                catch (const invalid_argument &e)
                {
                    cout << "\nError\n"
                         << e.what() << endl;
                }
            }
            else
            {
                cin.clear();
                cout << "Invalid input. Please enter numbers only.\n";
            }
        }
        while (true) // STUDENT ID
        {
            cout << "\nEnter the student ID\n";
            getline(cin, s_id);
            try
            {
                set_s_id(s_id);
                break;
            }
            catch (const invalid_argument &e)
            {
                cout << "\nError\n"
                     << e.what() << endl;
            }
        }

        while (true) // STUDENT NAME
        {
            cout << "\nEnter the student name\n";
            getline(cin, name);
            try
            {
                set_n(name);
                break;
            }
            catch (const invalid_argument &e)
            {
                cout << "\nError\n"
                     << e.what() << endl;
            }
        }

        while (true) // STUDENT FAMILY NAME
        {
            cout << "\nEnter the student family\n";
            getline(cin, f_name);
            try
            {
                set_f(f_name);
                break;
            }

            catch (const invalid_argument &e)
            {
                cout << "\nError\n"
                     << e.what() << endl;
            }
        }

        while (true) // STUDENT EAMIAL
        {
            cout << "\nEnter the student email\n";
            getline(cin, email);
            try
            {
                set_e(email);
                break;
            }
            catch (const invalid_argument &e)
            {
                cout << "\nError\n"
                     << e.what() << endl;
            }
        }

        while (true) // STUDENT BALANCE
        {
            cout << "\nEnter the student balance\n";
            if (cin >> balance)
            {
                try
                {
                    set_b(balance);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                catch (const invalid_argument &e)
                {
                    cout << "\nError\n"
                         << e.what() << endl;
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers only.\n";
            }
        }

        while (true) // STUDENT ACTIVITY
        {
            cout << "\nIs the student still active? (1 for yes, 0 for no): ";
            if (cin >> active)
            {
                set_active(active);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter 1 (true) or 0 (false).\n";
            }
        }
    }

    void print() const
    {
        cout << "\nstudent name : " << name;
        cout << "\nstudent family : " << f_name;
        cout << "\nuser ID : " << u_id;
        cout << "\nstudent id : " << s_id;
        cout << "\nemail : " << email;
        cout << "\nbalance : " << balance;
        cout << "\nactivity :" << (active ? "Yes" : "NO");
    }
};

class reservation
{
    int reservation_id;
    student Student;
    diningHall *Hall;
    meal *Meal;
    status condition;
    time_t created_at;

public:
    reservation(int i, const student &s, diningHall *h, meal *m, const status &c, const time_t &t)
    {
        set_reservation_id(i);
        set_student(s);
        set_dinighall(h);
        set_meal(m);
        set_condition(c);
        set_created_at(t);
    }

    reservation()
    {
        reservation_id = 0;
        Student = student();
        Hall = nullptr;
        Meal = nullptr;
        condition = (status ::FAILED);
        created_at = time(nullptr);
    }

    void set_reservation_id(int id)
    {
        if (id >= 001 && id < 732)
        {
            reservation_id = id;
        }
        else
        {
            throw invalid_argument("\nThe reservation ID must be bewteen one and seven hundred and seventy seven");
        }
    }

    void set_student(student s)
    {
        Student = s;
    }

    void set_dinighall(diningHall *h)
    {
        Hall = h;
    }

    void set_meal(meal *m)
    {
        Meal = m;
    }

    void set_condition(status c)
    {
        condition = c;
    }

    void set_created_at(time_t t)
    {
        created_at = t;
    }

    int get_reservation_id() const
    {
        return reservation_id;
    }

    student get_student() const
    {
        return Student;
    }

    diningHall *get_hall() const
    {
        return Hall;
    }

    meal *get_meal() const
    {
        return Meal;
    }

    status get_condtion() const
    {
        return condition;
    }

    int get_time() const
    {
        return created_at;
    }

    void input()
    {

        while (true) // reservation ID
        {
            cout << "\nEnter the reservation ID";
            if (cin >> reservation_id)
            {
                try
                {
                    set_reservation_id(reservation_id);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                catch (const invalid_argument &e)
                {
                    cout << "\nError\n"
                         << e.what() << endl;
                }
            }
            else
            {
                cout << "The reservation ID must be only numbers";
            }
        }

        created_at = time(nullptr);
        
        condition = status::SUCCESS;
    }

    void cancle()
    {
        condition = status::CANCELED;
    }

    string statusToString(status s) const
    {
        switch (s)
        {
        case status::FAILED:
            return "Failed";
        case status::SUCCESS:
            return "Success";
        case status::CANCELED:
            return "Canceled";
        default:
            return "Unknown";
        }
    }

    void print() const
    {
        if (statusToString(condition) == "Success")
        {
            cout << "reservation ID = " << reservation_id << endl;
            Student.print();
            Hall->print();
            Meal->print();
            cout << endl
                 << statusToString(condition);
            struct tm *time = localtime(&created_at);
            cout<<endl<<put_time(time, "%Y/%m/%d %H:%M:%S");
        }
        else
        {
            cout << endl
                 << statusToString(condition);
        }
    }
};