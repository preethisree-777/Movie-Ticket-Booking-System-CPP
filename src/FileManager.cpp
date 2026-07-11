#include "../include/FileManager.h"
#include <fstream>
#include <sstream>

using namespace std;

//-----------------------------------------------------
// Constructor
//-----------------------------------------------------

FileManager::FileManager(const string &bookings,
                         const string &movies)
{
    bookingFile = bookings;
    movieFile = movies;
}

//-----------------------------------------------------
// Save Bookings
//-----------------------------------------------------

void FileManager::saveBookings(Ticket *head)
{
    ofstream file(bookingFile);

    if (!file.is_open())
        return;

    Ticket *temp = head;

    while (temp != nullptr)
    {
        file << temp->bookingID << "|"
             << temp->movieID << "|"
             << temp->customerName << "|"
             << temp->movieName << "|"
             << temp->screenNumber << "|"
             << temp->bookingDate << "|"
             << temp->showTime << "|"
             << temp->seatNumber << "|"
             << temp->ticketPrice << "|"
             << temp->isCancelled
             << endl;

        temp = temp->next;
    }

    file.close();
}

//-----------------------------------------------------
// Load Bookings
//-----------------------------------------------------

Ticket *FileManager::loadBookings(int &nextBookingID)
{
    ifstream file(bookingFile);

    if (!file.is_open())
        return nullptr;

    Ticket *head = nullptr;
    Ticket *tail = nullptr;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string temp;

        int bookingID;
        int movieID;
        int screenNumber;

        string customerName;
        string movieName;
        string bookingDate;
        string showTime;
        string seatNumber;

        float price;
        bool cancelled;

        getline(ss, temp, '|');
        bookingID = stoi(temp);

        getline(ss, temp, '|');
        movieID = stoi(temp);

        getline(ss, customerName, '|');

        getline(ss, movieName, '|');

        getline(ss, temp, '|');
        screenNumber = stoi(temp);

        getline(ss, bookingDate, '|');

        getline(ss, showTime, '|');

        getline(ss, seatNumber, '|');

        getline(ss, temp, '|');
        price = stof(temp);

        getline(ss, temp, '|');
        cancelled = stoi(temp);

        Ticket *ticket = new Ticket(
            bookingID,
            movieID,
            customerName,
            movieName,
            screenNumber,
            bookingDate,
            showTime,
            seatNumber,
            price);

        ticket->isCancelled = cancelled;
        ticket->next = nullptr;

        if (head == nullptr)
        {
            head = tail = ticket;
        }
        else
        {
            tail->next = ticket;
            tail = ticket;
        }

        if (bookingID >= nextBookingID)
            nextBookingID = bookingID + 1;
    }

    file.close();

    return head;
}

//-----------------------------------------------------
// Save Movies
//-----------------------------------------------------

void FileManager::saveMovies(const vector<Movie> &movies)
{
    ofstream file(movieFile);

    if (!file.is_open())
        return;

    for (const auto &movie : movies)
    {
        file << movie.getMovieID() << "|"
             << movie.getMovieName() << "|"
             << movie.getTicketPrice();

        vector<string> shows = movie.getShowTimes();

        for (const auto &show : shows)
        {
            file << "|" << show;
        }

        file << endl;
    }

    file.close();
}

//-----------------------------------------------------
// Load Movies
//-----------------------------------------------------

vector<Movie> FileManager::loadMovies()
{
    vector<Movie> movies;

    ifstream file(movieFile);

    if (!file.is_open())
        return movies;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string temp;

        getline(ss, temp, '|');
        int id = stoi(temp);

        string name;
        getline(ss, name, '|');

        getline(ss, temp, '|');
        float price = stof(temp);

        // Placeholder values because Movie.h
        // doesn't expose all attributes.
        Movie movie(id,
                    name,
                    "Unknown",
                    "Unknown",
                    "Unknown",
                    120,
                    price);

        while (getline(ss, temp, '|'))
        {
            movie.addShowTime(temp);
        }

        movies.push_back(movie);
    }

    file.close();

    return movies;
}

//-----------------------------------------------------
// Check File Exists
//-----------------------------------------------------

bool FileManager::fileExists(const string &file) const
{
    ifstream f(file);

    return f.good();
}