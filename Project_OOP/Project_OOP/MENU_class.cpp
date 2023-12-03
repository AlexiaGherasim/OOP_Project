#include <iostream>
#include <string>
using namespace std;

class Menu {
private:
    string* date;
    string* time;
    string* name;
    string* location;
    static const int maxAttributes = 4;
    string attributes[maxAttributes];

public:
    Menu();
    Menu(string d, string tm, string n, string l);

    ~Menu();

    Menu& operator=(const Menu& other);
    friend ostream& operator<<(ostream& os, const Menu& menu);
    friend istream& operator>>(istream& is, Menu& menu);
    bool operator==(const Menu& other) const;
    string operator[](int index) const;

    string getDate() const;
    string getTime() const;
    string getName() const;
    string getLocation() const;

    void setDate(string d);
    void setTime(string tm);
    void setName(string n);
    void setLocation(string l);

    void displayMenuDetails() const;
    void displayMenuDetails(ostream& os) const;

    void processAttributes() const;

    void displayAttributes() const;
};

Menu::Menu() {
    date = new string("");
    time = new string("");
    name = new string("");
    location = new string("");
}

Menu::Menu(string d, string tm, string n, string l) {
    date = new string(d);
    time = new string(tm);
    name = new string(n);
    location = new string(l);
}

Menu::~Menu() {
    delete date;
    delete time;
    delete name;
    delete location;
}

Menu& Menu::operator=(const Menu& other) {
    if (this != &other) {
        delete date;
        delete time;
        delete name;
        delete location;

        date = new string(*(other.date));
        time = new string(*(other.time));
        name = new string(*(other.name));
        location = new string(*(other.location));

        for (int i = 0; i < maxAttributes; ++i) {
            attributes[i] = other.attributes[i];
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const Menu& menu) {
    os << "Date: " << *(menu.date) << "\n";
    os << "Time: " << *(menu.time) << "\n";
    os << "Name: " << *(menu.name) << "\n";
    os << "Location: " << *(menu.location) << "\n";

    os << "Attributes:\n";
    for (int i = 0; i < menu.maxAttributes; ++i) {
        os << "Attribute " << i + 1 << ": " << menu.attributes[i] << "\n";
    }

    return os;
}

istream& operator>>(istream& is, Menu& menu) {
    cout << "Enter the date (DD-MM-YYY): ";
    is.ignore();
    getline(is, *menu.date);

    cout << "Enter the time: ";
    getline(is, *menu.time);

    cout << "Enter the name: ";
    getline(is, *menu.name);

    cout << "Enter the location: ";
    getline(is, *menu.location);

    for (int i = 0; i < menu.maxAttributes; ++i) {
        cout << "Enter attribute " << i + 1 << ": ";
        getline(is, menu.attributes[i]);
    }

    return is;
}

bool Menu::operator==(const Menu& other) const {
    return (*date == *(other.date)) && (*time == *(other.time)) &&
        (*name == *(other.name)) && (*location == *(other.location)) &&
        (attributes[0] == other.attributes[0]) &&
        (attributes[1] == other.attributes[1]) &&
        (attributes[2] == other.attributes[2]) &&
        (attributes[3] == other.attributes[3]);
}

string Menu::operator[](int index) const {
    switch (index) {
    case 0:
        return *date;
    case 1:
        return *time;
    case 2:
        return *name;
    case 3:
        return *location;
    default:
        return "";
    }
}

string Menu::getDate() const {
    return *date;
}

string Menu::getTime() const {
    return *time;
}

string Menu::getName() const {
    return *name;
}

string Menu::getLocation() const {
    return *location;
}

void Menu::setDate(string d) {
    *date = d;
}

void Menu::setTime(string tm) {
    *time = tm;
}

void Menu::setName(string n) {
    *name = n;
}

void Menu::setLocation(string l) {
    *location = l;
}

void Menu::displayMenuDetails() const {
    cout << "Date(DD-MM-YYYY): " << *date << "\n";
    cout << "Time: " << *time << "\n";
    cout << "Name: " << *name << "\n";
    cout << "Location: " << *location << "\n";

    cout << "Attributes:\n";
    for (int i = 0; i < maxAttributes; ++i) {
        cout << "Attribute " << i + 1 << ": " << attributes[i] << "\n";
    }
}

void Menu::displayMenuDetails(ostream& os) const {
    os << "Date(DD-MM-YYYY): " << *date << "\n";
    os << "Time: " << *time << "\n";
    os << "Name: " << *name << "\n";
    os << "Location: " << *location << "\n";

    os << "Attributes:\n";
    for (int i = 0; i < maxAttributes; ++i) {
        os << "Attribute " << i + 1 << ": " << attributes[i] << "\n";
    }
}

void Menu::processAttributes() const {
    cout << "Processing Menu Attributes..." << "\n";
    cout << "Processing completed." << "\n";
}

void Menu::displayAttributes() const {
    cout << "Displaying Menu Attributes..." << "\n";
    cout << "Display completed." << "\n";
}

int main() {
    Menu menu1("07-01-2020", "10:00", "Concert", "Casa Poporului");
    cout << "Menu 1\n";
    menu1.displayMenuDetails();
    cout << "\n";

    Menu menu2;
    cout << "Enter details for Menu 2:\n";
    cin >> menu2;

    cout << "\nMenu 2\n";
    menu2.displayMenuDetails();
    cout << "\n";

    Menu menu3 = menu1;
    cout << "\nMenu 3 (Menu 1 copy):\n";
    menu3.displayMenuDetails();
    cout << "\n";

    if (menu1 == menu2) {
        cout << "\nMenu 1 is equal to Menu 2." << "\n";
    }
    else {
        cout << "\nMenu 1 is not equal to Menu 2." << "\n";
    }

    menu3.processAttributes();
    menu3.displayAttributes();

    return 0;
}