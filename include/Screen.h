#ifndef SCREEN_H
#define SCREEN_H
#include <string>
class Screen
{
    int screenNumber, rows, columns;

public:
    Screen();
    Screen(int, int = 10, int = 10);
    int getScreenNumber() const;
    int getRows() const;
    int getColumns() const;
    std::string getSeatLabel(char, int) const;
};
#endif
