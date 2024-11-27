#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include "cell.h"
#include "block.h"
#include "level.h"
#include "board.h"

class TextDisplay {
    const Board &board;
public:
    TextDisplay(const Board &board);

    // Displays the current state of the board
    void display();
};

#endif
