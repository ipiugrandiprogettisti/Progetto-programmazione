#include "header/utils.hpp"
#include "header/MyString.hpp"

// custom itoa, converts int to const char *
// FIXME problema append, a volte viene stampato garbage... problemi con \0 finale DA TESTARE ANCHE QUI SE C'È PROBLEMA
const char *itoa(int num)
{
    MyString str = MyString();
    bool isNeg = false;
    if (num < 0)
    {
        isNeg = true;
        num *= -1;
    }

    if (num == 0)
        // str.append('0');
        str += '0';

    for (int i = 0; num > 0; i++)
    {
        char c = '0' + num % 10;
        // str.append(c);
        str += c;
        num = num / 10;
    }

    if (isNeg)
        // str.append('-');
        str += '-';

    str.reverse();
    return str.get();
}

// check if color is supported by user's terminal
void checkColors()
{
    if (has_colors() == FALSE)
    {
        endwin();
        std::cout << "Your terminal does not support color\n";
        exit(1);
    }
}

// listRooms functions
// head insert
