#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>
using namespace std;
class Movie
{
    int movieID, duration;
    std::string movieName, genre, language, director;
    float ticketPrice;
    bool nowShowing;
    std::vector<std::string> showTimes;

public:
    Movie();
    Movie(int, const std::string &, const std::string &, const std::string &, const std::string &, int, float);
    void addShowTime(const std::string &);
    int getMovieID() const;
    std::string getMovieName() const;
    std::vector<std::string> getShowTimes() const;
    float getTicketPrice() const;
    void displayMovie() const;
    string getGenre() const;
    string getLanguage() const;
    string getDirector() const;
    int getDuration() const;
};
#endif
