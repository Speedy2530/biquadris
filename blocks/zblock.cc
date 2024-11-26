#include "zblock.h"

using namespace std;

ZBlock::ZBlock(bool isCurr) : Block{isCurr}, shape{'T'} {
    relPos = { {-1, 0}, {-1, 1}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > ZBlock::getRelPos() const {
    return relPos;
}

char ZBlock::getShape() const { return 'T'; }

void ZBlock::rotate(string dir) {
    switch(rotated) {
        case 0:
                relPos = { {-2, 1}, {-1, 0}, {-1, 1}, {0, 0} };
                rotated = 1;
        case 1:
                relPos = { {-1, 0}, {-1, 1}, {0, 1}, {0, 2} }; 
                rotated = 0;
    }
}
// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> ZBlock::clone() const {
    return std::make_unique<ZBlock>(*this);
}
