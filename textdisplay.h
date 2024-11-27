#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include "cell.h"
#include "block.h"
#include "level.h"
#include "board.h"
#include "xwindow.h"

class TextDisplay {
    const Board &board1;
    const Board &board2;
    bool textMode;
    unsigned int highscore;
    Xwindow *xwindow_ptr; // Corrected class name

public:
    // Constructor takes two boards and a mode flag
    TextDisplay(const Board &b1, const Board &b2, bool mode = true);

    // Destructor to clean up Xwindow if used
    ~TextDisplay();

    // Displays the current state of the boards
    void display();

private:
    // Helper methods for different display modes
    void displayText();
    void displayGraphical();
};

#endif

