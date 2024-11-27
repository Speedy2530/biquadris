// xwindow.cc
#include "xwindow.h"
#include <iostream>
#include <algorithm>

// Constructor
XWindow::XWindow(const Board &board1, const Board &board2) 
    : board1(board1), board2(board2), 
      xw(MARGIN_LEFT + board1.getWidth() * DESIRED_CELL_WIDTH + SPACING + board2.getWidth() * DESIRED_CELL_WIDTH + MARGIN_RIGHT,
          MARGIN_TOP + std::max(board1.getHeight(), board2.getHeight()) * DESIRED_CELL_HEIGHT + INFO_HEIGHT + MARGIN_BOTTOM) {
    
    // Log the window dimensions
    std::cerr << "Initializing Xwindow with width: " << xw.getWidth() 
              << ", height: " << xw.getHeight() << std::endl;

    // Initialize background
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::White);
}

// Displays the boards and game state
void XWindow::display() {
    // Clear the window
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::White);
    
    // Cell dimensions
    int cellWidth = DESIRED_CELL_WIDTH;
    int cellHeight = DESIRED_CELL_HEIGHT;
    
    // Starting positions with margins
    int startX1 = MARGIN_LEFT;
    int startY = MARGIN_TOP;
    
    // Draw first board
    for (int row = 0; row < board1.getHeight(); ++row) {
        for (int col = 0; col < board1.getWidth(); ++col) {
            const Cell& cell = board1.getCell(row, col);
            int x = startX1 + col * cellWidth;
            int y = startY + row * cellHeight;

            int color = Xwindow::White; // Default color

            char shape = cell.getShape();
            switch(shape) {
                case 'I': color = Xwindow::Cyan; break;
                case 'J': color = Xwindow::Blue; break;
                case 'L': color = Xwindow::Orange; break;
                case 'O': color = Xwindow::Yellow; break;
                case 'S': color = Xwindow::Green; break;
                case 'T': color = Xwindow::Purple; break;
                case 'Z': color = Xwindow::Red; break;
                case '*': color = Xwindow::Black; break;
                default: color = Xwindow::White; break;
            }

            if (cell.isFilled()) {
                xw.fillRectangle(x, y, cellWidth, cellHeight, color);
            } else {
                // Draw empty cell border
                xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }

    // Draw second board
    int startX2 = startX1 + board1.getWidth() * cellWidth + SPACING;

    for (int row = 0; row < board2.getHeight(); ++row) {
        for (int col = 0; col < board2.getWidth(); ++col) {
            const Cell& cell = board2.getCell(row, col);
            int x = startX2 + col * cellWidth;
            int y = startY + row * cellHeight;

            int color = Xwindow::White; // Default color

            char shape = cell.getShape();
            switch(shape) {
                case 'I': color = Xwindow::Cyan; break;
                case 'J': color = Xwindow::Blue; break;
                case 'L': color = Xwindow::Orange; break;
                case 'O': color = Xwindow::Yellow; break;
                case 'S': color = Xwindow::Green; break;
                case 'T': color = Xwindow::Purple; break;
                case 'Z': color = Xwindow::Red; break;
                case '*': color = Xwindow::Black; break;
                default: color = Xwindow::White; break;
            }

            if (cell.isFilled()) {
                xw.fillRectangle(x, y, cellWidth, cellHeight, color);
            } else {
                // Draw empty cell border
                xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }

    // Update additional info (score, level)
    updateInfo();

    // Refresh the window to show updates
    xw.redraw();
}

// Updates the UI information area
void XWindow::updateInfo() {
    // Define starting positions within the info area
    int infoStartY = MARGIN_TOP / 2; // Adjust as needed
    int scoreX1 = MARGIN_LEFT;
    int levelX1 = MARGIN_LEFT;

    int startX2 = MARGIN_LEFT + board1.getWidth() * DESIRED_CELL_WIDTH + SPACING;
    int scoreX2 = startX2;
    int levelX2 = startX2;

    // Draw score and level for player 1
    std::string scoreStr1 = "Score: " + std::to_string(board1.getScore());
    std::string levelStr1 = "Level: " + std::to_string(board1.getLevel());
    xw.drawString(scoreX1, infoStartY, scoreStr1);
    xw.drawString(levelX1, infoStartY + 15, levelStr1);

    // Draw score and level for player 2
    std::string scoreStr2 = "Score: " + std::to_string(board2.getScore());
    std::string levelStr2 = "Level: " + std::to_string(board2.getLevel());
    xw.drawString(scoreX2, infoStartY, scoreStr2);
    xw.drawString(levelX2, infoStartY + 15, levelStr2);
}
