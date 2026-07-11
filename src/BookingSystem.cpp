#include "../include/BookingSystem.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//-----------------------------------------------------
// Constructor
//-----------------------------------------------------

BookingSystem::BookingSystem()
    : head(nullptr),
      nextBookingID(1001),
      totalBookings(0),
      cancelledBookings(0),
      totalRevenue(0),
      fileManager("data/bookings.txt", "data/movies.txt")
{
    initializeMovies();
    initializeScreens();
    loadData();
}

//-----------------------------------------------------

BookingSystem::~BookingSystem()
{
    saveData();

    Ticket *temp;

    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

//-----------------------------------------------------

void BookingSystem::initializeMovies()
{
    if (!movies.empty())
        return;

    Movie m1(101, "Kalki 2898 AD", "Sci-Fi",
             "Telugu", "Nag Ashwin", 181, 250);

    m1.addShowTime("10:00 AM");
    m1.addShowTime("2:00 PM");
    m1.addShowTime("6:00 PM");

    Movie m2(102, "Pushpa 2", "Action",
             "Telugu", "Sukumar", 195, 300);

    m2.addShowTime("9:00 AM");
    m2.addShowTime("1:00 PM");
    m2.addShowTime("7:00 PM");

    Movie m3(103, "Interstellar", "Sci-Fi",
             "English", "Christopher Nolan", 169, 350);

    m3.addShowTime("11:00 AM");
    m3.addShowTime("3:00 PM");
    m3.addShowTime("8:00 PM");

    movies.push_back(m1);
    movies.push_back(m2);
    movies.push_back(m3);
}

//-----------------------------------------------------

void BookingSystem::initializeScreens()
{
    screens.push_back(Screen(1));
    screens.push_back(Screen(2));
    screens.push_back(Screen(3));
}

//-----------------------------------------------------

void BookingSystem::displayMovies()
{
    cout << "\n========== MOVIES ==========\n";

    for (const auto &movie : movies)
    {
        movie.displayMovie();
        cout << "---------------------------\n";
    }
}

//-----------------------------------------------------

void BookingSystem::displayScreens()
{
    cout << "\n======= SCREENS =======\n";

    for (const auto &screen : screens)
    {
        cout << "Screen : "
             << screen.getScreenNumber()
             << " ("
             << screen.getRows()
             << " x "
             << screen.getColumns()
             << ")" << endl;
    }
}

//-----------------------------------------------------

bool BookingSystem::adminLogin()
{
    string user, pass;

    cout << "\nAdmin Username : ";
    cin >> user;

    cout << "Password : ";
    cin >> pass;

    return user == "admin" && pass == "1234";
}

//-----------------------------------------------------

void BookingSystem::mainMenu()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << " MOVIE TICKET BOOKING SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Customer\n";
        cout << "2. Admin\n";
        cout << "3. Exit\n";

        cout << "\nEnter Choice : ";

        cin >> choice;

        switch (choice)
        {
        case 1:

            cout << "\n------ Customer Menu ------\n";

            cout << "1. Book Ticket\n";
            cout << "2. Display Tickets\n";
            cout << "3. Search by Booking ID\n";
            cout << "4. Search by Customer\n";
            cout << "5. Search by Movie\n";
            cout << "6. Update Ticket\n";
            cout << "7. Cancel Ticket\n";
            cout << "8. Revenue Report\n";
            cout << "9. Booking Statistics\n";
            cout << "0. Back\n";

            int ch;

            cin >> ch;

            switch (ch)
            {
            case 1:
                bookTicket();
                break;
            case 2:
                displayAllTickets();
                break;
            case 3:
                searchByBookingID();
                break;
            case 4:
                searchByCustomerName();
                break;
            case 5:
                searchByMovieName();
                break;
            case 6:
                updateTicket();
                break;
            case 7:
                cancelTicket();
                break;
            case 8:
                revenueReport();
                break;
            case 9:
                bookingStatistics();
                break;
            }

            break;

        case 2:

            if (adminLogin())
                adminMenu();
            else
                cout << "\nInvalid Login.\n";

            break;

        case 3:

            saveData();

            cout << "\nThank You.\n";

            break;

        default:

            cout << "\nInvalid Choice\n";
        }

    } while (choice != 3);
}
//-----------------------------------------------------
// Check Seat Availability
//-----------------------------------------------------

bool BookingSystem::isSeatAvailable(int movieID,
                                    int screenNo,
                                    const string &date,
                                    const string &time,
                                    const string &seat)
{
    Ticket *temp = head;

    while (temp != nullptr)
    {
        if (temp->movieID == movieID &&
            temp->screenNumber == screenNo &&
            temp->bookingDate == date &&
            temp->showTime == time &&
            temp->seatNumber == seat &&
            !temp->isCancelled)
        {
            return false;
        }

        temp = temp->next;
    }

    return true;
}

