#include "tblock.h"

using namespace std;

TBlock::TBlock(bool isCurr) : Block{isCurr}, shape{'T'} {
    relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > TBlock::getRelPos() const {
    return relPos;
}

char TBlock::getShape() const { return 'T'; }

void TBlock::rotate(string dir) {
    switch(rotated) {
        case 0:
            if (dir == "clockwise") {
                relPos = { {-1, 0}, {0, 1}, {-2, 1}, {-1, 1} };
                rotated = 1;
            }
            else {
                relPos = { {-2, 0}, {-1, 0}, {0, 0}, {-1, 0} }; 
                rotated = 3;
            }
        case 1:
            if (dir == "clockwise") {
                relPos = { {0, 0}, {0, 1}, {0, 2}, {-1, 1} }; 
                rotated = 2;
            }
            else {
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} }; 
                rotated = 0;
            }
        case 2:
            if (dir == "clockwise") {
                relPos = { {-2, 0}, {-1, 0}, {0, 0}, {-1, 0} }; 
                rotated = 3;
            }
            else {
                relPos = { {-1, 0}, {0, 1}, {-2, 1}, {-1, 1} }; 
                rotated = 1;
            }
        case 3: 
            if (dir == "clockwise") {
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} };
                rotated = 0;
            }
            else {
                relPos = { {0, 0}, {0, 1}, {0, 2}, {-1, 1} };
                rotated = 2;
            }
    }
}
// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> TBlock::clone() const {
    return std::make_unique<TBlock>(*this);
}
