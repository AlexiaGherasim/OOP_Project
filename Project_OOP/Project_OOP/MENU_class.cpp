#include <iostream>
#include <string>
using namespace std;

class Menu 
{
private:
    string* name;
    string* location;
    string* date;
    string* time;
    const int MAX_NAME_LENGTH = 50;
    static int menuCount; 

public:
    // Constructors
    Menu();
    Menu(string n, string l, string d, string t);
    Menu(const Menu& other);

    // Destructor
    ~Menu();

    // Overloaded operators
    Menu& operator=(const Menu& other);
    friend ostream& operator<<(ostream& os, const Menu& menu);
    friend istream& operator>>(istream& is, Menu& menu);
    bool operator==(const Menu& other) const;
    string operator[](int index) const;
    Menu operator+(const Menu& other) const;
    Menu operator-(const Menu& other) const;
    Menu operator++(); // Prefix increment
    Menu operator--(); // Prefix decrement
    Menu operator++(int); // Postfix increment
    Menu operator--(int); // Postfix decrement
    explicit operator int() const; // Explicit cast to int
    bool operator!() const; // Negation operator
    bool operator<(const Menu& other) const;
    bool operator>(const Menu& other) const;
    bool operator<=(const Menu& other) const;
    bool operator>=(const Menu& other) const;

    // Accessor functions
    string getName() const;
    string getLocation() const;
    string getDate() const;
    string getTime() const;
    int getMaxNameLength() const; // Accessor for constant field

    // Setter functions
    void setName(string n);
    void setLocation(string l);
    void setDate(string d);
    void setTime(string t);

    // Display functions
    void displayMenu() const;
    void displayMenu(ostream& os) const;

    // Generic processing methods
    void processAttributes() const;
    void displayAttributes() const;

    // Static method
    static int getMenuCount();

    // Exception class for invalid input
    class InvalidInputException : public exception {
    public:
        const char* what() const throw () {
            return "Invalid input for Menu attribute!";
        }
    };
};

int Menu::menuCount = 0;

Menu::Menu() 
{
    name = new string("");
    location = new string("");
    date = new string("");
    time = new string("");
    menuCount++;
}

Menu::Menu(string n, string l, string d, string t) 
{
    name = new string(n);
    location = new string(l);
    date = new string(d);
    time = new string(t);
    menuCount++;
}

Menu::Menu(const Menu& other) 
{
    name = new string(*(other.name));
    location = new string(*(other.location));
    date = new string(*(other.date));
    time = new string(*(other.time));
    menuCount++;
}

Menu::~Menu() 
{
    delete name;
    delete location;
    delete date;
    delete time;
    menuCount--;
}

Menu& Menu::operator=(const Menu& other) 
{
    if (this != &other) {
        delete name;
        delete location;
        delete date;
        delete time;

        name = new string(*(other.name));
        location = new string(*(other.location));
        date = new string(*(other.date));
        time = new string(*(other.time));
    }
    return *this;
}

ostream& operator<<(ostream& os, const Menu& menu) 
{
    os << "Menu Name: " << *(menu.name) << endl;
    os << "Location: " << *(menu.location) << endl;
    os << "Date: " << *(menu.date) << endl;
    os << "Time: " << *(menu.time) << endl;
    return os;
}

istream& operator>>(istream& is, Menu& menu) 
{
    cout << "Enter the name of the event: ";
    is.ignore(); // Ignore any previous newline characters in the input buffer
    getline(is, *menu.name);

    cout << "Enter the location of the event: ";
    getline(is, *menu.location);

    cout << "Enter the date of the event (e.g., YYYY-MM-DD): ";
    getline(is, *menu.date);

    cout << "Enter the time of the event: ";
    getline(is, *menu.time);

    return is;
}

bool Menu::operator==(const Menu& other) const 
{
    return (*name == *(other.name)) && (*location == *(other.location)) &&
        (*date == *(other.date)) && (*time == *(other.time));
}

string Menu::operator[](int index) const 
{
    switch (index) {
    case 0:
        return *name;
    case 1:
        return *location;
    case 2:
        return *date;
    case 3:
        return *time;
    default:
        return "";
    }
}

Menu Menu::operator+(const Menu& other) const 
{
    return Menu(*name + *(other.name), *location + *(other.location),
        *date + *(other.date), *time + *(other.time));
}

Menu Menu::operator-(const Menu& other) const 
{
    return Menu(*name, *location, *date, *time); // Ignoring subtraction for strings
}

Menu Menu::operator++() 
{
    (*name) += "++";
    return *this;
}

Menu Menu::operator--() 
{
    (*name) += "--";
    return *this;
}

Menu Menu::operator++(int) 
{
    Menu temp(*this);
    (*name) += "++";
    return temp;
}

Menu Menu::operator--(int) 
{
    Menu temp(*this);
    (*name) += "--";
    return temp;
}

Menu::operator int() const 
{
    return static_cast<int>(name->length());
}

bool Menu::operator!() const 
{
    return name->empty();
}

bool Menu::operator<(const Menu& other) const 
{
    return (*name < *(other.name));
}

bool Menu::operator>(const Menu& other) const 
{
    return (*name > *(other.name));
}

bool Menu::operator<=(const Menu& other) const 
{
    return (*name <= *(other.name));
}

bool Menu::operator>=(const Menu& other) const 
{
    return (*name >= *(other.name));
}

int Menu::getMenuCount() 
{
    return menuCount;
}

string Menu::getName() const 
{
    return *name;
}

string Menu::getLocation() const 
{
    return *location;
}

string Menu::getDate() const 
{
    return *date;
}

string Menu::getTime() const 
{
    return *time;
}

int Menu::getMaxNameLength() const 
{
    return MAX_NAME_LENGTH;
}

void Menu::setName(string n) 
{
    if (n.length() <= MAX_NAME_LENGTH) {
        *name = n;
    }
    else {
        throw InvalidInputException();
    }
}

void Menu::setLocation(string l) 
{
    *location = l;
}

void Menu::setDate(string d) 
{
    *date = d;
}

void Menu::setTime(string t) 
{
    *time = t;
}

void Menu::displayMenu() const 
{
    cout << "Menu Name: " << *name << endl;
    cout << "Location: " << *location << endl;
    cout << "Date: " << *date << endl;
    cout << "Time: " << *time << endl;
}

void Menu::displayMenu(ostream& os) const 
{
    os << "Menu Name: " << *name << endl;
    os << "Location: " << *location << endl;
    os << "Date: " << *date << endl;
    os << "Time: " << *time << endl;
}

void Menu::processAttributes() const 
{
    cout << "Processing Menu Attributes..." << endl;
   
}

void Menu::displayAttributes() const 
{
    cout << "Displaying Menu Attributes..." << endl;
    
}
