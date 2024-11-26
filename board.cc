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

bool Board::isGameOver() return gameOver;


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