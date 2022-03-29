#include "header/game.hpp"

void    startgame()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    // draw main menu and get user choice 0 is play, 1 is credits. -1 is error.
    int choice = getMenu(maxX, maxY, 0, 0);

    endwin(); // End curses mode
}