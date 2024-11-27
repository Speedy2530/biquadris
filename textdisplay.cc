// textdisplay.cc
#include "textdisplay.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

// Constructor
TextDisplay::TextDisplay(const Board &b1, const Board &b2, bool mode)
    : board1(b1), board2(b2), textMode(mode), xwindow_ptr(nullptr) {
    if (!textMode) {
        try {
            // Initialize XWindow with both boards
            xwindow_ptr = new XWindow(board1, board2);
        } catch (const char* msg) {
            std::cerr << "Error initializing Xwindow: " << msg << std::endl;
            std::cerr << "Continuing with text mode." << std::endl;
            textMode = true;
            if (xwindow_ptr) {
                delete xwindow_ptr;
                xwindow_ptr = nullptr;
            }
        }
    }
}

// Destructor
TextDisplay::~TextDisplay() {
    if (xwindow_ptr) {
        delete xwindow_ptr;
    }
}

// Display method
void TextDisplay::display(bool player1Turn) {
    // Always display text
    displayText();

    // If textMode is false and xwindow_ptr is initialized, update the graphical display
    if (!textMode && xwindow_ptr) {
        xwindow_ptr->display(player1Turn);
    }
}

// Definition of displayText()
void TextDisplay::displayText() {
    // Update highscore based on player scores
    // unsigned int highscore = std::max(board1.getHiScore(), board2.getHiScore());

    // Display highscore
    std::cout << "Player 1 Highscore: " << board1.getHiScore() << "       "
              << "Player 2 Highscore: " << board2.getHiScore() << std::endl;

    // Display Level
    // std::cout << "Player 1 Level: " << board1.getLevel() << "           "
    //           << "Player 2 Level: " << board2.getLevel() << std::endl;

    // Define border characters
    const char corner = '+';
    const char horizontal = '-';
    const char vertical = '|';
    const int boardWidth = board1.getWidth(); // Assuming both boards have the same width
    const int boardHeight = board1.getHeight(); // Assuming both boards have the same height

    // Function to create a border line based on board width
    auto createBorder = [&](int width) -> std::string {
        std::string border = "";
        border += corner;
        for(int i = 0; i < width; ++i) {
            border += horizontal;
        }
        border += corner;
        return border;
    };

    // Create borders for both boards
    std::string topBorder = createBorder(boardWidth);
    std::string separator = createBorder(boardWidth);

    // Display levels and scores with borders
    std::cout << topBorder << "               " << topBorder << std::endl;
    std::cout << vertical << " Level: " << board1.getLevel();
    // Fill remaining space if level number is single-digit
    if(board1.getLevel() < 10) std::cout << " ";
    std::cout << " " << vertical << "               " << vertical << " Level: " << board2.getLevel();
    if(board2.getLevel() < 10) std::cout << " ";
    std::cout << " " << vertical << std::endl;

    std::cout << vertical << " Score: " << board1.getScore();
    if(board1.getScore() < 10) std::cout << " ";
    std::cout << " " << vertical << "               " << vertical << " Score: " << board2.getScore();
    if(board2.getScore() < 10) std::cout << " ";
    std::cout << " " << vertical << std::endl;

    std::cout << separator << "               " << separator << std::endl;

    // Display each row of both boards with side borders
    for(int i = 0; i < boardHeight; ++i) {
        std::cout << vertical;
        for(int j = 0; j < boardWidth; ++j) {
            std::cout << board1.getCell(i, j).getShape();
        }
        std::cout << vertical << "               " << vertical;
        for(int k = 0; k < boardWidth; ++k) {
            std::cout << board2.getCell(i, k).getShape();
        }
        std::cout << vertical << std::endl;
    }

    // Display bottom borders
    std::cout << topBorder << "               " << topBorder << std::endl;
    std::cout << std::endl;
    
    // Get the next blocks for both players
    const Block* nextBlock1 = board1.getNextBlock();
    const Block* nextBlock2 = board2.getNextBlock();

    // Get string representations of the next blocks
    std::vector<std::string> nextBlockLines1 = getBlockString(nextBlock1);
    std::vector<std::string> nextBlockLines2 = getBlockString(nextBlock2);

    // Format the next block lines to center under each board
    std::vector<std::string> formattedNextBlockLines1;
    std::vector<std::string> formattedNextBlockLines2;

    for (const auto& line : nextBlockLines1) {
        int totalPadding = boardWidth - line.length();
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;
        std::string formattedLine = std::string(leftPadding, ' ') + line + std::string(rightPadding, ' ');
        formattedNextBlockLines1.push_back(formattedLine);
    }

    for (const auto& line : nextBlockLines2) {
        int totalPadding = boardWidth - line.length();
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;
        std::string formattedLine = std::string(leftPadding, ' ') + line + std::string(rightPadding, ' ');
        formattedNextBlockLines2.push_back(formattedLine);
    }
    
    // Print the "Next:" labels centered under each board
    int labelTotalPadding = boardWidth - 5; // "Next:" is 5 characters
    int labelLeftPadding = labelTotalPadding / 2;
    int labelRightPadding = labelTotalPadding - labelLeftPadding;

    std::cout << vertical << std::string(labelLeftPadding, ' ') << "Next:" << std::string(labelRightPadding, ' ') << vertical
              << "               "
              << vertical << std::string(labelLeftPadding, ' ') << "Next:" << std::string(labelRightPadding, ' ') << vertical << std::endl;

    // Print the next block lines
    for (size_t i = 0; i < formattedNextBlockLines1.size(); ++i) {
        std::cout << vertical << formattedNextBlockLines1[i] << vertical
                  << "               "
                  << vertical << formattedNextBlockLines2[i] << vertical << std::endl;
    }

    // Optional: Add an empty line after the next blocks
    std::cout << std::endl;
}

std::vector<std::string> TextDisplay::getBlockString(const Block* block) {
    std::vector<std::string> lines;
    if (!block) {
        // Return empty lines if block is null
        for (int i = 0; i < 4; ++i) {
            lines.push_back("    ");
        }
        return lines;
    }

    // Initialize a 4x4 grid
    char grid[4][4] = { {' ', ' ', ' ', ' '}, 
                        {' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' '} };

    // Find min and max positions to adjust the block within the grid
    int minRow = INT_MAX, minCol = INT_MAX;
    for (const auto& [relRow, relCol] : block->getRelPos()) {
        minRow = std::min(minRow, relRow);
        minCol = std::min(minCol, relCol);
    }

    // Place block shape in the grid
    for (const auto& [relRow, relCol] : block->getRelPos()) {
        int row = relRow - minRow;
        int col = relCol - minCol;
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            grid[row][col] = block->getShape();
        }
    }

    // Convert grid to lines
    for (int i = 0; i < 4; ++i) {
        std::string line;
        for (int j = 0; j < 4; ++j) {
            line += grid[i][j];
        }
        lines.push_back(line);
    }

    return lines;
}
