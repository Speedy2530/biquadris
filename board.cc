#include "board.h"
#include <iostream>

using namespace std;

Board:Board(unique_ptr<Level> initialLevel, bool textMode) :
    grid{TOTAL_ROWS, vector<Cell>(TOTAL_COLS)},
    currLevel{move(initialLevel)}, 
    origRow{3},
    origCol{0}.
    score{0},
    hiScore{0},
    textMode{textMode},
    gameOver{false},
    currBlockID{-1},
    linesCleared{0},
    currLevelNum{0}
    {
        nextBlock = currLevel->makeNextBlock();
        newBlock();
}


// Helpers
bool Board::fillCells() {
    for (const auto& [relRow, relCol] : blocks[currBlockID]->getRelPos()) {
        int absRow = origRow + relRow;
        int absCol = origCol + relCol;
        grid[absRow][absCol].fill(currBlock->getShape(), currBlockID);
    }
}

int getNewBlockID(vector<unique_ptr<Block>>& blocks, vector<int>& freeBlockIDs) {
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
        int r = row + relRow:
        int c = col + relCol;

        // if out of bounds or conflicting space
        if (r < 0 || r >= TOTAL_ROWS || c < 0 || c >= TOTAL_COLS) return false; 
        if (grid[r][c].isFilled()) return false;

        return true;
    }
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

    originRow = 3;
    originCol = 0;

    fillCells(); // should I do this here?
    if (!placeBlock(*blocks[newBlockID], originRow, originCol)) gameOver = true;

    nextBlock = currentLevel->makeNextBlock();
}

void Board::forceBlock(char shape) {
    blocks[currBlockID] = currentLevel->blockFromShape(shape);
}


bool Board::moveBlockLeft() {
    if (currBlockID == -1) return false;

    newCol = origCol - 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(*blocks[currBlockID], origRow, newCol)) {
        fillCells();
        return false;
    }

    origCol = newCol;
    fillCells();

    return true;
}

bool Board::moveBlockRight() {
    if (currBlockID == -1) return false;

    newCol = origCol + 1;

    removeBlockFromGrid(*blocks[currBlockID], origRow, origCol);

    if (!canPlaceBlock(*blocks[currBlockID], origRow, newCol)) {
        fillCells();
        return false;
    }
    
    origCol = newCol;
    fillCells();

    return true;
}

bool Board::moveBlockDown() {
    if (currBlockID == -1) return false;

    newRow = origRow + 1;

    removeBlockFromGrid(*blocks[currBlockID], origRow, origCol);

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

    return true;
}

bool Board::rotateBlock(string dir) {
    if (currBlockID == -1) return false;

    removeBlockFromGrid(*blocks[currBlockID], origRow, origCol);

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
    // The block is already placed on the grid
    // Update any necessary state if needed
}


// Remove the block from the grid without resetting the unique_ptr
void Board::removeBlockFromGrid(int blockID, int row, int col) {
    if (blockID < 0 || blockID >= blocks.size() || !blocks[blockID]) return;

    for (const auto& [relRow, relCol] : blocks[blockID].getRelPos()) {
        int absRow = row + relRow;
        int absCol = col + relCol;
        grid[absRow][absCol].clear();
    }
}

// // Permanently remove the block from the grid and reset the unique_ptr
// void Board::removeBlockPermanently(int blockID, int row, int col) {
//     if (blockID < 0 || blockID >= blocks.size() || !blocks[blockID]) return;

//     removeBlockFromGrid(blockID);
//     blocks[blockID].reset();
//     freeBlockIDs.push_back(blockID);

//     if (currBlock == blockID) currBlock = -1;
// }


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
                grid[r][c].clear()
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
            if (count == 4 || blocks[blockID].getShape() == '*') {

                int lvl = blocks[blockID].getBlockLevel;
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
        cout << "Level Up! New Level: " << currentLevelNum << endl;
    }

    switch (currLevelNum) {
        case 0:
            currentLevel = make_unique<Level1>();
            break;
        case 1:
            currentLevel = make_unique<Level2>();
            break;
        case 2:
            currentLevel = make_unique<Level3>();
            break;
        case 3:
            currentLevel = make_unique<Level4>();
            break;
        default:
            cout << "No higher level defined. Staying at Level " << currLevelNum << endl;
            break;
    }
}

void Board::levelDown() {
    if (currLevelNum != 0) {
        currLevelNum--;
        cout << "Level Down! New Level: " << currentLevelNum << endl;
    }

    switch (currLevelNum) {
        case 1:
            currentLevel = make_unique<Level0>();
            break;
        case 2:
            currentLevel = make_unique<Level1>();
            break;
        case 3:
            currentLevel = make_unique<Level2>();
            break;
        case 4:
            currentLevel = make_unique<Level3>();
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
    cout << nextBlock->print();
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
    blocks.clear()
    freeBlockIDs.clear()
    clearedIDs.clear()
    currBlock = -1;
    nextBlock = nullptr;
    newBlock();
}


int Board::getCurrBlockID() { return currBlockID; }

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

void Board::updateHiScore() { if (score > hiScore) hiScore = score; }

bool Board::isGameOver() const return gameOver;
