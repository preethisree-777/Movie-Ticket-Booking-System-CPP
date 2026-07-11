#ifndef TICKET_H
#define TICKET_H
#include <string>
class Ticket
{
public:
    int bookingID, movieID, screenNumber;
    std::string customerName, movieName, bookingDate, showTime, seatNumber;
    float ticketPrice;
    bool isCancelled;
    Ticket *next;
    Ticket();
    Ticket(int, int, const std::string &, const std::string &, int, const std::string &, const std::string &, const std::string &, float);
    void displayTicket() const;
};
#endif
