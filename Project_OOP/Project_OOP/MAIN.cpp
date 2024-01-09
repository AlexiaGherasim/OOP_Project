#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Entity
{
public:
    virtual void process() const = 0;
    virtual ~Entity() {}
};

class Location
{
private:
    int maxSeats;
    int numRows;
    int numZones;
    vector<int> seatsPerRow;

public:
    Location(int max, int rows, int zones, const vector<int>& seats);
    Location(const Location& other);
    ~Location();
    Location& operator=(const Location& other);

    friend ostream& operator<<(ostream& os, const Location& location);
    friend istream& operator>>(istream& is, Location& location);

    bool operator==(const Location& other) const;
    int operator[](int index) const;
    Location operator+(const Location& other) const;
    Location operator-(const Location& other) const;
    Location operator++();
    Location operator--();
    Location operator++(int);
    Location operator--(int);
    explicit operator int() const;
    bool operator!() const;
    bool operator<(const Location& other) const;
    bool operator>(const Location& other) const;
    bool operator<=(const Location& other) const;
    bool operator>=(const Location& other) const;

    int getMaxSeats() const;
    int getNumRows() const;
    int getNumZones() const;
    const vector<int>& getSeatsPerRow() const;

    void setMaxSeats(int max);
    void setNumRows(int rows);
    void setNumZones(int zones);
    void setSeatsPerRow(const vector<int>& seats);

    void displayLocationDetails() const;
    virtual void additionalLocationMethod() const;
};

Location::Location(int max, int rows, int zones, const vector<int>& seats)
    : maxSeats(max), numRows(rows), numZones(zones), seatsPerRow(seats) {}

Location::Location(const Location& other)
    : maxSeats(other.maxSeats), numRows(other.numRows), numZones(other.numZones), seatsPerRow(other.seatsPerRow) {}

Location::~Location() {}

