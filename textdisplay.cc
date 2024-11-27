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
            // Calculate window dimensions based on board sizes
            int cellWidth = 30;
            int cellHeight = 30;
            int spacing = 20;
            int windowWidth = (b1.getWidth() + b2.getWidth()) * cellWidth + 3 * spacing;
            int windowHeight = std::max(b1.getHeight(), b2.getHeight()) * cellHeight + 100; // Extra space for info

            // Initialize Xwindow
            xwindow_ptr = new Xwindow(windowWidth, windowHeight);
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
    if (textMode) {
        displayText();
    } else {
        displayGraphical();
    }
}

// Text display implementation with separate highscore
void TextDisplay::displayText() {
    // Update highscore based on player scores
    //if (board1.getScore() >= board2.getScore()) {
    //    if (highscore < board1.getScore()) {
    //        highscore = board1.getScore();
    //    }
    //} else {
    //    if (highscore < board2.getScore()) {
    //        highscore = board2.getScore();
    //    }
    //}

    // Display highscore
    //std::cout << "             Highscore: " << highscore << std::endl;
    cout << "Player 1 Highscore: " << board1.getHiScore() << "       " <<
	    "Player 2 Highscore: " << board2.getHiScore() << endl;

    // Display Level
    cout << "Player 1 Level: " << board1.getLevel() << "           " <<
	    "Player 2 Level: " << board2.getLevel() << endl;

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
            border += std::string(1, horizontal);
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
    cout << endl;
}

// Graphical display implementation
void TextDisplay::displayGraphical() {
    if (!xwindow_ptr) return;

    // Clear the window
    xwindow_ptr->fillRectangle(0, 0, xwindow_ptr->getWidth(), xwindow_ptr->getHeight(), Xwindow::White);

    // Define cell size and spacing
    const int cellWidth = 30;
    const int cellHeight = 30;
    const int spacing = 20;

    // Starting positions
    int startX1 = 10;
    int startY = 50; // Space for info

    // Draw first board
    for(int i = 0; i < board1.getHeight(); ++i) {
        for(int j = 0; j < board1.getWidth(); ++j) {
            const Cell& cell = board1.getCell(i, j);
            int x = startX1 + j * cellWidth;
            int y = startY + i * cellHeight;

            if(cell.isFilled()) {
                char shape = cell.getShape();
                int color;
                switch(shape) {
                    case 'I': color = Xwindow::Cyan; break;
                    case 'J': color = Xwindow::Blue; break;
                    case 'L': color = Xwindow::Orange; break;
                    case 'O': color = Xwindow::Yellow; break;
                    case 'S': color = Xwindow::Green; break;
                    case 'T': color = Xwindow::Purple; break;
                    case 'Z': color = Xwindow::Red; break;
                    case '*': color = Xwindow::Black; break; // Example for special blocks
                    default: color = Xwindow::White; break;
                }
                xwindow_ptr->fillRectangle(x, y, cellWidth, cellHeight, color);
            } else {
                // Draw empty cell border
                xwindow_ptr->drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }

    // Draw second board with spacing
    int startX2 = startX1 + board1.getWidth() * cellWidth + spacing;

    for(int i = 0; i < board2.getHeight(); ++i) {
        for(int j = 0; j < board2.getWidth(); ++j) {
            const Cell& cell = board2.getCell(i, j);
            int x = startX2 + j * cellWidth;
            int y = startY + i * cellHeight;

            if(cell.isFilled()) {
                char shape = cell.getShape();
                int color;
                switch(shape) {
                    case 'I': color = Xwindow::Cyan; break;
                    case 'J': color = Xwindow::Blue; break;
                    case 'L': color = Xwindow::Orange; break;
                    case 'O': color = Xwindow::Yellow; break;
                    case 'S': color = Xwindow::Green; break;
                    case 'T': color = Xwindow::Purple; break;
                    case 'Z': color = Xwindow::Red; break;
                    case '*': color = Xwindow::Black; break; // Example for special blocks
                    default: color = Xwindow::White; break;
                }
                xwindow_ptr->fillRectangle(x, y, cellWidth, cellHeight, color);
            } else {
                // Draw empty cell border
                xwindow_ptr->drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }

    // Draw highscore and levels
    std::string highscoreStr = "Highscore: " + std::to_string(highscore);
    xwindow_ptr->drawString(10, 30, highscoreStr);

    std::string levelStr1 = "Level: " + std::to_string(board1.getLevel());
    std::string levelStr2 = "Level: " + std::to_string(board2.getLevel());
    xwindow_ptr->drawString(10, 45, levelStr1);
    xwindow_ptr->drawString(startX2, 45, levelStr2);

    // Refresh the window to show updates
    xwindow_ptr->redraw();
}

