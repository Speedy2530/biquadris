// xwindow.h
#ifndef XWINDOW_H
#define XWINDOW_H

#include "window.h" // Include the Xwindow class
#include "board.h"
#include <string>

// Layout Constants
const int INFO_HEIGHT = 50;         // Height reserved for UI elements
const int DESIRED_CELL_WIDTH = 30;  // Width of each cell
const int DESIRED_CELL_HEIGHT = 30; // Height of each cell
const int MARGIN_LEFT = 10;         // Left margin
const int MARGIN_TOP = 10;          // Top margin
const int MARGIN_RIGHT = 10;        // Right margin
const int MARGIN_BOTTOM = 10;       // Bottom margin

class XWindow {
    const Board &board;
    Xwindow xw; // Instance of Xwindow

public:
    XWindow(const Board &board);
    ~XWindow() = default; // Default destructor is sufficient

    // Displays the current state of the board
    void display();

    // Optional: Update the window title with score and level
    void updateInfo();
};

#endif

