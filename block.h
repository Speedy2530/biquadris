#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "cell.h"

using namespace std;

class Block {
    protected:
        vector <pair <int, int> > relPos;
        bool currBlock;
        bool heavy;
        int rotated; // 0 1 2 3
    public:
        Block(bool isCurr = false, bool isHeavy = false, int rot = 0)
        : currBlock(isCurr), heavy(isHeavy), rotation(rot) {}

        virtual vector <pair <int, int> > getRelPos() const = 0;
        virtual char getShape() const = 0;
        virtual void rotate(string dir) = 0;
        virtual unique_ptr<Block> clone() const = 0;

        bool isHeavy() const { return heavy; }
        void setHeavy(bool isHeavy) { heavy = isHeavy; }
        bool isCurrentBlock() const { return currentBlock; }
        void setAsCurrentBlock(bool isCurr) { currentBlock = isCurr; }
        int getRotation() const { return rotation; }
        void setRotation(int rot) { rotation = rot; }

        void print() const;
        virtual ~Block() = default;
};


#endif