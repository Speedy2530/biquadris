#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "cell.h"

using namespace std;

class Block {
    protected:
        vector <pair <int, int> > relPos; // bottom left is {0, 0}
        bool currBlock;
        bool heavy;
        int rotated; // 0 1 2 3, representing 90, 0, -90, -180 degrees
    public:
        Block(bool isCurr = false, bool isHeavy = false, int rot = 0)
        : currBlock(isCurr), heavy(isHeavy), rotated(rot) {}

        virtual vector <pair <int, int> > getRelPos() const = 0;
        virtual char getShape() const = 0;
        virtual void rotate(string dir) = 0;
        virtual unique_ptr<Block> clone() const = 0;

        bool isHeavy() const { return heavy; }
        void setHeavy(bool isHeavy) { heavy = isHeavy; }
        bool isCurrBlock() const { return currBlock; }
        void setAsCurrBlock(bool isCurr) { currBlock = isCurr; }
        int getRotation() const { return rotated; }
        void setRotation(int rot) { rotated = rot; }

        void print() const;
        virtual ~Block() = default;
};


#endif