#include "board.h"
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board(unique_ptr<Level> initialLevel, bool textMode, string seqFile) :
    grid{TOTAL_ROWS, vector<Cell>(TOTAL_COLS)},
    currLevel{move(initialLevel)}, 
    origRow{3},
    origCol{0},
    score{0},
    hiScore{0},
    textMode{textMode},
    currBlockID{-1},
    gameOver{false},
    blocksSinceClear{0},
    linesCleared{0},
    currLevelNum{0},
    seqFile{seqFile},
    blocks{100}
    {
        nextBlock = currLevel->makeNextBlock(blocksSinceClear);
        newBlock();
}


// Helpers
void Board::fillCells() {
    if (currBlockID == -1 || currBlockID >= static_cast<int>(blocks.size()) || !blocks[currBlockID]) return;

    for (const auto& [relRow, relCol] : blocks[currBlockID]->getRelPos()) {
        int absRow = origRow + relRow;
        int absCol = origCol + relCol;
        grid[absRow][absCol].fill(blocks[currBlockID]->getShape(), currBlockID);
    }
}

int Board::getNewBlockID(vector<unique_ptr<Block>>& blocks, vector<int>& freeBlockIDs) const {
    if (!freeBlockIDs.empty()) {
        int id = freeBlockIDs.back();
        freeBlockIDs.pop_back();
        return id;
    } else {
        blocks.emplace_back(nullptr); // Placeholder
        return blocks.size() - 1;
    }
}

// row and col in the params represent the "bottom left" position of the block on the board
bool Board::canPlaceBlock(const Block& block, int row, int col) const {
    for (const auto& [relRow, relCol] : block.getRelPos()) {
        int r = row + relRow;
        int c = col + relCol;

        // if out of bounds or conflicting space
        if (r < 0 || r >= TOTAL_ROWS || c < 0 || c >= TOTAL_COLS) return false; 
        if (grid[r][c].isFilled()) return false;
    }

    return true;
}

// bool Board::placeBlock(unique_ptr<Block> block, int row, int col) {
//     if (!canPlaceBlock(*block, row, col)) {
//         gameOver = true;
//         return false;
//     }

//     int blockID = getNewBlockID(blocks, freeBlockIDs);
//     blocks[blockID] = move(block);
//     currBlock = blockID;

//     // Place the block on the grid
//     fillCells();

//     origRow = row;
//     origCol = col;

//     return true;
// }


// // Important methods
void Board::newBlock() {
    int newBlockID = getNewBlockID(blocks, freeBlockIDs);
    blocks[newBlockID] = move(nextBlock);
    currBlockID = newBlockID; 

    origRow = 3;
    origCol = 0;

    if (!canPlaceBlock(*blocks[newBlockID], origRow, origCol)) {
        gameOver = true;
        return;
    }

    fillCells();
    nextBlock = currLevel->makeNextBlock(blocksSinceClear);
    blocksSinceClear++;
}

void Board::forceBlock(char shape) {
    blocks[currBlockID] = currLevel->blockFromShape(shape);
}

bool Board::moveBlockLeft() {
    if (currBlockID == -1) return false;

    int newCol = origCol - 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(*blocks[currBlockID], origRow, newCol)) {
        fillCells();
        return false;
    }

    origCol = newCol;
    fillCells();
    if (blocks[currBlockID]->isHeavy()) {
        moveBlockDown();
        if (!blocks[currBlockID]->isLocked()) moveBlockDown();
    }

    return true;
}

bool Board::moveBlockRight() {
    if (currBlockID == -1) return false;

    int newCol = origCol + 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(*blocks[currBlockID], origRow, newCol)) {
        fillCells();
        return false;
    }
    
    origCol = newCol;

    fillCells();
    if (blocks[currBlockID]->isHeavy()) {
        moveBlockDown();
        if (!blocks[currBlockID]->isLocked()) moveBlockDown();
    }

    return true;
}

bool Board::moveBlockDown() {
    if (currBlockID == -1) return false;

    int newRow = origRow + 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(*blocks[currBlockID], newRow, origCol)) {
        // Can no longer go down, lock the block
        fillCells();
        lockBlock();
        clearLines();
        newBlock();
        return false;
    }

    origRow = newRow;
    fillCells();

    // edge case
    if (!canPlaceBlock(*blocks[currBlockID], origRow, origCol+1) && !canPlaceBlock(*blocks[currBlockID], origRow, origCol-1)
        && !canPlaceBlock(*blocks[currBlockID], origRow-1, origCol)) {
            lockBlock();
            clearLines();
            newBlock();
    }

    return true;
}

bool Board::rotateBlock(const string& dir) {
    if (currBlockID == -1) return false;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    blocks[currBlockID]->rotate(dir);

    if (canPlaceBlock(*blocks[currBlockID], origRow, origCol)) {
        fillCells();

        return true;
    }
    else {
        string oppositeDir = "";
        if (dir == "clockwise") oppositeDir = "counterclockwise";
        else oppositeDir = "clockwise";
        
        // revert the relative position rotation if it doesn't work
        blocks[currBlockID]->rotate(oppositeDir);
        fillCells();

        return false;
    }
}

bool Board::dropBlock() {
    if (currBlockID == -1) return false;

    while (moveBlockDown()) {
        // Keep moving down until it can't
    }

    return true;
}

