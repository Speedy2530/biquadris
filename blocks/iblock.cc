#include "iblock.h"

using namespace std;

IBlock::IBlock(bool isCurr) : Block{isCurr}, shape{'I'} {
    relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > IBlock::getRelPos() const {
    return relPos;
}

char IBlock::getShape() const { return 'I'; }

void IBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0:
                relPos = { {0, 0}, {-1, 0}, {-2, 0}, {-3, 0} };
                rotated = 1;
                break;
            case 1:
                relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0:
                relPos = { {0, 0}, {-1, 0}, {-2, 0}, {-3, 0} };
                rotated = 1;
                break;
            case 1:
                relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
                rotated = 0;
                break;
        }
    }
}

// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> IBlock::clone() const {
    return std::make_unique<IBlock>(*this);
}
