#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <vector>
#include "Ticket.h"
#include "Movie.h"
class FileManager
{
    std::string bookingFile, movieFile;

public:
    FileManager(
        const std::string &bookings = "data/bookings.txt",
        const std::string &movies = "data/movies.txt");
    void saveBookings(Ticket *);
    Ticket *loadBookings(int &);
    void saveMovies(const std::vector<Movie> &);
    std::vector<Movie> loadMovies();
    bool fileExists(const std::string &) const;
};
#endif
