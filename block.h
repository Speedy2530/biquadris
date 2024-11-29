#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "cell.h"

using namespace std;

class Block {
    protected:
        int blockLevel;
        bool heavy;
        int rotated; // 0 1 2 3, representing 90, 0, -90, -180 degrees
        char shape;
        bool locked;
        bool heavyFromEffect;
        vector <pair <int, int> > relPos; // bottom left is {0, 0}

        static int idCounter;

    public:
	Block(int level, bool isHeavy, int rot, char shape)
    	: blockLevel(level), heavy(isHeavy), rotated(rot), shape{shape}, locked(false), heavyFromEffect(false) {}

        virtual vector <pair <int, int> > getRelPos() const = 0;
        virtual void rotate(string dir) = 0;

        char getShape() const { return shape; }
        bool isHeavy() const { return heavy; }
        bool getHeavyFromEffect() const { return heavyFromEffect; }
        bool isLocked() const { return locked; }
        void setLocked(bool isLocked) { locked = isLocked; }
        void setHeavy(bool isHeavy) { heavy = isHeavy; }
        void setHeavyFromEffect(bool isHeavyFromEffect) { heavyFromEffect = isHeavyFromEffect; }
        int getRotation() const { return rotated; }
        void setRotation(int rot) { rotated = rot; }
        int getBlockLevel() { return blockLevel; }
        void setBlockLevel(int level) { blockLevel = level; }

        virtual void print() const;
        virtual ~Block() = default;
};


#endif

