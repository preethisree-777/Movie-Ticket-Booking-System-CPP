
#include "../include/Ticket.h"
#include <iostream>
using namespace std;

Ticket::Ticket()
{
    bookingID = 0;
    movieID = 0;
    screenNumber = 0;
    customerName = "";
    movieName = "";
    bookingDate = "";
    showTime = "";
    seatNumber = "";
    ticketPrice = 0.0f;
    isCancelled = false;
    next = nullptr;
}

Ticket::Ticket(int id, int mId, const string &customer, const string &movie,
               int screen, const string &date, const string &time,
               const string &seat, float price)
{
    bookingID = id;
    movieID = mId;
    screenNumber = screen;
    customerName = customer;
    movieName = movie;
    bookingDate = date;
    showTime = time;
    seatNumber = seat;
    ticketPrice = price;
    isCancelled = false;
    next = nullptr;
}

void Ticket::displayTicket() const
{
    cout << "\n========== TICKET ==========\n";
    cout << "Booking ID : " << bookingID << endl;
    cout << "Customer   : " << customerName << endl;
    cout << "Movie      : " << movieName << endl;
    cout << "Screen     : " << screenNumber << endl;
    cout << "Date       : " << bookingDate << endl;
    cout << "Time       : " << showTime << endl;
    cout << "Seat       : " << seatNumber << endl;
    cout << "Price      : Rs. " << ticketPrice << endl;
    cout << "Status     : " << (isCancelled ? "Cancelled" : "Booked") << endl;
}
