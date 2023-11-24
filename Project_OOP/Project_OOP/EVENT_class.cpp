#include <iostream>
#include <string>
using namespace std;

class Event
{
private:
    string name;
    string date;
    string time;
    string* eventType; // Dynamically defined field
    static const int maxSeats = 200; // Static field representing the maximum number of seats
    int seatsReserved[maxSeats]; // Statically defined array 

public:
    // Constructors
    Event() : name(""), date(""), time(""), eventType(nullptr)
    {
        for (int i = 0; i < maxSeats; ++i)
        {
            seatsReserved[i] = 0;
        }
    }

    Event(string n, string d, string t, string type) : name(n), date(d), time(t)
    {
        if (type.length() > 0)
        {
            eventType = new string(type);
        }
        else
        {
            throw invalid_argument("Event type cannot be empty.");
        }

        for (int i = 0; i < maxSeats; ++i)
        {
            seatsReserved[i] = 0;
        }
    }

    // Copy constructor
    Event(const Event& other) : name(other.name), date(other.date), time(other.time)
    {
        eventType = new string(*(other.eventType));

        for (int i = 0; i < maxSeats; ++i)
        {
            seatsReserved[i] = other.seatsReserved[i];
        }
    }

    // Destructor
    ~Event()
    {
        delete eventType;
    }

    // Overloaded assignment operator
    Event& operator=(const Event& other)
    {
        if (this != &other)
        {
            delete eventType;
            name = other.name;
            date = other.date;
            time = other.time;
            eventType = new string(*(other.eventType));

            for (int i = 0; i < maxSeats; ++i)
            {
                seatsReserved[i] = other.seatsReserved[i];
            }
        }

        return *this;
    }

    // Accessor functions
    string getName() const
    {
        return name;
    }

    void setName(const string& n)
    {
        if (n.length() > 0)
        {
            name = n;
        }
        else
        {
            throw invalid_argument("Name cannot be empty.");
        }
    }

    string getDate() const
    {
        return date;
    }


    string getTime() const
    {
        return time;
    }


    string getEventType() const
    {
        return *eventType;
    }

    void setEventType(const string& type)
    {
        if (type.length() > 0)
        {
            *eventType = type;
        }
        else
        {
            throw invalid_argument("Event type cannot be empty.");
        }
    }

    int getMaxSeats() const
    {
        return maxSeats;
    }

    int getSeatsReserved(int index) const
    {
        if (index >= 0 && index < maxSeats)
        {
            return seatsReserved[index];
        }
        else
        {
            throw out_of_range("Invalid seat index.");
        }
    }

    void setSeatsReserved(int index, int value)
    {
        if (index >= 0 && index < maxSeats)
        {
            seatsReserved[index] = value;
        }
        else
        {
            throw out_of_range("Invalid seat index.");
        }
    }

    // Display
    void displayEventInfo() const
    {
        cout << "Event: " << name << "\nDate: " << date << "\nTime: " << time << "\nType: " << *eventType << endl;
    }

    void displaySeatsReserved() const
    {
        cout << "Seats Reserved: ";
        for (int i = 0; i < maxSeats; ++i)
        {
            cout << seatsReserved[i] << " ";
        }
        cout << endl;
    }

    // Overloaded << and >> operators
    friend ostream& operator<<(ostream& os, const Event& event)
    {
        os << "Event: " << event.name << "\nDate: " << event.date << "\nTime: " << event.time << "\nType: " << *(event.eventType) << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Event& event)
    {
        cout << "Enter Event Name: ";
        is >> event.name;
        cout << "Enter Date: ";
        is >> event.date;
        cout << "Enter Time: ";
        is >> event.time;
        cout << "Enter Event Type: ";
        is >> *(event.eventType);

        return is;
    }

    // Overloaded operators
    bool operator==(const Event& other) const
    {
        return (name == other.name) && (date == other.date) && (time == other.time) && (*eventType == *(other.eventType));
    }

    Event operator+(const Event& other) const
    {
        // Define the behavior of the + operator for Events
        Event result = *this;
        result.name += other.name;
        result.date += other.date;
        result.time += other.time;
        *(result.eventType) += *(other.eventType);

        for (int i = 0; i < maxSeats; ++i)
        {
            result.seatsReserved[i] += other.seatsReserved[i];
        }

        return result;
    }

    // Overloaded [] operator
    int operator[](int index) const
    {
        if (index >= 0 && index < maxSeats)
        {
            return seatsReserved[index];
        }
        else
        {
            throw out_of_range("Invalid seat index.");
        }
    }

    // Overloaded +,- operators
    Event operator++()
    { // Prefix ++
        for (int i = 0; i < maxSeats; ++i) {
            ++seatsReserved[i];
        }
        return *this;
    }

    Event operator--()
    { // Prefix --
        for (int i = 0; i < maxSeats; ++i) {
            --seatsReserved[i];
        }
        return *this;
    }

    Event operator++(int)
    { // Postfix ++
        Event temp = *this;
        for (int i = 0; i < maxSeats; ++i) {
            ++seatsReserved[i];
        }
        return temp;
    }

    Event operator--(int)
    { // Postfix --
        Event temp = *this;
        for (int i = 0; i < maxSeats; ++i) {
            --seatsReserved[i];
        }
        return temp;
    }

};