//-----------------------------------------------------
// Display Seat Layout
//-----------------------------------------------------

void BookingSystem::displaySeatLayout(int movieID,
                                      int screenNo,
                                      const string &date,
                                      const string &time)
{
    cout << "\n========== SEAT LAYOUT ==========\n";

    for (char row = 'A'; row <= 'J'; row++)
    {
        for (int col = 1; col <= 10; col++)
        {
            string seat = string(1, row) + to_string(col);

            if (isSeatAvailable(movieID, screenNo, date, time, seat))
                cout << setw(5) << seat;
            else
                cout << setw(5) << "XX";
        }

        cout << endl;
    }

    cout << "\nXX = Booked Seat\n";
}

//-----------------------------------------------------
// Book Ticket
//-----------------------------------------------------

void BookingSystem::bookTicket()
{
    displayMovies();

    int movieID;

    cout << "\nMovie ID : ";
    cin >> movieID;

    Movie *selectedMovie = nullptr;

    for (auto &m : movies)
    {
        if (m.getMovieID() == movieID)
        {
            selectedMovie = &m;
            break;
        }
    }

    if (selectedMovie == nullptr)
    {
        cout << "\nInvalid Movie.\n";
        return;
    }

    string customer;

    cin.ignore();

    cout << "Customer Name : ";
    getline(cin, customer);

    int screen;

    displayScreens();

    cout << "Screen Number : ";
    cin >> screen;

    vector<string> shows = selectedMovie->getShowTimes();

    cout << "\nAvailable Shows\n";

    for (size_t i = 0; i < shows.size(); i++)
        cout << i + 1 << ". " << shows[i] << endl;

    int option;

    cout << "Choose Show : ";
    cin >> option;

    if (option < 1 || option > shows.size())
    {
        cout << "\nInvalid Show.\n";
        return;
    }

    string show = shows[option - 1];

    cin.ignore();

    string date;

    cout << "Booking Date : ";
    getline(cin, date);

    displaySeatLayout(movieID,
                      screen,
                      date,
                      show);

    string seat;

    cout << "\nSeat Number : ";
    getline(cin, seat);

    if (!isSeatAvailable(movieID,
                         screen,
                         date,
                         show,
                         seat))
    {
        cout << "\nSeat Already Booked.\n";
        return;
    }

    Ticket *ticket = new Ticket(
        nextBookingID++,
        movieID,
        customer,
        selectedMovie->getMovieName(),
        screen,
        date,
        show,
        seat,
        selectedMovie->getTicketPrice());

    ticket->next = nullptr;

    if (head == nullptr)
    {
        head = ticket;
    }
    else
    {
        Ticket *temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = ticket;
    }

    totalBookings++;

    totalRevenue += ticket->ticketPrice;

    cout << "\n=============================\n";
    cout << "Booking Successful\n";
    cout << "=============================\n";

    ticket->displayTicket();

    saveData();
}

//-----------------------------------------------------
// Display All Tickets
//-----------------------------------------------------

void BookingSystem::displayAllTickets()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings Found.\n";
        return;
    }

    Ticket *temp = head;

    while (temp != nullptr)
    {
        temp->displayTicket();

        cout << "-----------------------------\n";

        temp = temp->next;
    }
}
//-----------------------------------------------------
// Search By Booking ID
//-----------------------------------------------------

void BookingSystem::searchByBookingID()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings Found.\n";
        return;
    }

    int id;

    cout << "\nEnter Booking ID : ";
    cin >> id;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        if (temp->bookingID == id)
        {
            temp->displayTicket();
            return;
        }

        temp = temp->next;
    }

    cout << "\nBooking Not Found.\n";
}

//-----------------------------------------------------
// Search By Customer Name
//-----------------------------------------------------

void BookingSystem::searchByCustomerName()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings Found.\n";
        return;
    }

    cin.ignore();

    string name;

    cout << "\nCustomer Name : ";

    getline(cin, name);

    Ticket *temp = head;

    bool found = false;

    while (temp != nullptr)
    {
        if (temp->customerName == name)
        {
            temp->displayTicket();
            found = true;
        }

        temp = temp->next;
    }

    if (!found)
        cout << "\nNo Booking Found.\n";
}

//-----------------------------------------------------
// Search By Movie Name
//-----------------------------------------------------

void BookingSystem::searchByMovieName()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings Found.\n";
        return;
    }

    cin.ignore();

    string movie;

    cout << "\nMovie Name : ";

    getline(cin, movie);

    Ticket *temp = head;

    bool found = false;

    while (temp != nullptr)
    {
        if (temp->movieName == movie)
        {
            temp->displayTicket();
            found = true;
        }

        temp = temp->next;
    }

    if (!found)
        cout << "\nNo Booking Found.\n";
}

