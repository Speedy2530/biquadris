#include "lblock.h"

using namespace std;

LBlock::LBlock(bool isCurr) : Block{isCurr, 0, false, 0}, shape{'L'} {
    relPos = { {-1, 2}, {0, 0}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > LBlock::getRelPos() const {
    return relPos;
}

char LBlock::getShape() const { return 'L'; }

void LBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0:
                relPos = { {-2, 0}, {-1, 0}, {0, 0}, {0, 1} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 0} };
                rotated = 2;
                break;
            case 2:
                relPos = { {0, 0}, {0, 1}, {-1, 1}, {-2, 1} };
                rotated = 3;
                break;
            case 3:
                relPos = { {0, 0}, {0, 1}, {0, 2}, {-1, 2} };
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0:
                relPos = { {0, 0}, {0, 1}, {0, 2}, {-1, 2} };
                rotated = 3;
                break;
            case 3:
                relPos = { {0, 0}, {0, 1}, {-1, 1}, {-2, 1} };
                rotated = 2;
                break;
            case 2:
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 0} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-2, 0}, {-1, 0}, {0, 0}, {0, 1} };
                rotated = 0;
                break;
        }
    }
}


// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> LBlock::clone() const {
    return std::make_unique<LBlock>(*this);
}
