#include <iostream>
#include <string>
using namespace std;

class Event {
private:
    string* type;
    string* date;
    string* time;
    string* location;
    const static int MAX_SEATS = 20;
    string seats[MAX_SEATS];

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

    void processAttributes() const;
    void displayAttributes() const;
};

Event::Event() {
    type = new string("");
    date = new string("");
    time = new string("");
    location = new string("");
}

Event::Event(string t, string l, string d, string tm) {
    type = new string(t);
    date = new string(d);
    time = new string(tm);
    location = new string(l);
}

Event::Event(const Event& other) {
    type = new string(*(other.type));
    date = new string(*(other.date));
    time = new string(*(other.time));
    location = new string(*(other.location));
}

Event::~Event() {
    delete type;
    delete date;
    delete time;
    delete location;
}

Event& Event::operator=(const Event& other) {
    if (this != &other) {
        delete type;
        delete date;
        delete time;
        delete location;

        type = new string(*(other.type));
        date = new string(*(other.date));
        time = new string(*(other.time));
        location = new string(*(other.location));
    }
    return *this;
}

ostream& operator<<(ostream& os, const Event& event) {
    os << "Event Type: " << *(event.type) << "\n";
    os << "Date: " << *(event.date) << "\n";
    os << "Time: " << *(event.time) << "\n";
    os << "Location: " << *(event.location) << "\n";
    return os;
}

istream& operator>>(istream& is, Event& event) {
    cout << "Enter the type of the event: ";
    is.ignore();
    getline(is, *event.type);

    cout << "Enter the date of the event (DD-MM-YYYY): ";
    getline(is, *event.date);

    cout << "Enter the time of the event: ";
    getline(is, *event.time);

    cout << "Enter the location of the event: ";
    getline(is, *event.location);

    return is;
}

bool Event::operator==(const Event& other) const {
    return (*type == *(other.type)) && (*date == *(other.date)) &&
        (*time == *(other.time)) && (*location == *(other.location));
}

string Event::operator[](int index) const {
    switch (index) {
    case 0:
        return *type;
    case 1:
        return *date;
    case 2:
        return *time;
    case 3:
        return *location;
    default:
        return "";
    }
}

Event Event::operator+(const Event& other) const {
    return Event(*type + *(other.type), *location + *(other.location),
        *date + *(other.date), *time + *(other.time));
}

Event Event::operator-(const Event& other) const {
    return Event(*type, *location, *date, *time);
}

Event Event::operator++() {
    (*type) += "++";
    return *this;
}

Event Event::operator--() {
    (*type) += "--";
    return *this;
}

Event Event::operator++(int) {
    Event temp(*this);
    (*type) += "++";
    return temp;
}

Event Event::operator--(int) {
    Event temp(*this);
    (*type) += "--";
    return temp;
}

Event::operator int() const {
    return static_cast<int>(type->length());
}

bool Event::operator!() const {
    return type->empty();
}

bool Event::operator<(const Event& other) const {
    return (*type < *(other.type));
}

bool Event::operator>(const Event& other) const {
    return (*type > *(other.type));
}

bool Event::operator<=(const Event& other) const {
    return (*type <= *(other.type));
}

bool Event::operator>=(const Event& other) const {
    return (*type >= *(other.type));
}

int Event::getMaxSeats() const {
    return MAX_SEATS;
}

string Event::getType() const {
    return *type;
}

string Event::getDate() const {
    return *date;
}

string Event::getTime() const {
    return *time;
}

string Event::getLocation() const {
    return *location;
}

void Event::setType(string t) {
    *type = t;
}

void Event::setDate(string d) {
    *date = d;
}

void Event::setTime(string tm) {
    *time = tm;
}

void Event::setLocation(string l) {
    *location = l;
}

void Event::displayEventDetails() const {
    cout << "Event Type: " << *type << "\n";
    cout << "Date(DD-MM-YYYY): " << *date << "\n";
    cout << "Time: " << *time << "\n";
    cout << "Location: " << *location << "\n";
}

void Event::displayEventDetails(ostream& os) const {
    os << "Event Type: " << *type << "\n";
    os << "Date(DD-MM-YYYY): " << *date << "\n";
    os << "Time: " << *time << "\n";
    os << "Location: " << *location << "\n";
}

void Event::processAttributes() const {
    cout << "Processing Event Attributes..." << "\n";
}

void Event::displayAttributes() const {
    cout << "Displaying Event Attributes..." << "\n";
}

int main() {
    Event event1("Concert", "Casa Poporului", "01-01-2020", "10:00");
    cout << "Event 1:\n" << event1 << "\n";

    Event event2;
    cout << "Enter details for Event 2:\n";
    cin >> event2;

    cout << "\nEvent 2:\n" << event2 << "\n";

    Event event3 = event1 + event2;
    cout << "\nEvent 3 (Event 1 + Event 2):\n" << event3 << "\n";

    event3++;
    cout << "\nEvent 3 after incrementing:\n" << event3 << "\n";

    cout << "\nEvent 3 length: " << int(event3) << "\n";

    if (!event1) {
        cout << "\nEvent 1 is empty." << "\n";
    }
    else {
        cout << "\nEvent 1 is not empty." << "\n";
    }

    if (event1 == event2) {
        cout << "\nEvent 1 is equal to Event 2." << "\n";
    }
    else {
        cout << "\nEvent 1 is not equal to Event 2." << "\n";
    }

    cout << "\nMaximum Seats: " << event1.getMaxSeats() << "\n";

    return 0;
}