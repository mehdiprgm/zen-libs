#pragma once

#include <termios.h>
#include <stdio.h>

static struct termios old, current;

namespace zen::terminal {
    void initTermios(int echo);
    void resetTermios();

    char getch_(int echo);
    char getch(void);
    char getche(void);
}

