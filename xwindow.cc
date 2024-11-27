// xwindow.cc
#include "xwindow.h"
#include <iostream>
#include <algorithm>
#include <climits>

// Constructor
XWindow::XWindow(const Board &board1, const Board &board2) 
    : board1(board1), board2(board2), 
      xw(MARGIN_LEFT + board1.getWidth() * DESIRED_CELL_WIDTH + SPACING + board2.getWidth() * DESIRED_CELL_WIDTH + MARGIN_RIGHT,
          MARGIN_TOP + std::max(board1.getHeight(), board2.getHeight()) * DESIRED_CELL_HEIGHT + INFO_HEIGHT + MARGIN_BOTTOM) {
    
    // Log the window dimensions
    // std::cerr << "Initializing Xwindow with width: " << xw.getWidth() 
    //           << ", height: " << xw.getHeight() << std::endl;

    // Initialize background
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::Pink);
}

// Displays the boards and game state
void XWindow::display(bool player1Turn) {
    // Clear the window
    xw.fillRectangle(0, 0, xw.getWidth(), xw.getHeight(), Xwindow::Pink);

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
                case '*': color = Xwindow::Brown; break;
                default: color = Xwindow::White; break;
            }

            if (cell.isFilled()) {
		// Draw shadow
    		xw.fillRectangle(x + 2, y + 2, cellWidth, cellHeight, Xwindow::Grey);	
                xw.fillRectangle(x, y, cellWidth, cellHeight, color);
		// Draw a border around the cell
    		xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            } else {
                // Draw empty cell border
                xw.fillRectangle(x, y, cellWidth, cellHeight, Xwindow::White);
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
		// Draw shadow
    		xw.fillRectangle(x + 2, y + 2, cellWidth, cellHeight, Xwindow::Grey);	
                xw.fillRectangle(x, y, cellWidth, cellHeight, color);
		// Draw a border around the cell
    		xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            } else {
                // Draw empty cell border
                xw.fillRectangle(x, y, cellWidth, cellHeight, Xwindow::White);
                xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
            }
        }
    }

    // Board dimensions
    int boardWidth1 = board1.getWidth();
    int boardHeight1 = board1.getHeight();
    int boardWidth2 = board2.getWidth();
    int boardHeight2 = board2.getHeight();

    if (player1Turn) {
        xw.drawRectangle(startX1, startY, boardWidth1 * cellWidth, boardHeight1 * cellHeight, Xwindow::Red);
    } else {
        xw.drawRectangle(startX2, startY, boardWidth2 * cellWidth, boardHeight2 * cellHeight, Xwindow::Red);
    }	

    int nextBlockY = MARGIN_TOP + std::max(board1.getHeight(), board2.getHeight()) * DESIRED_CELL_HEIGHT + 20;
    drawNextBlock(board1, MARGIN_LEFT, nextBlockY);
    drawNextBlock(board2, MARGIN_LEFT + board1.getWidth() * DESIRED_CELL_WIDTH + SPACING, nextBlockY);

    // Update additional info (score, level)
    updateInfo();

    // Refresh the window to show updates
    xw.redraw();
}

void XWindow::drawNextBlock(const Board& board, int startX, int startY) {
    const Block* nextBlock = board.getNextBlock();
    if (!nextBlock) return;

    // Get shape and relative positions
    char shape = nextBlock->getShape();
    const auto& relPos = nextBlock->getRelPos();

    // Set cell size
    int cellWidth = DESIRED_CELL_WIDTH;
    int cellHeight = DESIRED_CELL_HEIGHT;

    // Determine color based on block type
    int color;
    switch(shape) {
        case 'I': color = Xwindow::Cyan; break;
        case 'J': color = Xwindow::Blue; break;
        case 'L': color = Xwindow::Orange; break;
        case 'O': color = Xwindow::Yellow; break;
        case 'S': color = Xwindow::Green; break;
        case 'T': color = Xwindow::Purple; break;
        case 'Z': color = Xwindow::Red; break;
        default: color = Xwindow::White; break;
    }

    // Adjust positions to center the block in a 4x4 grid
    int minRow = INT_MAX, minCol = INT_MAX;
    int maxRow = INT_MIN, maxCol = INT_MIN;
    for (const auto& pos : relPos) {
        minRow = std::min(minRow, pos.first);
        maxRow = std::max(maxRow, pos.first);
        minCol = std::min(minCol, pos.second);
        maxCol = std::max(maxCol, pos.second);
    }
    int blockWidth = maxCol - minCol + 1;
    int blockHeight = maxRow - minRow + 1;

    int offsetX = (4 - blockWidth) / 2;
    int offsetY = (4 - blockHeight) / 2;

    // Draw each cell of the block
    for (const auto& pos : relPos) {
        int x = startX + (pos.second - minCol + offsetX) * cellWidth;
        int y = startY + (pos.first - minRow + offsetY) * cellHeight;

        xw.fillRectangle(x, y, cellWidth, cellHeight, color);
        xw.drawRectangle(x, y, cellWidth, cellHeight, Xwindow::Black);
    }

    // Draw a label "Next:"
    xw.drawString(startX, startY, "Next:");
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
    std::string highscoreStr1 = "Highscore: " + std::to_string(board1.getHiScore());
    std::string scoreStr1 = "Score: " + std::to_string(board1.getScore());
    std::string levelStr1 = "Level: " + std::to_string(board1.getLevel());
    xw.drawString(scoreX1, infoStartY, highscoreStr1);
    xw.drawString(scoreX1, infoStartY + 15, scoreStr1);
    xw.drawString(levelX1, infoStartY + 30, levelStr1);

    // Draw score and level for player 2
    std::string highscoreStr2 = "Highscore: " + std::to_string(board2.getHiScore());
    std::string scoreStr2 = "Score: " + std::to_string(board2.getScore());
    std::string levelStr2 = "Level: " + std::to_string(board2.getLevel());
    xw.drawString(scoreX2, infoStartY, highscoreStr2);
    xw.drawString(scoreX2, infoStartY + 15, scoreStr2);
    xw.drawString(levelX2, infoStartY + 30, levelStr2);
}
