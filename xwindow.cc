#include "xwindow.h"
#include "board.h"

// Constructor
XWindow::XWindow(const Board &board) : board{board}, xw{300, 600} {} // Adjust window size

// Displays the board and game state
void XWindow::display() {
    // Clear the window
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::White);

    // Board dimensions
    int boardWidth = board.getWidth();
    int boardHeight = board.getHeight();

    // Cell dimensions
    int cellWidth = xw.getWidth() / boardWidth;
    int cellHeight = xw.getHeight() / boardHeight;

    // Draw each cell
    for (int row = 0; row < boardHeight; ++row) {
        for (int col = 0; col < boardWidth; ++col) {
            Cell cell = board.getCell(row, col); // Assuming you have this method
            int x = col * cellWidth;
            int y = row * cellHeight;

            int color = Xwindow::White; // Default color
            if (!cell.isEmpty()) {
                // Map cell content to color
                // For example:
                color = Xwindow::Black; // Or another color based on cell content
            }

            // Draw the cell
            xw.fillRectangle(x, y, cellWidth, cellHeight, color);
        }
    }

    // Draw grid lines (optional)
    for (int i = 0; i <= boardWidth; ++i) {
        int x = i * cellWidth;
        xw.drawLine(x, 0, x, xw.getHeight());
    }
    for (int i = 0; i <= boardHeight; ++i) {
        int y = i * cellHeight;
        xw.drawLine(0, y, xw.getWidth(), y);
    }

    // Display additional info (score, level)
    xw.drawString(10, xw.getHeight() - 20, "Score: " + std::to_string(board.getScore()));
    xw.drawString(10, xw.getHeight() - 40, "Level: " + std::to_string(board.getLevel()));
}

