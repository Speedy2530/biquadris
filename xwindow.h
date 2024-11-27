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
const int MARGIN_TOP = 50;          // Top margin (increase to make room for info)
const int MARGIN_RIGHT = 10;        // Right margin
const int MARGIN_BOTTOM = 10;       // Bottom margin
const int SPACING = 20;             // Space between the two boards

class XWindow {
    const Board &board1;
    const Board &board2;
    Xwindow xw; // Instance of Xwindow

public:
    XWindow(const Board &board1, const Board &board2);
    ~XWindow() = default;

    // Displays the current state of the boards
    void display();

    // Updates the UI information area
    void updateInfo();
};

#endif
