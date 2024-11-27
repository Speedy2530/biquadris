#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "cell.h"
#include "block.h"
#include "level.h"
#include "levels/all_levels.h"

using namespace std;

class Cell;
class Block;
class Level;

class Board {
    private:
        vector <vector <Cell> > grid; // 18x11 grid
        unique_ptr<Level> currLevel;
        unique_ptr<Block> nextBlock;

        vector < unique_ptr <Block> > blocks; // list of blocks with index as IDs
        vector <int> freeBlockIDs; // free IDs within the blocks vector for reuse
        int currBlockID;
        bool gameOver;

        vector <int> clearedBlockIDs; // list of block IDs that have been cleared (1 per cell)

        string seqFile;
        int origRow; 
        int origCol; 
        int score;
        int hiScore;
        int blocksSinceClear;
        int linesCleared;
        int currLevelNum;
        bool textMode;

        // Helpers
        void fillCells();
        bool canPlaceBlock(int row, int col) const;
        void lockBlock();
        void removeBlockFromGrid(int blockID, int row, int col);
        void clearLines();
        void calculateScore(int linesCleared);
        int getNewBlockID();

    public:
        static const int TOTAL_ROWS = 18; // 15 playable rows + 3 reserve rows
        static const int TOTAL_COLS = 11;

        Board(unique_ptr<Level> initialLevel, bool textMode = false, string seqFile = "");
        ~Board() = default;

        // Block Management
        bool placeBlock(unique_ptr<Block> block);
        bool moveBlockLeft();
        bool moveBlockRight();
        bool moveBlockDown();
        bool rotateBlock(const string& dir);
        bool dropBlock();
        void newBlock();
        void forceBlock(char s);
        void setCellsBlind(bool isBlind);

        // Levels
        void levelUp();
        void levelDown();
        void setRandom(bool isRand);
        void setSeed(int seed);

        // Scoring
        int getScore() const;
        int getHiScore() const;
        void updateHiScore();

        int getCurrBlockID() const;
        const vector < unique_ptr <Block> > &getBlocks() const;

        // Display
        void display() const;

        // Game State
        bool isGameOver() const;
        void reset();
	
	// ** New Accessor Methods for XWindow **
        int getWidth() const { return TOTAL_COLS; }
        int getHeight() const { return TOTAL_ROWS; }
        const Cell& getCell(int row, int col) const { return grid[row][col]; }
        int getLevel() const { return currLevelNum; }
};

#endif 
