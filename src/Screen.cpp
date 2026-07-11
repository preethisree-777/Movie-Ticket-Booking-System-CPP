
#include "../include/Screen.h"
#include <string>
using namespace std;

Screen::Screen()
{
    screenNumber = 1;
    rows = 10;
    columns = 10;
}

Screen::Screen(int number, int r, int c)
{
    screenNumber = number;
    rows = r;
    columns = c;
}

int Screen::getScreenNumber() const { return screenNumber; }
int Screen::getRows() const { return rows; }
int Screen::getColumns() const { return columns; }

string Screen::getSeatLabel(char row, int col) const
{
    return string(1, row) + to_string(col);
}
