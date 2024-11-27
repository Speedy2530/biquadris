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

class Board {
    private:
        vector <vector <Cell> > grid; // 18x11 grid
        unique_ptr<Level> currLevel;
        unique_ptr<Block> nextBlock;

        vector < unique_ptr <Block> > blocks; // list of blocks with index as IDs
        vector <int> freeBlockIDs; // free IDs within the blocks vector for reuse
        int currBlockID;

        vector <int> clearedBlockIDs; // list of block IDs that have been cleared (1 per cell)

        int origRow; 
        int origCol; 
        int score;
        int hiScore;
        int linesCleared;
        int currLevelNum;
        bool textMode;
        bool gameOver;

        // Helpers
        void fillCells();
        bool canPlaceBlock(const Block& block, int row, int col) const;
        void lockBlock();
        void removeBlockFromGrid(int blockID, int row, int col);
        void clearLines();
        void calculateScore(int linesCleared);
        int getNewBlockID(vector<unique_ptr<Block>>& blocks, vector<int>& freeBlockIDs);
        void reset();

    public:
        static const int TOTAL_ROWS = 18; // 15 playable rows + 3 reserve rows
        static const int TOTAL_COLS = 11;

        Board(unique_ptr<Level> initialLevel, bool textMode = false);
        ~Board() = default;

        // Block Management
        bool placeBlock(unique_ptr<Block> block);
        bool moveBlockLeft();
        bool moveBlockRight();
        bool moveBlockDown();
        bool rotateBlock(string dir);
        bool dropBlock();
        void newBlock();

        // Levels
        void levelUp();
        void levelDown();

        // Scoring
        int getScore() const;
        int getHiScore() const;
        int getCurrBlockID() const;
        void updateHiScore();

        // Display
        void display() const;

        // Game State
        bool isGameOver() const;
};

#endif 