//-----------------------------------------------------
// Update Ticket
//-----------------------------------------------------

void BookingSystem::updateTicket()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings.\n";
        return;
    }

    int id;

    cout << "\nBooking ID : ";

    cin >> id;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        if (temp->bookingID == id)
        {
            cin.ignore();

            string date;

            string seat;

            cout << "New Date : ";

            getline(cin, date);

            cout << "New Seat : ";

            getline(cin, seat);

            if (!isSeatAvailable(temp->movieID,
                                 temp->screenNumber,
                                 date,
                                 temp->showTime,
                                 seat))
            {
                cout << "\nSeat Already Booked.\n";
                return;
            }

            temp->bookingDate = date;

            temp->seatNumber = seat;

            saveData();

            cout << "\nBooking Updated Successfully.\n";

            return;
        }

        temp = temp->next;
    }

    cout << "\nBooking Not Found.\n";
}

//-----------------------------------------------------
// Cancel Ticket
//-----------------------------------------------------

void BookingSystem::cancelTicket()
{
    if (head == nullptr)
    {
        cout << "\nNo Bookings.\n";
        return;
    }

    int id;

    cout << "\nBooking ID : ";

    cin >> id;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        if (temp->bookingID == id)
        {
            if (temp->isCancelled)
            {
                cout << "\nAlready Cancelled.\n";
                return;
            }

            temp->isCancelled = true;

            cancelledBookings++;

            totalRevenue -= temp->ticketPrice;

            saveData();

            cout << "\nBooking Cancelled Successfully.\n";

            return;
        }

        temp = temp->next;
    }

    cout << "\nBooking Not Found.\n";
}
//-----------------------------------------------------
// Revenue Report
//-----------------------------------------------------

void BookingSystem::revenueReport()
{
    cout << "\n========== REVENUE REPORT ==========\n";

    cout << "Total Bookings     : " << totalBookings << endl;
    cout << "Cancelled Bookings : " << cancelledBookings << endl;
    cout << "Successful Booking : "
         << totalBookings - cancelledBookings << endl;

    cout << "Total Revenue      : Rs. "
         << totalRevenue << endl;
}

//-----------------------------------------------------
// Booking Statistics
//-----------------------------------------------------

void BookingSystem::bookingStatistics()
{
    int active = 0;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        if (!temp->isCancelled)
            active++;

        temp = temp->next;
    }

    cout << "\n========== BOOKING STATISTICS ==========\n";

    cout << "Movies Available      : "
         << movies.size() << endl;

    cout << "Screens Available     : "
         << screens.size() << endl;

    cout << "Total Bookings        : "
         << totalBookings << endl;

    cout << "Active Bookings       : "
         << active << endl;

    cout << "Cancelled Bookings    : "
         << cancelledBookings << endl;
}

//-----------------------------------------------------
// Admin Menu
//-----------------------------------------------------

void BookingSystem::adminMenu()
{
    int choice;

    do
    {
        cout << "\n=========== ADMIN MENU ===========\n";

        cout << "1. Display Movies\n";
        cout << "2. Display Tickets\n";
        cout << "3. Revenue Report\n";
        cout << "4. Booking Statistics\n";
        cout << "5. Save Data\n";
        cout << "6. Load Data\n";
        cout << "0. Logout\n";

        cout << "\nChoice : ";

        cin >> choice;

        switch (choice)
        {
        case 1:

            displayMovies();
            break;

        case 2:

            displayAllTickets();
            break;

        case 3:

            revenueReport();
            break;

        case 4:

            bookingStatistics();
            break;

        case 5:

            saveData();

            cout << "\nData Saved.\n";

            break;

        case 6:

            loadData();

            cout << "\nData Loaded.\n";

            break;

        case 0:

            break;

        default:

            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 0);
}

//-----------------------------------------------------
// Save Data
//-----------------------------------------------------

void BookingSystem::saveData()
{
    fileManager.saveBookings(head);

    fileManager.saveMovies(movies);
}

//-----------------------------------------------------
// Load Data
//-----------------------------------------------------

void BookingSystem::loadData()
{
    int nextID = nextBookingID;

    head = fileManager.loadBookings(nextID);

    nextBookingID = nextID;

    vector<Movie> loadedMovies =
        fileManager.loadMovies();

    if (!loadedMovies.empty())
        movies = loadedMovies;

    totalBookings = 0;
    cancelledBookings = 0;
    totalRevenue = 0;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        totalBookings++;

        if (temp->isCancelled)
            cancelledBookings++;
        else
            totalRevenue += temp->ticketPrice;

        temp = temp->next;
    }
}