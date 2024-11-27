#ifndef XWINDOW_H
#define XWINDOW_H

#include <vector>
#include <iostream>
#include "cell.h"
#include "block.h"
#include "level.h"
#include "board.h"
#include "window.h" // Include the Xwindow class

class XWindow {
    const Board &board;
    Xwindow xw; // Add an instance of Xwindow
public:
    XWindow(const Board &board);

    // Displays the current state of the board
    void display();
};

#endif

