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

class Event : public Entity, public Location
{
private:
    string type;
    string date;
    string time;
    vector<string> ticketTypes;
    vector<Ticket> issuedTickets;

public:
    Event(string t, string d, string tm, const vector<string>& types);
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
    const vector<string>& getTicketTypes() const;
    const vector<Ticket>& getIssuedTickets() const;

    void setType(string t);
    void setDate(string d);
    void setTime(string tm);
    void setTicketTypes(const vector<string>& types);

    void generateTickets();
    bool validateTicket(const string& ticketId);

    void displayEventDetails() const;
    void additionalEventMethod() const;
};

Event::Event(string t, string d, string tm, const vector<string>& types)
    : type(t), date(d), time(tm), ticketTypes(types) {}

Event::Event(const Event& other)
    : type(other.type), date(other.date), time(other.time), ticketTypes(other.ticketTypes), issuedTickets(other.issuedTickets) {}

Event::~Event() {}

Event& Event::operator=(const Event& other)
{
    if (this != &other) {
        type = other.type;
        date = other.date;
        time = other.time;
        ticketTypes = other.ticketTypes;
        issuedTickets = other.issuedTickets;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Event& event)
{
    os << "Event Type: " << event.type << "\n";
    os << "Date: " << event.date << "\n";
    os << "Time: " << event.time << "\n";
    os << "Ticket Types: ";
    for (const string& ticketType : event.ticketTypes)
    {
        os << ticketType << ", ";
    }
    os << "\n";
    os << "Issued Tickets:\n";
    for (const Ticket& ticket : event.issuedTickets)
    {
        os << ticket;
    }
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
    getline(is, event, time);

    cout << "Enter the available ticket types (comma-separated): ";
    event.ticketTypes.clear();
    string types;
    is.ignore();
    getline(is, types);

    size_t pos = 0;
    while ((pos = types.find(',')) != string::npos)
    {
        event.ticketTypes.push_back(types.substr(0, pos));
        types.erase(0, pos + 1);
    }
    event.ticketTypes.push_back(types); // Add the last type

    return is;
}

bool Event::operator==(const Event& other) const
{
    return (type == other.type) && (date == other.date) && (time == other.time) && (ticketTypes == other.ticketTypes) && (issuedTickets == other.issuedTickets);
}

string Event::operator[](int index) const
{
    switch (index) {
    case 0:
        return type;
    case 1:
        return date;
    case 2:
        return time;
    default:
        return "";
    }
}

Event Event::operator+(const Event& other) const
{
    vector<string> combinedTicketTypes = ticketTypes;
    combinedTicketTypes.insert(combinedTicketTypes.end(), other.ticketTypes.begin(), other.ticketTypes.end());
    return Event(type + other.type, date + other.date, time + other.time, combinedTicketTypes);
}

Event Event::operator-(const Event& other) const
{
    return Event(type, date, time, ticketTypes);
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

const vector<string>& Event::getTicketTypes() const
{
    return ticketTypes;
}

const vector<Ticket>& Event::getIssuedTickets() const
{
    return issuedTickets;
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

void Event::setTicketTypes(const vector<string>& types)
{
    ticketTypes = types;
}

void Event::generateTickets()
{
    for (const string& ticketType : ticketTypes)
    {
        issuedTickets.emplace_back(ticketType);
    }
}

bool Event::validateTicket(const string& ticketId)
{
    for (Ticket& ticket : issuedTickets)
    {
        if (ticket.getId() == ticketId)
        {
            ticket.validate();
            return true;
        }
    }
    return false;
}

void Event::displayEventDetails() const
{
    cout << "Event Details:\n";
    cout << *this;
}

void Event::additionalEventMethod() const
{
    cout << "Additional Event Method\n";
}



class Menu
{
public:
    static void displayMainMenu()
    {
        cout << "====== Main Menu ======\n";
        cout << "1. Enter Location Details\n";
        cout << "2. Enter Event Details\n";
        cout << "3. Generate Tickets\n";
        cout << "4. Validate Ticket\n";
        cout << "5. Display Location Details\n";
        cout << "6. Display Event Details\n";
        cout << "0. Exit\n";
    }

    static void executeMainMenu(int choice, Location& location, Event& event)
    {
        switch (choice)
        {
        case 1:
            cin >> location;
            break;
        case 2:
            cin >> event;
            break;
        case 3:
            event.generateTickets();
            break;
        case 4:
            validateTicket(event);
            break;
        case 5:
            location.displayLocationDetails();
            break;
        case 6:
            event.displayEventDetails();
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    static void validateTicket(Event& event)
    {
        cout << "Enter the ticket ID to validate: ";
        string ticketId;
        cin.ignore();
        getline(cin, ticketId);

        if (event.validateTicket(ticketId))
        {
            cout << "Ticket is valid.\n";
        }
        else {
            cout << "Invalid ticket ID.\n";
        }
    }
};



class Ticket
{
private:
    string id;
    string type;
    bool isValid;

public:

    Ticket() : isValid(false) {}

    Ticket(const string& ticketType);
    Ticket(const Ticket& other);
    ~Ticket();
    Ticket& operator=(const Ticket& other);

    friend ostream& operator<<(ostream& os, const Ticket& ticket);

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

    const string& getId() const;
    const string& getType() const;
    bool getIsValid() const;

    void validate();

    void displayTicketDetails() const;
    void additionalTicketMethod() const;
};

Ticket::Ticket(const string& ticketType) : type(ticketType), isValid(false)
{
    // Generate a unique ticket ID
    srand(static_cast<unsigned>(time(nullptr)));
    id = to_string(rand() % 1000000);
}

Ticket::Ticket(const Ticket& other) : id(other.id), type(other.type), isValid(other.isValid) {}

Ticket::~Ticket() {}

Ticket& Ticket::operator=(const Ticket& other)
{
    if (this != &other)
    {
        id = other.id;
        type = other.type;
        isValid = other.isValid;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Ticket& ticket)
{
    os << "Ticket ID: " << ticket.id << "\n";
    os << "Ticket Type: " << ticket.type << "\n";
    os << "Is Valid: " << (ticket.isValid ? "Yes" : "No") << "\n";
    return os;
}

bool Ticket::operator==(const Ticket& other) const
{
    return (id == other.id) && (type == other.type) && (isValid == other.isValid);
}

string Ticket::operator[](int index) const
{
    switch (index) {
    case 0:
        return id;
    case 1:
        return type;
    case 2:
        return isValid ? "Yes" : "No";
    default:
        return "";
    }
}

Ticket Ticket::operator+(const Ticket& other) const
{
    return Ticket(type + other.type);
}

Ticket Ticket::operator-(const Ticket& other) const
{
    return Ticket(type);
}

Ticket Ticket::operator++()
{
    type += "++";
    return *this;
}

Ticket Ticket::operator--()
{
    type += "--";
    return *this;
}

Ticket Ticket::operator++(int)
{
    Ticket temp(*this);
    type += "++";
    return temp;
}

Ticket Ticket::operator--(int)
{
    Ticket temp(*this);
    type += "--";
    return temp;
}

Ticket::operator int() const
{
    return static_cast<int>(type.length());
}

bool Ticket::operator!() const
{
    return type.empty();
}

bool Ticket::operator<(const Ticket& other) const
{
    return (type < other.type);
}

bool Ticket::operator>(const Ticket& other) const
{
    return (type > other.type);
}

bool Ticket::operator<=(const Ticket& other) const
{
    return (type <= other.type);
}

bool Ticket::operator>=(const Ticket& other) const
{
    return (type >= other.type);
}

const string& Ticket::getId() const
{
    return id;
}

const string& Ticket::getType() const
{
    return type;
}

bool Ticket::getIsValid() const
{
    return isValid;
}

void Ticket::validate()
{
    isValid = true;
}

void Ticket::displayTicketDetails() const
{
    cout << "Ticket Details:\n";
    cout << *this;
}

void Ticket::additionalTicketMethod() const
{
    cout << "Additional Ticket Method\n";
}

class TicketManager
{
private:
    vector<Ticket> issuedTickets;

public:
    void saveTicketsToFile(const string& filename)
    {
        ofstream outputFile(filename, ios::binary | ios::out);
        if (!outputFile.is_open())
        {
            cerr << "Error opening the file for saving.\n";
            return;
        }

        for (const Ticket& ticket : issuedTickets)
        {
            outputFile.write(reinterpret_cast<const char*>(&ticket), sizeof(Ticket));
        }

        outputFile.close();
    }

    void loadTicketsFromFile(const string& filename)
    {
        ifstream inputFile(filename, ios::binary | ios::in);
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file for loading.\n";
            return;
        }

        issuedTickets.clear();

        Ticket tempTicket;
        while (inputFile.read(reinterpret_cast<char*>(&tempTicket), sizeof(Ticket)))
        {
            issuedTickets.push_back(tempTicket);
        }

        inputFile.close();
    }
};

int main(int argc, char* argv[])
{
    Location location(0, 0, 0, {});
    Event event("", "", "", {});
    TicketManager ticketManager;

    if (argc == 2)
    {
        string filename(argv[1]);
        ticketManager.loadTicketsFromFile(filename);
    }

    int choice;
    do
    {
        Menu::displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        Menu::executeMainMenu(choice, location, event);
    } while (choice != 0);

    if (argc == 2)
    {
        string filename(argv[1]);
        ticketManager.saveTicketsToFile(filename);
    }

    return 0;
}