
#include "../include/Movie.h"
#include <iostream>
using namespace std;

Movie::Movie()
{
    movieID = 0;
    duration = 0;
    ticketPrice = 0;
    nowShowing = true;
}

Movie::Movie(int id, const string &name, const string &gen,
             const string &lang, const string &dir,
             int dur, float price)
{
    movieID = id;
    movieName = name;
    genre = gen;
    language = lang;
    director = dir;
    duration = dur;
    ticketPrice = price;
    nowShowing = true;
}

void Movie::addShowTime(const string &time) { showTimes.push_back(time); }
int Movie::getMovieID() const { return movieID; }
string Movie::getMovieName() const { return movieName; }
vector<string> Movie::getShowTimes() const { return showTimes; }
float Movie::getTicketPrice() const { return ticketPrice; }
string Movie::getGenre() const
{
    return genre;
}

string Movie::getLanguage() const
{
    return language;
}

string Movie::getDirector() const
{
    return director;
}

int Movie::getDuration() const
{
    return duration;
}

void Movie::displayMovie() const
{
    cout << "\nMovie ID : " << movieID << endl;
    cout << "Movie    : " << movieName << endl;
    cout << "Genre    : " << genre << endl;
    cout << "Language : " << language << endl;
    cout << "Director : " << director << endl;
    cout << "Duration : " << duration << " mins" << endl;
    cout << "Price    : Rs. " << ticketPrice << endl;
    cout << "Shows    : ";
    for (const auto &s : showTimes)
        cout << s << " ";
    cout << endl;
}
