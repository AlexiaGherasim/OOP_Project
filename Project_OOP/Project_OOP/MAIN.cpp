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