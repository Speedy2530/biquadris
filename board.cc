#include "board.h"
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board(unique_ptr<Level> initialLevel, bool textMode, string seqFile) :
    grid(TOTAL_ROWS, vector<Cell>(TOTAL_COLS)),
    currLevel(move(initialLevel)),
    nextBlock(nullptr),
    blocks(0),
    freeBlockIDs(),
    currBlockID(-1),
    gameOver(false),
    clearedBlockIDs(),
    blockLockedDuringLastMove{false},
    seqFile(seqFile),
    origRow(3),
    origCol(0),
    score(0),
    hiScore(0),
    blocksSinceClear(0),
    linesCleared(0),
    currLevelNum(0),
    initialLevel{currLevel->getLevelNum()},
    textMode(textMode)
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
        if (absRow >= 0 && absRow < TOTAL_ROWS && absCol >= 0 && absCol < TOTAL_COLS) {
            grid[absRow][absCol].fill(blocks[currBlockID]->getShape(), currBlockID);
        }
        else {
            cerr << "Weird thing in fillCells happening." << endl;
        }
    }
}

int Board::getNewBlockID() {
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
bool Board::canPlaceBlock(int row, int col) const {
    if (currBlockID == -1 || currBlockID >= static_cast<int>(blocks.size()) || !blocks[currBlockID]) {
        return false;
    }

    for (const auto& [relRow, relCol] : blocks[currBlockID]->getRelPos()) {
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
    int newBlockID = getNewBlockID();
    blocks[newBlockID] = move(nextBlock);
    currBlockID = newBlockID; 

    origRow = 3;
    origCol = 0;

    if (!canPlaceBlock(origRow, origCol)) {
        gameOver = true;
        return;
    }

    nextBlock = currLevel->makeNextBlock(blocksSinceClear);

    // Conditions for dropping *
    if ((blocks[currBlockID]->getShape() == '*') && (blocksSinceClear == 0)) {
        blocks[currBlockID] = move(nextBlock);
        nextBlock = currLevel->makeNextBlock(blocksSinceClear);
    }
    else if (blocks[currBlockID]->getShape() == '*') {
        dropBlock();
    }

    fillCells();

    if (!nextBlock) {
        cerr << "Error: nextBlock is null." << endl;
        return;
    }
}

void Board::forceBlock(char shape) {
    bool isHeavy = blocks[currBlockID]->isHeavy();
    removeBlockFromGrid(currBlockID, origRow, origCol);
    blocks[currBlockID] = currLevel->blockFromShape(shape);
    blocks[currBlockID]->setHeavy(isHeavy);
    if (!canPlaceBlock(origRow, origCol)) {
        gameOver = true;
        return;
    }
    fillCells();
}


bool Board::moveBlockLeft() {
    if (currBlockID == -1) return false;

    int newCol = origCol - 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(origRow, newCol)) {
        fillCells();
        return false;
    }

    origCol = newCol;
    fillCells();

    if (!blocks[currBlockID]->isHeavy()) {
        fillCells();
    }
    else {
        moveBlockDown();
        if (blocks[currBlockID]->getHeavyFromEffect()) moveBlockDown();
    }

    return true;
}

bool Board::moveBlockRight() {
    if (currBlockID == -1 || !blocks[currBlockID]) return false;

    int newCol = origCol + 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    if (!canPlaceBlock(origRow, newCol)) {
        fillCells();
        return false;
    }
    
    origCol = newCol;

    if (!blocks[currBlockID]->isHeavy()) {
        fillCells();
    }
    else {
        moveBlockDown();
        if (blocks[currBlockID]->getHeavyFromEffect()) moveBlockDown();
    }

    return true;
}

bool Board::moveBlockDown() {
    if (currBlockID == -1 || !blocks[currBlockID]) return false;

    int newRow = origRow + 1;

    removeBlockFromGrid(currBlockID, origRow, origCol);

       if (!canPlaceBlock(newRow, origCol)) {
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
    // if (!canPlaceBlock(origRow, origCol+1) && !canPlaceBlock(origRow, origCol-1)
    //     && !canPlaceBlock(origRow+1, origCol)) {
    //         lockBlock();
    //         clearLines();
    //         newBlock();
    // }

    return true;
}

bool Board::rotateBlock(const string& dir) {
    if (currBlockID == -1) return false;

    removeBlockFromGrid(currBlockID, origRow, origCol);

    blocks[currBlockID]->rotate(dir);

    if (canPlaceBlock(origRow, origCol)) {
        if (!blocks[currBlockID]->isHeavy()) {
            fillCells();
        }
        else {
            moveBlockDown();
            if (blocks[currBlockID]->getHeavyFromEffect()) moveBlockDown();
        }

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
    if (currBlockID == -1 || !blocks[currBlockID]) return false;

    while (moveBlockDown()) {
        // Keep moving down until it can't
    }

    return true;
}

void Board::lockBlock() {
    blocks[currBlockID]->setLocked(true);
    blockLockedDuringLastMove = true;
    blocksSinceClear++;
}

bool Board::isCurrentBlockLocked() {
    return blocks[currBlockID]->isLocked();
}

void Board::setBlockLockedDuringLastMove(bool lock) {
    blockLockedDuringLastMove = lock;
}

// Remove the block from the grid without resetting the unique_ptr
void Board::removeBlockFromGrid(int blockID, int row, int col) {
    if (blockID < 0 || blockID >= static_cast<int>(blocks.size()) || !blocks[blockID]) return;

    for (const auto& [relRow, relCol] : blocks[blockID]->getRelPos()) {
        int absRow = row + relRow;
        int absCol = col + relCol;
        if (absRow >= 0 && absRow < TOTAL_ROWS && absCol >= 0 && absCol < TOTAL_COLS) {
            grid[absRow][absCol].clear();
        }
        else {
            cerr << "weird thing happening when clearing block from grid" << endl;
        }
    }
}

void Board::clearLines() {
    linesCleared = 0;
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

            // Shift all rows above down by one
            for (int rowToMove = r; rowToMove > 0; --rowToMove) {
                for (int c = 0; c < TOTAL_COLS; ++c) {
                    grid[rowToMove][c].fill(
                        grid[rowToMove - 1][c].getShape(),
                        grid[rowToMove - 1][c].getBlockID()
                    );
                }
            }

            // Clear the topmost row after shifting
            for (int c = 0; c < TOTAL_COLS; ++c) {
                grid[0][c].clear();
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
                remove(clearedBlockIDs.begin(), clearedBlockIDs.end(), blockID),
                clearedBlockIDs.end()
                );

                // clear the block from the blocks list
                blocks[blockID].reset();
                freeBlockIDs.push_back(blockID);
            }
        }

        blocksSinceClear = 0;

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
    if (currLevelNum >= 4) {
        cerr << "Level too high to level up" << endl;
        return;
    }
    else {
        currLevelNum++;
        cout << "Level Up! New Level: " << currLevelNum << endl;
    }
    
    setLevel(currLevelNum);

    if (currLevelNum == 4 || currLevelNum == 3) {
        blocks[currBlockID]->setHeavy(true);
        nextBlock->setHeavy(true);
    }
}

void Board::levelDown() {
    if (currLevelNum == 0) {
        cerr << "Level too low to level down" << endl;
        return;
    }
    else {
        currLevelNum--;
        cout << "Level Down! New Level: " << currLevelNum << endl;
    }
    setLevel(currLevelNum);

    if (currLevelNum < 3) {
        nextBlock->setHeavy(false);
        if (!blocks[currBlockID]->getHeavyFromEffect()) {
            blocks[currBlockID]->setHeavy(false);
        }
    }
}

void Board::setLevel(int level) {
    if (level >= 0 && level <= 4) currLevelNum = level;
    
    switch (currLevelNum) {
        case 0:
            currLevel = make_unique<Level0>(seqFile);
            break;
        case 1:
            currLevel = make_unique<Level1>();
            break;
        case 2:
            currLevel = make_unique<Level2>();
            break;
        case 3:
            currLevel = make_unique<Level3>(seqFile);
            break;
        case 4:
            currLevel = make_unique<Level4>(seqFile);
            break;
        default:
            break;
    }
}

void Board::setLevelFile(string file) {
    if (currLevelNum == 3) {
        currLevel = make_unique<Level3>(file);
    }
    else if (currLevelNum == 4) {
        currLevel = make_unique<Level4>(file);
    }
    currLevel->setRand(false);
}


// Testing purposes, prints one board
void Board::display() const {
    for (int r = 0; r < TOTAL_ROWS; r++) {
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
    cout << "Score: " << score << "  Hi-Score: " << hiScore << endl;
    
    if (nextBlock) {
        cout << "Next Block:" << endl;
        nextBlock->print();
    } else {
        cout << "No next block available.\n";
    }
}

void Board::setCellsBlind(bool isBlind) {
    for (int r = 2; r < 12; r++) {
        for (int c = 2; c < 9; c++) {
            grid[r][c].setBlind(isBlind);
        }
    }
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
    blocksSinceClear = 0;
    currLevelNum = initialLevel;
    setLevel(currLevelNum);

    nextBlock = currLevel->makeNextBlock(blocksSinceClear);
    newBlock();
}


int Board::getCurrBlockID() const { return currBlockID; }

const vector < unique_ptr <Block> > &Board::getBlocks() const { return blocks; }

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

void Board::updateHiScore() { if (score > hiScore) hiScore = score; }

int Board::getLinesCleared() const { return linesCleared; }

bool Board::wasBlockLockedDuringLastMove() const { return blockLockedDuringLastMove; }

void Board::setRandom(bool isRand) { currLevel->setRand(isRand); };

void Board::setSeed(int seed) { currLevel->setSeed(seed); };

bool Board::isGameOver() const { return gameOver; }

const Block* Board::getNextBlock() const {
    return nextBlock.get();
}