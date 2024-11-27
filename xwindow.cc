// xwindow.cc
#include "xwindow.h"
#include <iostream>

// Constructor
XWindow::XWindow(const Board &board) 
    : board(board), 
      xw(MARGIN_LEFT + board.getWidth() * DESIRED_CELL_WIDTH + MARGIN_RIGHT,
          MARGIN_TOP + board.getHeight() * DESIRED_CELL_HEIGHT + INFO_HEIGHT + MARGIN_BOTTOM) {
    
    // Log the window dimensions
    std::cerr << "Initializing Xwindow with width: " << xw.getWidth() 
              << ", height: " << xw.getHeight() << std::endl;

    // Initialize background
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::White);
}

// Displays the board and game state
void XWindow::display() {
    // Clear the window
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::White);
    
    // Board dimensions
    int boardWidth = board.getWidth();
    int boardHeight = board.getHeight();
    
    // Cell dimensions
    int cellWidth = DESIRED_CELL_WIDTH;
    int cellHeight = DESIRED_CELL_HEIGHT;
    
    // Starting positions with margins
    int startX = MARGIN_LEFT;
    int startY = MARGIN_TOP;
    
    // Debugging logs
    std::cerr << "Window Width: " << xw.getWidth() 
              << ", Window Height: " << xw.getHeight() << std::endl;
    std::cerr << "Board Width: " << boardWidth 
              << ", Board Height: " << boardHeight << std::endl;
    std::cerr << "Cell Width: " << cellWidth 
              << ", Cell Height: " << cellHeight << std::endl;
    std::cerr << "StartX: " << startX 
              << ", StartY: " << startY << std::endl;
    
    // Draw each cell
    for (int row = 0; row < boardHeight; ++row) {
        for (int col = 0; col < boardWidth; ++col) {
            const Cell& cell = board.getCell(row, col);
            int x = startX + col * cellWidth;
            int y = startY + row * cellHeight;
    
            // Determine color based on block type or other criteria
            int color = Xwindow::White; // Default color for empty cells
    
            char shape = cell.getShape();
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
    
            if (cell.isFilled()) {
                xw.fillRectangle(x, y, cellWidth, cellHeight, color);
            } else {
                // Optional: Draw empty cell border
                xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }
    
    // Draw grid lines (optional)
    for (int i = 0; i <= boardWidth; ++i) {
        int x = startX + i * cellWidth;
        xw.drawLine(x, startY, x, startY + boardHeight * cellHeight, Xwindow::Black);
    }
    for (int i = 0; i <= boardHeight; ++i) {
        int y = startY + i * cellHeight;
        xw.drawLine(startX, y, startX + boardWidth * cellWidth, y, Xwindow::Black);
    }
    
    // Update additional info (score, level)
    updateInfo();
    
    // Refresh the window to show updates
    xw.redraw();
}

// Updates the UI information area
void XWindow::updateInfo() {
    // Define starting positions within the info area
    int infoStartY = xw.getHeight() - INFO_HEIGHT + 20; // 20 pixels from top of info area
    int scoreX = MARGIN_LEFT;
    int levelX = MARGIN_LEFT + 150; // Adjust as needed
    
    // Debugging logs
    std::cerr << "Drawing score at (" << scoreX << ", " << infoStartY << ")" << std::endl;
    std::cerr << "Drawing level at (" << levelX << ", " << infoStartY << ")" << std::endl;
    
    // Draw score and level
    std::string scoreStr = "Score: " + std::to_string(board.getScore());
    std::string levelStr = "Level: " + std::to_string(board.getLevel());
    
    xw.drawString(scoreX, infoStartY, scoreStr);
    xw.drawString(levelX, infoStartY, levelStr);
}

