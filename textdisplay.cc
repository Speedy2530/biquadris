// textdisplay.cc
#include "textdisplay.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

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
void TextDisplay::display() {
    // Always display text
    displayText();

    // If textMode is false and xwindow_ptr is initialized, update the graphical display
    if (!textMode && xwindow_ptr) {
        xwindow_ptr->display();
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
}
