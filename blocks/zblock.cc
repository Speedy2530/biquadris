#include "zblock.h"

using namespace std;

ZBlock::ZBlock(bool isCurr) : Block{isCurr, 0, false, 0}, shape{'Z'} {
    relPos = { {-1, 0}, {-1, 1}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > ZBlock::getRelPos() const {
    return relPos;
}

char ZBlock::getShape() const { return 'Z'; }

void ZBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0: // Rotate 0° -> 90°
                relPos = { {0, 1}, {-1, 0}, {-1, 1}, {-2, 0} }; // Vertical Z
                rotated = 1;
                break;
            case 1: // Rotate 90° -> 0°
                relPos = { {0, 0}, {0, 1}, {-1, 1}, {-1, 2} }; // Horizontal Z
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0: // Rotate 0° -> 90°
                relPos = { {0, 1}, {-1, 0}, {-1, 1}, {-2, 0} }; // Vertical Z
                rotated = 1;
                break;
            case 1: // Rotate 90° -> 0°
                relPos = { {0, 0}, {0, 1}, {-1, 1}, {-1, 2} }; // Horizontal Z
                rotated = 0;
                break;
        }
    }
}


// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> ZBlock::clone() const {
    return std::make_unique<ZBlock>(*this);
}
