#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Block.h"
#include "Level.h"
#include "cell.h"

using namespace std;

class Board {
    private:
        vector <vector <Cell> > grid; // 18x11 grid
        unique_ptr<Level> currLevel;
        unique_ptr<Block> currBlock;
        vector <unique_ptr <Block> > blocks;
        int origRow; 
        int origCol; 
        int score;
        int hiScore;
        bool textMode;
        bool gameOver;

        // Helpers
        bool canPlaceBlock(const Block& block, int row, int col) const;
        void lockBlock();
        void clearLines();
        void calculateScore(int linesCleared);
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
        bool rotateBlock(RotationDirection direction);
        bool dropBlock();
        void newBlock();

        // Scoring
        int getScore() const;
        int getHiScore() const;
        void updateHiScore();

        // Display
        void display() const;

        // Game State
        bool isGameOver() const;
};

#endif 
