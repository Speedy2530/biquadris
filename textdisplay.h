// textdisplay.h
#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include "cell.h"
#include "block.h"
#include "level.h"
#include "board.h"
#include "xwindow.h" // Include the updated XWindow class

class TextDisplay {
    const Board &board1;
    const Board &board2;
    bool textMode;
    unsigned int highscore;
    unique_ptr<XWindow> xwindow_ptr; // Use XWindow instead of Xwindow

public:
    // Constructor takes two boards and a mode flag
    TextDisplay(const Board &b1, const Board &b2, bool mode = true);

    // Destructor to clean up XWindow if used
    ~TextDisplay();

    // Displays the current state of the boards
    void display(bool player1Turn);

private:
    // Helper methods for different display modes
    void displayText();
    void displayGraphical();
    std::vector<std::string> getBlockString(const Block* block);
};

#endif
