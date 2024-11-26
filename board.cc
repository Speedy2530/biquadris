#include "board.h"

using namespace std;

Board:Board(unique_ptr<Level> initialLevel, bool textMode) :
    grid{TOTAL_ROWS, vector<Cell>(TOTAL_COLS)},
    currLevel{move(initialLevel)}, 
    origRow{3},
    origCol{0}.
    score{0},
    hiScore{0},
    textMode{textMode},
    gameOver{false} 
    {
        newBlock();
}

bool Board::placeBlock(unique_ptr<Block> block) {
    if (!canPlaceBlock(*block, origRow, origCol)) {
        gameOver = true;
        return false;
    }

    currBlock = move(block);

    // Place the block on the grid
    fillCells();

    return true;
}

// Helper
// row and col in the params represent the "bottom left" position of the block on the board
bool Board::canPlaceBlock(const Block& block, int row, int col) const {
    for (const auto& [relRow, relCol] : block.getRelPos()) {
        int r = row + relRow:
        int c = col + relCol;

        // if out of bounds or conflicting space
        if (r < 0 || r >= TOTAL_ROWS || c < 0 || c >= TOTAL_COLS) return false; 
        if (grid[r][c].isFilled()) return false;

        return true;
    }
}

// Helper
bool Board::fillCells() {
    for (const auto& [relRow, relCol] : currBlock->getRelPos()) {
        int absRow = origRow + relRow;
        int absCol = origCol + relCol;
        grid[absRow][absCol].fill(currBlock->getShape());
    }
}

bool Board::moveBlockLeft() {
    if (!currBlock) return false;

    newCol = origCol - 1;

    if (!canPlaceBlock(*currBlock, origRow, newCol)) return false;

    removeBlock(*currBlock, origRow, origCol);
    origCol = newCol;
    fillCells();
}

bool Board::moveBlockRight() {
    if (!currBlock) return false;

    newCol = origCol + 1;

    if (!canPlaceBlock(*currBlock, origRow, newCol)) return false;

    removeBlock(*currBlock, origRow, origCol);
    origCol = newCol;
    fillCells();
}

bool Board::moveBlockDown() {
    if (!currBlock) return false;

    newRow = origRow + 1;

    if (!canPlaceBlock(*currBlock, newRow, origCol)) {
        // Can no longer go down, lock the block
        lockBlock();
        clearLines();
        newBlock();
        return false;
    }

    removeBlock(*currBlock, origRow, origCol);
    origRow = newRow;
    fillCells();
}

bool Board::rotateBlock(string dir) {
    if (!currBlock) return false;

    removeBlock(*currBlock, origRow, origCol);

    currBlock->rotate(dir);

    if (canPlaceBlock(*currBlock, origRow, origCell)) {
        fillCells();
        return true;
    }
    else {
        string oppositeDir = ""
        if (dir == "clockwise") oppositeDir = "counterclockwise";
        else oppositeDir = "clockwise";
        
        // revert the relative position rotation if it doesn't work
        currBlock->rotate(oppositeDir);

        // replace the block at its original position
        fillCells();

        return false;
    }
}

bool Board::dropBlock() {
    if (!currBlock) return false;

    while (moveBlockDown()) {
        // Keep moving down until it can't
    }

    return true;
}

void Board::lockBlock() {
    // The block is already placed on the grid
    // Update any necessary state if needed
}

void Board::newBlock() {
    unique_ptr<Block> newBlock = currLevel->makeNextBlock();

    // Reset bottom left origin to (3, 0) 
    origRow = 3;
    origCol = 0;

    if (!placeBlock(move(newBlock), origRow, origCol)) gameOver = true;
}


void Board::clearLines() {
    int linesCleared = 0;

    for (int r = 0; r < TOTAL_ROWS; r++) {
        bool fullLine = true;
        for (int c = 0; c < TOTAL_COLS; c++) {
            if (!grid[r][c].isFilled()) {
                fullLine = false;
                break;
            }
        }

        if (fullLine) {
            linesCleared++;
            // Clear the line
            for (int c = 0; c < TOTAL_COLS; c++) {
                grid[r][c].clear();
            }

            // Move all rows above down by one
            // DOUBLE CHECK THIS IDK IF IT WORKS
            for (int moveRow = r; moveRow < TOTAL_ROWS - 1; moveRow++) {
                for (int c = 0; c < TOTAL_COLS; c++) {
                    grid[moveRow][c].fill(grid[moveRow + 1][c].getShape());
                    grid[moveRow + 1][c].clear();
                }
            }

            // Recheck the same row
            r--;
        }
    }

    if (linesCleared > 0) {
        calculateScore(linesCleared);
    }
}

// Scoring  CHECK THIS AS WELL
void Board::calculateScore(int linesCleared) {
    int points = (currentLevel->getLevelNum() + linesCleared) * 
                 (currentLevel->getLevelNum() + linesCleared);
    score += points;

    // Update high score if necessary
    if (score > hiScore) {
        hiScore = score;
    }
}


// COPIED FROM CHAT

void Board::removeBlock(const Block& block, int row, int col) {
    for (const auto& [relRow, relCol] : block.getRelPos()) {
        int absRow = row + relRow;
        int absCol = col + relCol;
        grid[absRow][absCol].clear();
    }
}

#include <iostream>

void Board::display() const {
    for (int r = TOTAL_ROWS - 1; r >= 0; --r) {
        std::cout << "|";
        for (int c = 0; c < TOTAL_COLS; ++c) {
            if (grid[r][c].isOccupied()) {
                std::cout << grid[r][c].getShape();
            } else {
                std::cout << " ";
            }
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
    std::cout << "Score: " << score << "  Hi-Score: " << hiScore << "\n";
}


int Board::getScore() const {
    return score;
}

int Board::getHiScore() const {
    return hiScore;
}

void Board::updateHiScore() {
    if (score > hiScore)
        hiScore = score;
}

void Board::reset() {
    // Clear the grid
    for (int r = 0; r < TOTAL_ROWS; ++r) {
        for (int c = 0; c < TOTAL_COLS; ++c) {
            grid[r][c].clear();
        }
    }

    // Reset scores
    score = 0;

    // Reset game state
    gameOver = false;

    // Generate a new block
    newBlock();
}



bool Board::isGameOver() const return gameOver;




        // Helpers
        void lockBlock();
        void clearLines();
        void calculateScore(int linesCleared);
        void reset();

        // Scoring
        int getScore() const;
        int getHiScore() const;
        void updateHiScore();

        // Display
        void display() const;