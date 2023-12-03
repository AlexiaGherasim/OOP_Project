#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

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

void Ticket::setSeat(string s) {
    *seat = s;
}

void Ticket::setTime(string tm) {
    *time = tm;
}

void Ticket::setName(string n) {
    *name = n;
}

void Ticket::setDate(string d) {
    *date = d;
}

void Ticket::setLocation(string l) {
    *location = l;
}

void Ticket::displayTicketDetails() const {
    cout << "Ticket ID: " << id << "\n";
    cout << "Type: " << *type << "\n";
    cout << "Seat: " << *seat << "\n";
    cout << "Time: " << *time << "\n";
    cout << "Name: " << *name << "\n";
    cout << "Date: " << *date << "\n";
    cout << "Location: " << *location << "\n";
}

void Ticket::displayTicketDetails(ostream& os) const {
    os << "Ticket ID: " << id << "\n";
    os << "Type: " << *type << "\n";
    os << "Seat: " << *seat << "\n";
    os << "Time: " << *time << "\n";
    os << "Name: " << *name << "\n";
    os << "Date: " << *date << "\n";
    os << "Location: " << *location << "\n";
}

void Ticket::processAttributes() const {
    cout << "Processing Ticket Attributes..." << "\n";
    cout << "Processing completed." << "\n";
}

void Ticket::displayAttributes() const {
    cout << "Displaying Ticket Attributes..." << endl;
    cout << "Display completed." << endl;
}