void Board::lockBlock() {
    blocks[currBlockID].setLock(true);
}


// Remove the block from the grid without resetting the unique_ptr
void Board::removeBlockFromGrid(int blockID, int row, int col) {
    if (blockID < 0 || blockID >= static_cast<int>(blocks.size()) || !blocks[blockID]) return;

    for (const auto& [relRow, relCol] : blocks[blockID]->getRelPos()) {
        int absRow = row + relRow;
        int absCol = col + relCol;
        grid[absRow][absCol].clear();
    }
}

void Board::clearLines() {
    for (int r = 0; r < TOTAL_ROWS; r++) {
        bool isFullLine = true;
        vector<int> blockIDs = {};

        for (int c = 0; c < TOTAL_COLS; c++) {
            if (!grid[r][c].isFilled()) {
                isFullLine = false;
                break;
            }
            blockIDs.push_back(grid[r][c].getBlockID());
        }

        if (isFullLine) {
            linesCleared++;
            clearedBlockIDs.insert(clearedBlockIDs.end(), blockIDs.begin(), blockIDs.end());

            for (int c = 0; c < TOTAL_COLS; c++) {
                grid[r][c].clear();
            }

            for (int rowToMove = r; rowToMove < TOTAL_ROWS - 1; ++rowToMove) {
                for (int c = 0; c < TOTAL_COLS; ++c) {
                    grid[rowToMove][c].fill(grid[rowToMove + 1][c].getShape(), grid[rowToMove + 1][c].getBlockID());
                    grid[rowToMove + 1][c].clear();
                }
            }

            r--;
        }
    }

    if (linesCleared > 0) {
        // Count occurrences of each blockID
        unordered_map<int, int> blockCount;
        for (int id : clearedBlockIDs) {
            blockCount[id]++;
        }

        // Check for blocks that have all their cells cleared (appear 4 times)
        for (const auto& [blockID, count] : blockCount) {

            // If cleared block
            if (count == 4 || blocks[blockID]->getShape() == '*') {

                int lvl = blocks[blockID]->getBlockLevel();
                score += (lvl + 1) * (lvl + 1); // add level

                // remove the relevant blockID instances from the clearedBlockIDs list
                clearedBlockIDs.erase(
                std::remove(clearedBlockIDs.begin(), clearedBlockIDs.end(), blockID),
                clearedBlockIDs.end()
                );

                // clear the block from the blocks list
                blocks[blockID].reset();
                freeBlockIDs.push_back(blockID);
            }
        }

        blocksSinceClear = 0;
        linesCleared = 0;

        // Update the score based on lines cleared
        calculateScore(linesCleared);
    }
}


// Scoring CHECK
void Board::calculateScore(int linesCleared) {
    int points = (currLevel->getLevelNum() + linesCleared) * (currLevel->getLevelNum() + linesCleared);
    score += points;

    if (score > hiScore) hiScore = score;
}

// Levels

void Board::levelUp() {
    if (currLevelNum < 4) {
        currLevelNum++;
        cout << "Level Up! New Level: " << currLevelNum << endl;
    }

    switch (currLevelNum) {
        case 0:
            currLevel = make_unique<Level1>();
            break;
        case 1:
            currLevel = make_unique<Level2>();
            break;
        case 2:
            currLevel = make_unique<Level3>(seqFile);
            break;
        case 3:
            currLevel = make_unique<Level4>(seqFile);
            break;
        default:
            cout << "No higher level defined. Staying at Level " << currLevelNum << endl;
            break;
    }
}

void Board::levelDown() {
    if (currLevelNum != 0) {
        currLevelNum--;
        cout << "Level Down! New Level: " << currLevelNum << endl;
    }

    switch (currLevelNum) {
        case 1:
            currLevel = make_unique<Level0>(seqFile);
            break;
        case 2:
            currLevel = make_unique<Level1>();
            break;
        case 3:
            currLevel = make_unique<Level2>();
            break;
        case 4:
            currLevel = make_unique<Level3>(seqFile);
            break;
        default:
            cout << "No Lower level defined. Staying at Level " << currLevelNum << endl;
            break;
    }
}


void Board::display() const {
    for (int r = TOTAL_ROWS - 1; r >= 0; r--) {
        cout << "|";
        for (int c = 0; c < TOTAL_COLS; ++c) {
            cout << grid[r][c].getShape();
        }
        cout << "|\n";
    }

    // Print the bottom border
    cout << "+";
    for (int c = 0; c < TOTAL_COLS; ++c) {
        cout << "-";
    }
    cout << "+\n";

    // Print score and hi score
    cout << "Score: " << score << "  Hi-Score: " << hiScore << "\n";
    nextBlock->print();
}


void Board::reset() {
    // Clear the grid
    for (int r = 0; r < TOTAL_ROWS; ++r) {
        for (int c = 0; c < TOTAL_COLS; ++c) {
            grid[r][c].clear();
        }
    }

    score = 0;
    gameOver = false;
    blocks.clear();
    freeBlockIDs.clear();
    clearedBlockIDs.clear();
    currBlockID = -1;
    nextBlock = nullptr;
    newBlock();
}


int Board::getCurrBlockID() const { return currBlockID; }

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

void Board::updateHiScore() { if (score > hiScore) hiScore = score; }

bool Board::isGameOver() const { return gameOver; }
