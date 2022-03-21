#include <ncurses.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

// TODO: creare classe MyWindow e implementare print

// Custom string class
class MyString
{
public:
    char *string;
    int length = 0;

public:
    MyString()
    {
        string = new char[strlen("\0") + 1];
        strcpy(string, "\0");
        this->length = strlen("\0");
    }

    MyString(char const *text)
    {
        this->length = strlen(text);
        string = new char[strlen(text) + 1];
        strcpy(string, text);
    }

    // append string
    void append(char const *text)
    {
        char *oldStr = new char[strlen(string) + 1];

        for (int i = 0; string[i] != '\0'; i++)
            oldStr[i] = string[i];

        length = strlen(oldStr) + strlen(text);
        string = new char[length + 1];

        for (int i = 0; oldStr[i] != '\0'; i++)
            string[i] = oldStr[i];

        int c = 0;
        for (int i = strlen(oldStr); text[c] != '\0'; i++)
        {
            string[i] = text[c];
            c++;
        }

        delete oldStr;
    }

    // returns string length, does not count '\0'
    int getLength()
    {
        return length;
    }

    // returns string
    const char *get()
    {
        return string;
    }
};

// return new window
WINDOW *newWindow(int height, int width, int starty, int startx)
{
    WINDOW *localWindow;

    localWindow = newwin(height, width, starty, startx);
    box(localWindow, 0, 0); /* 0, 0 gives default characters
                             * for the vertical and horizontal
                             * lines			*/
    wrefresh(localWindow);  /* Show that box 		*/

    return localWindow;
}

// destroy the given window
void destroyWindow(WINDOW *localWindow)

{
    /* box(localWindow, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners
     * and so an ugly remnant of window.
     */
    wborder(localWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    /* The parameters taken are
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window
     * 3. rs: character to be used for the right side of the window
     * 4. ts: character to be used for the top side of the window
     * 5. bs: character to be used for the bottom side of the window
     * 6. tl: character to be used for the top left corner of the window
     * 7. tr: character to be used for the top right corner of the window
     * 8. bl: character to be used for the bottom left corner of the window
     * 9. br: character to be used for the bottom right corner of the window
     */
    wrefresh(localWindow);
    delwin(localWindow);
}

/*
draw the main menu and returns choice taken by user:
- 0: Play
- 1: Credits
*/
int getMenu(int maxY, int maxX, int offY, int offX)
{
    const int MAX_ITEMS = 2,
              MIN_ITEMS = 0,
              MAX_LENGTH_ITEM = 20;
    int startX = LINES, startY = COLS, width, height;
    char string[MAX_ITEMS][MAX_LENGTH_ITEM] = {"Play", "Credits"};
    int selectedItem = 0; // could only be -1, 0 or 1. 0 is default

    WINDOW *myWin = newwin(maxY, maxX, offY, offX);
    wrefresh(myWin);
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();                           /* Start color 			*/
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // first color is font color, second is background color
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // color for selected item
    wbkgd(myWin, COLOR_PAIR(1));
    wrefresh(myWin);
    // Activating color for one line
    /*
    attron(COLOR_PAIR(1));
    mvaddstr(startY, startY, "ciao a tutti");
    attroff(COLOR_PAIR(1));
    */
    // center string
    startY = LINES / 2 - 1;
    startX = COLS / 2 - 1;
    int padding = 0; // set padding between menu items when displayed
    for (int i = 0; i < MAX_ITEMS; i++)
    {

        // check if current item is the selected one, if it is like so print it glowly
        if (i == selectedItem)
        {
            attron(COLOR_PAIR(2));
            mvaddstr(startY + padding, startX, string[i]);
            attroff(COLOR_PAIR(2));
        }
        else
        {
            attron(COLOR_PAIR(1));
            mvaddstr(startY + padding, startX, string[i]);
            attroff(COLOR_PAIR(1));
        }
        padding += 3;
    }

    int ch; // pressed key
    MyString item = MyString((char const *)"STRINGA");
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()) != KEY_F(1)) // if F1 is pressed quit
    {
        switch (ch)
        {
        case KEY_UP:
            move(0, 0);
            clrtoeol();
            wrefresh(myWin);
            addstr("a");
            if (selectedItem++ > MAX_ITEMS - 1)
                selectedItem = MIN_ITEMS; // reset selectedItem to 0
            else
                selectedItem++;
            break;
        case KEY_DOWN:
            move(0, 0);
            clrtoeol();
            wrefresh(myWin);
            mvaddstr(0, 0, "freccia giù");
            if (selectedItem-- < MIN_ITEMS - 1)
                selectedItem = MAX_ITEMS; // reset selectedItem to 0
            else
                selectedItem--;
            break;
        }
    }

    return selectedItem;
}