Location& Location::operator=(const Location& other)
{
    if (this != &other)
    {
        maxSeats = other.maxSeats;
        numRows = other.numRows;
        numZones = other.numZones;
        seatsPerRow = other.seatsPerRow;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Location& location)
{
    os << "Max Seats: " << location.maxSeats << "\n";
    os << "Num Rows: " << location.numRows << "\n";
    os << "Num Zones: " << location.numZones << "\n";
    os << "Seats per Row: ";
    for (int seats : location.seatsPerRow)
    {
        os << seats << ", ";
    }
    os << "\n";
    return os;
}

istream& operator>>(istream& is, Location& location)
{
    cout << "Enter the maximum number of seats: ";
    is >> location.maxSeats;

    cout << "Enter the number of rows: ";
    is >> location.numRows;

    cout << "Enter the number of zones: ";
    is >> location.numZones;

    cout << "Enter the seats per row (comma-separated): ";
    location.seatsPerRow.clear();
    string seats;
    is.ignore();
    getline(is, seats);

    size_t pos = 0;
    while ((pos = seats.find(',')) != string::npos)
    {
        int seat = stoi(seats.substr(0, pos));
        location.seatsPerRow.push_back(seat);
        seats.erase(0, pos + 1);
    }
    location.seatsPerRow.push_back(stoi(seats));

    return is;
}

bool Location::operator==(const Location& other) const
{
    return (maxSeats == other.maxSeats) && (numRows == other.numRows) && (numZones == other.numZones) && (seatsPerRow == other.seatsPerRow);
}

int Location::operator[](int index) const
{
    if (index >= 0 && index < seatsPerRow.size())
    {
        return seatsPerRow[index];
    }
    return -1;
}

Location Location::operator+(const Location& other) const
{
    vector<int> combinedSeatsPerRow = seatsPerRow;
    combinedSeatsPerRow.insert(combinedSeatsPerRow.end(), other.seatsPerRow.begin(), other.seatsPerRow.end());
    return Location(maxSeats + other.maxSeats, numRows + other.numRows, numZones + other.numZones, combinedSeatsPerRow);
}

Location Location::operator-(const Location& other) const
{
    return Location(maxSeats, numRows, numZones, seatsPerRow);
}

Location Location::operator++()
{
    maxSeats++;
    numRows++;
    numZones++;
    for (int& seats : seatsPerRow)
    {
        seats++;
    }
    return *this;
}

Location Location::operator--()
{
    maxSeats--;
    numRows--;
    numZones--;
    for (int& seats : seatsPerRow)
    {
        seats--;
    }
    return *this;
}

Location Location::operator++(int)
{
    Location temp(*this);
    maxSeats++;
    numRows++;
    numZones++;
    for (int& seats : seatsPerRow)
    {
        seats++;
    }
    return temp;
}

Location Location::operator--(int)
{
    Location temp(*this);
    maxSeats--;
    numRows--;
    numZones--;
    for (int& seats : seatsPerRow)
    {
        seats--;
    }
    return temp;
}

Location::operator int() const
{
    return static_cast<int>(maxSeats);
}

bool Location::operator!() const
{
    return maxSeats == 0;
}

bool Location::operator<(const Location& other) const
{
    return maxSeats < other.maxSeats;
}

bool Location::operator>(const Location& other) const
{
    return maxSeats > other.maxSeats;
}

bool Location::operator<=(const Location& other) const
{
    return maxSeats <= other.maxSeats;
}

bool Location::operator>=(const Location& other) const
{
    return maxSeats >= other.maxSeats;
}

int Location::getMaxSeats() const
{
    return maxSeats;
}

int Location::getNumRows() const
{
    return numRows;
}

int Location::getNumZones() const
{
    return numZones;
}

const vector<int>& Location::getSeatsPerRow() const
{
    return seatsPerRow;
}

void Location::setMaxSeats(int max)
{
    maxSeats = max;
}

void Location::setNumRows(int rows)
{
    numRows = rows;
}

void Location::setNumZones(int zones)
{
    numZones = zones;
}

void Location::setSeatsPerRow(const vector<int>& seats)
{
    seatsPerRow = seats;
}

void Location::displayLocationDetails() const
{
    cout << "Location Details:\n";
    cout << *this;
}

void Location::additionalLocationMethod() const
{
    cout << "Additional Location Method\n";
}

class Event : public Entity
{
private:
    string type;
    string date;
    string time;
    string location;
    const static int MAX_SEATS = 20;
    string seats[MAX_SEATS];
    vector<string> performers;

public:
    Event();
    Event(string t, string l, string d, string tm);
    Event(const Event& other);

    ~Event();

    Event& operator=(const Event& other);
    friend ostream& operator<<(ostream& os, const Event& event);
    friend istream& operator>>(istream& is, Event& event);
    bool operator==(const Event& other) const;
    string operator[](int index) const;
    Event operator+(const Event& other) const;
    Event operator-(const Event& other) const;
    Event operator++();
    Event operator--();
    Event operator++(int);
    Event operator--(int);
    explicit operator int() const;
    bool operator!() const;
    bool operator<(const Event& other) const;
    bool operator>(const Event& other) const;
    bool operator<=(const Event& other) const;
    bool operator>=(const Event& other) const;

    string getType() const;
    string getDate() const;
    string getTime() const;
    string getLocation() const;
    int getMaxSeats() const;

    void setType(string t);
    void setDate(string d);
    void setTime(string tm);
    void setLocation(string l);

    void displayEventDetails() const;
    void displayEventDetails(ostream& os) const;

    void process() const override;

    void setPerformers(const vector<string>& p)
    {
        performers = p;
    }

    const vector<string>& getPerformers() const
    {
        return performers;
    }
};

Event::Event() : type(""), date(""), time(""), location("") {}

Event::Event(string t, string l, string d, string tm) : type(t), location(l), date(d), time(tm) {}

Event::Event(const Event& other) : type(other.type), location(other.location), date(other.date), time(other.time) {}

Event::~Event() {}

Event& Event::operator=(const Event& other)
{
    if (this != &other)
    {
        type = other.type;
        location = other.location;
        date = other.date;
        time = other.time;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Event& event)
{
    os << "Event Type: " << event.type << "\n";
    os << "Date: " << event.date << "\n";
    os << "Time: " << event.time << "\n";
    os << "Location: " << event.location << "\n";
    return os;
}

istream& operator>>(istream& is, Event& event)
{
    cout << "Enter the type of the event: ";
    is.ignore();
    getline(is, event.type);

    cout << "Enter the date of the event (DD-MM-YYYY): ";
    getline(is, event.date);

    cout << "Enter the time of the event: ";
    getline(is, event.time);

    cout << "Enter the location of the event: ";
    getline(is, event.location);

    return is;
}

bool Event::operator==(const Event& other) const
{
    return (type == other.type) && (date == other.date) && (time == other.time) && (location == other.location);
}

string Event::operator[](int index) const
{
    switch (index)
    {
    case 0:
        return type;
    case 1:
        return date;
    case 2:
        return time;
    case 3:
        return location;
    default:
        return "";
    }
}

Event Event::operator+(const Event& other) const
{
    return Event(type + other.type, location + other.location, date + other.date, time + other.time);
}

Event Event::operator-(const Event& other) const
{
    return Event(type, location, date, time);
}

Event Event::operator++()
{
    type += "++";
    return *this;
}

Event Event::operator--()
{
    type += "--";
    return *this;
}

Event Event::operator++(int)
{
    Event temp(*this);
    type += "++";
    return temp;
}

Event Event::operator--(int)
{
    Event temp(*this);
    type += "--";
    return temp;
}

Event::operator int() const
{
    return static_cast<int>(type.length());
}

bool Event::operator!() const
{
    return type.empty();
}

bool Event::operator<(const Event& other) const
{
    return (type < other.type);
}

bool Event::operator>(const Event& other) const
{
    return (type > other.type);
}

bool Event::operator<=(const Event& other) const
{
    return (type <= other.type);
}

bool Event::operator>=(const Event& other) const
{
    return (type >= other.type);
}

int Event::getMaxSeats() const
{
    return MAX_SEATS;
}

string Event::getType() const
{
    return type;
}

string Event::getDate() const
{
    return date;
}

string Event::getTime() const
{
    return time;
}

string Event::getLocation() const
{
    return location;
}

void Event::setType(string t)
{
    type = t;
}

void Event::setDate(string d)
{
    date = d;
}

void Event::setTime(string tm)
{
    time = tm;
}

void Event::setLocation(string l)
{
    location = l;
}

void Event::displayEventDetails() const
{
    cout << "Event Type: " << type << "\n";
    cout << "Date(DD-MM-YYYY): " << date << "\n";
    cout << "Time: " << time << "\n";
    cout << "Location: " << location << "\n";
}

void Event::displayEventDetails(ostream& os) const
{
    os << "Event Type: " << type << "\n";
    os << "Date(DD-MM-YYYY): " << date << "\n";
    os << "Time: " << time << "\n";
    os << "Location: " << location << "\n";
}



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



class Ticket {
private:
    string* type;
    string* seat;
    string* time;
    string* name;
    string* date;
    string* location;
    int id;

public:
    Ticket();
    Ticket(string t, string s, string tm, string n, string d, string l);
    Ticket(const Ticket& other);

    ~Ticket();

    Ticket& operator=(const Ticket& other);
    friend ostream& operator<<(ostream& os, const Ticket& ticket);
    friend istream& operator>>(istream& is, Ticket& ticket);
    bool operator==(const Ticket& other) const;
    string operator[](int index) const;
    Ticket operator+(const Ticket& other) const;
    Ticket operator-(const Ticket& other) const;
    Ticket operator++();
    Ticket operator--();
    Ticket operator++(int);
    Ticket operator--(int);
    explicit operator int() const;
    bool operator!() const;
    bool operator<(const Ticket& other) const;
    bool operator>(const Ticket& other) const;
    bool operator<=(const Ticket& other) const;
    bool operator>=(const Ticket& other) const;

    string getType() const;
    string getSeat() const;
    string getTime() const;
    string getName() const;
    string getDate() const;
    string getLocation() const;
    int getID() const;

    void setType(string t);
    void setSeat(string s);
    void setTime(string tm);
    void setName(string n);
    void setDate(string d);
    void setLocation(string l);

    void displayTicketDetails() const;
    void displayTicketDetails(ostream& os) const;

    void processAttributes() const;

    void displayAttributes() const;

    static int generateUniqueID();
};

int Ticket::generateUniqueID() {
    return rand();
}

Ticket::Ticket() {
    type = new string("");
    seat = new string("");
    time = new string("");
    name = new string("");
    date = new string("");
    location = new string("");
    id = generateUniqueID();
}

Ticket::Ticket(string t, string s, string tm, string n, string d, string l) {
    type = new string(t);
    seat = new string(s);
    time = new string(tm);
    name = new string(n);
    date = new string(d);
    location = new string(l);
    id = generateUniqueID();
}

Ticket::Ticket(const Ticket& other) {
    type = new string(*(other.type));
    seat = new string(*(other.seat));
    time = new string(*(other.time));
    name = new string(*(other.name));
    date = new string(*(other.date));
    location = new string(*(other.location));
    id = other.id;
}

Ticket::~Ticket() {
    delete type;
    delete seat;
    delete time;
    delete name;
    delete date;
    delete location;
}

Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) {
        delete type;
        delete seat;
        delete time;
        delete name;
        delete date;
        delete location;

        type = new string(*(other.type));
        seat = new string(*(other.seat));
        time = new string(*(other.time));
        name = new string(*(other.name));
        date = new string(*(other.date));
        location = new string(*(other.location));
        id = other.id;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Ticket& ticket) {
    os << "Ticket ID: " << ticket.id << "\n";
    os << "Type: " << *(ticket.type) << "\n";
    os << "Seat: " << *(ticket.seat) << "\n";
    os << "Time: " << *(ticket.time) << "\n";
    os << "Name: " << *(ticket.name) << "\n";
    os << "Date: " << *(ticket.date) << "\n";
    os << "Location: " << *(ticket.location) << "\n";
    return os;
}

istream& operator>>(istream& is, Ticket& ticket) {
    cout << "Enter the type of the ticket: ";
    is.ignore();
    getline(is, *ticket.type);

    cout << "Enter the seat number: ";
    getline(is, *ticket.seat);

    cout << "Enter the time of the event: ";
    getline(is, *ticket.time);

    cout << "Enter the name on the ticket: ";
    getline(is, *ticket.name);

    cout << "Enter the date of the event (DD-MM-YYYY): ";
    getline(is, *ticket.date);

    cout << "Enter the location of the event: ";
    getline(is, *ticket.location);

    ticket.id = Ticket::generateUniqueID();
    return is;
}

bool Ticket::operator==(const Ticket& other) const {
    return (*type == *(other.type)) && (*seat == *(other.seat)) &&
        (*time == *(other.time)) && (*name == *(other.name)) &&
        (*date == *(other.date)) && (*location == *(other.location)) &&
        (id == other.id);
}

string Ticket::operator[](int index) const {
    switch (index) {
    case 0:
        return *type;
    case 1:
        return *seat;
    case 2:
        return *time;
    case 3:
        return *name;
    case 4:
        return *date;
    case 5:
        return *location;
    default:
        return "";
    }
}

Ticket Ticket::operator+(const Ticket& other) const {
    return Ticket(*type + *(other.type), *seat + *(other.seat),
        *time + *(other.time), *name + *(other.name),
        *date + *(other.date), *location + *(other.location));
}

Ticket Ticket::operator-(const Ticket& other) const {
    return Ticket(*type, *seat, *time, *name, *date, *location);
}

Ticket Ticket::operator++() {
    (*type) += "++";
    return *this;
}

Ticket Ticket::operator--() {
    (*type) += "--";
    return *this;
}

Ticket Ticket::operator++(int) {
    Ticket temp(*this);
    (*type) += "++";
    return temp;
}

Ticket Ticket::operator--(int) {
    Ticket temp(*this);
    (*type) += "--";
    return temp;
}

Ticket::operator int() const {
    return id;
}

bool Ticket::operator!() const {
    return type->empty();
}

bool Ticket::operator<(const Ticket& other) const {
    return (id < other.id);
}

bool Ticket::operator>(const Ticket& other) const {
    return (id > other.id);
}

bool Ticket::operator<=(const Ticket& other) const {
    return (id <= other.id);
}

bool Ticket::operator>=(const Ticket& other) const {
    return (id >= other.id);
}

string Ticket::getType() const {
    return *type;
}

string Ticket::getSeat() const {
    return *seat;
}

string Ticket::getTime() const {
    return *time;
}

string Ticket::getName() const {
    return *name;
}

string Ticket::getDate() const {
    return *date;
}

string Ticket::getLocation() const {
    return *location;
}

int Ticket::getID() const {
    return id;
}

void Ticket::setType(string t) {
    *type = t;
}

void Ticket::setSeat(string s)
{
    *seat = s;
}

void Ticket::setTime(string tm)
{
    *time = tm;
}

void Ticket::setName(string n)
{
    *name = n;
}

void Ticket::setDate(string d)
{
    *date = d;
}

void Ticket::setLocation(string l)
{
    *location = l;
}

void Ticket::displayTicketDetails() const
{
    cout << "Ticket ID: " << id << "\n";
    cout << "Type: " << *type << "\n";
    cout << "Seat: " << *seat << "\n";
    cout << "Time: " << *time << "\n";
    cout << "Name: " << *name << "\n";
    cout << "Date: " << *date << "\n";
    cout << "Location: " << *location << "\n";
}

void Ticket::displayTicketDetails(ostream& os) const
{
    os << "Ticket ID: " << id << "\n";
    os << "Type: " << *type << "\n";
    os << "Seat: " << *seat << "\n";
    os << "Time: " << *time << "\n";
    os << "Name: " << *name << "\n";
    os << "Date: " << *date << "\n";
    os << "Location: " << *location << "\n";
}

void Ticket::processAttributes() const
{
    cout << "Processing Ticket Attributes..." << "\n";
    cout << "Processing completed." << "\n";
}

void Ticket::displayAttributes() const
{
    cout << "Displaying Ticket Attributes..." << endl;
    cout << "Display completed." << endl;
}

int main()
{
    Menu menu1("02-02-2020", "19:00", "Concert", "Casa Poporului");
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

    if (menu1 == menu2)
    {
        cout << "\nMenu 1 is equal to Menu 2." << "\n";
    }
    else {
        cout << "\nMenu 1 is not equal to Menu 2." << "\n";
    }

    menu3.processAttributes();
    menu3.displayAttributes();

    cout << "\n-----------------------------\n";

    Event event1("Rock", "Concert", "09:00", "Casa Poporului");
    cout << "Event 1:\n";
    event1.displayEventDetails();
    cout << "\n";

    Event event2;
    cout << "Enter details for Event 2:\n";
    cin >> event2;

    cout << "\nEvent 2:\n";
    event2.displayEventDetails();
    cout << "\n";

    Event event3 = event1;
    cout << "\nEvent 3 (Event 1 copy):\n";
    event3.displayEventDetails();
    cout << "\n";

    if (event1 == event2)
    {
        cout << "\nEvent 1 is equal to Event 2." << "\n";
    }
    else {
        cout << "\nEvent 1 is not equal to Event 2." << "\n";
    }

    event3.processAttributes();
    event3.displayAttributes();

    cout << "\n-----------------------------\n";

    Ticket ticket1("VIP", "09", "10:00", "Maria Elena", "01-01-2020", "Casa Poporului");
    cout << "Ticket 1:\n";
    ticket1.displayTicketDetails();
    cout << "\n";

    Ticket ticket2;
    cout << "Enter details for Ticket 2:\n";
    cin >> ticket2;

    cout << "\nTicket 2:\n";
    ticket2.displayTicketDetails();
    cout << "\n";

    Ticket ticket3 = ticket1 + ticket2;
    cout << "\nTicket 3 (Ticket 1 + Ticket 2):\n";
    ticket3.displayTicketDetails();
    cout << "\n";

    ticket3++;
    cout << "\nTicket 3 after incrementing:\n";
    ticket3.displayTicketDetails();
    cout << "\n";

    cout << "\nTicket 3 ID: " << int(ticket3) << "\n";

    if (!ticket1)
    {
        cout << "\nTicket 1 is empty." << "\n";
    }
    else {
        cout << "\nTicket 1 is not empty." << "\n";
    }

    if (ticket1 == ticket2) {
        cout << "\nTicket 1 is equal to Ticket 2." << "\n";
    }
    else {
        cout << "\nTicket 1 is not equal to Ticket 2." << "\n";
    }

    ticket3.processAttributes();
    ticket3.displayAttributes();

    return 0;
}