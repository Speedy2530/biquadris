#include "textdisplay.h"
#include "board.h"

// Constructor
TextDisplay::TextDisplay(const Board &board) : board{board} {}

// Displays the board and game state
void TextDisplay::display() {
    const int TOTAL_ROWS = Board::TOTAL_ROWS;
    const int TOTAL_COLS = Board::TOTAL_COLS;
    const auto &grid = board.getGrid(); // We'll add a getGrid() method to Board

    // Print the board from top to bottom
    for (int r = TOTAL_ROWS - 1; r >= 0; --r) {
        std::cout << "|";
        for (int c = 0; c < TOTAL_COLS; ++c) {
            std::cout << grid[r][c].getShape();
        }
        std::cout << "|\n";
    }

    // Print the bottom border
    std::cout << "+";
    for (int c = 0; c < TOTAL_COLS; ++c) {
        std::cout << "-";
    }
    std::cout << "+\n";

    // Print score and hi score
    std::cout << "Level: " << board.getCurrLevelNum() << "\n";
    std::cout << "Score: " << board.getScore() << "  Hi-Score: " << board.getHiScore() << "\n";
    std::cout << "Next:\n";

    // Display the next block
    if (board.getNextBlock()) {
        board.getNextBlock()->print();
    }
}

