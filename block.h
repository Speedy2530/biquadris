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
        bool heavyFromEffect;
        bool locked;
        int rotated; // 0 1 2 3, representing 90, 0, -90, -180 degrees

        int blockID; // NOT USING THIS ANYMORE
        int blockLevel;

        static int idCounter;

    public:
	Block(bool isCurr, int level, bool isHeavy, int rot)
    	: currBlock(isCurr), heavy(isHeavy), heavyFromEffect(false), locked(false), rotated(rot), blockID(idCounter++), blockLevel(level) {}

        virtual vector <pair <int, int> > getRelPos() const = 0;
        virtual char getShape() const = 0;
        virtual void rotate(string dir) = 0;
        virtual unique_ptr<Block> clone() const = 0;

        bool isHeavy() const { return heavy; }
        bool getHeavyFromEffect() const { return heavyFromEffect; }
        bool isLocked() const { return locked; }
        void setLocked(bool isLocked) { locked = isLocked; }
        void setHeavy(bool isHeavy) { heavy = isHeavy; }
        void setHeavyFromEffect(bool isHeavyFromEffect) { heavyFromEffect = isHeavyFromEffect; }
        bool isCurrBlock() const { return currBlock; }
        void setAsCurrBlock(bool isCurr) { currBlock = isCurr; }
        int getRotation() const { return rotated; }
        void setRotation(int rot) { rotated = rot; }
        int getBlockID() { return blockID; }
        int getBlockLevel() { return blockLevel; }

        virtual void print() const;
        virtual ~Block() = default;
};


#endif

