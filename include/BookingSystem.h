#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H
#include <vector>
#include <string>
#include "Ticket.h"
#include "Movie.h"
#include "Screen.h"
#include "FileManager.h"
class BookingSystem
{
    Ticket *head;
    int nextBookingID, totalBookings, cancelledBookings;
    float totalRevenue;
    std::vector<Movie> movies;
    std::vector<Screen> screens;
    FileManager fileManager;

public:
    BookingSystem();
    ~BookingSystem();
    void initializeMovies();
    void initializeScreens();
    void displayMovies();
    void displayScreens();
    void bookTicket();
    void displayAllTickets();
    void searchByBookingID();
    void searchByCustomerName();
    void searchByMovieName();
    void updateTicket();
    void cancelTicket();
    bool isSeatAvailable(int, int, const std::string &, const std::string &, const std::string &);
    void displaySeatLayout(int, int, const std::string &, const std::string &);
    void revenueReport();
    void bookingStatistics();
    bool adminLogin();
    void adminMenu();
    void saveData();
    void loadData();
    void mainMenu();
};
#endif
