#include "sblock.h"

using namespace std;

SBlock::SBlock(bool isCurr) : Block{isCurr, 0, false, 0}, shape{'S'} {
    relPos = { {-1, 1}, {-1, 2}, {0, 0}, {0, 1} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > SBlock::getRelPos() const {
    return relPos;
}

char SBlock::getShape() const { return 'S'; }

void SBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0:
                relPos = { {-2, 0}, {-1, 0}, {-1, 1}, {0, 1} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-1, 1}, {-1, 2}, {0, 0}, {0, 1} };
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0:
                relPos = { {-2, 0}, {-1, 0}, {-1, 1}, {0, 1} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-1, 1}, {-1, 2}, {0, 0}, {0, 1} };
                rotated = 0;
                break;
        }
    }
}


// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> SBlock::clone() const {
    return std::make_unique<SBlock>(*this);
}

