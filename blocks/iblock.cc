#include "iblock.h"

using namespace std;

IBlock::IBlock(bool isCurr) : Block{isCurr}, shape{'T'} {
    relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} }  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > IBlock::getRelPos() const override {
    return relPos;
}

char IBlock::getShape() const override { return 'T'; }

void IBlock::rotate(string dir) {
    switch(rotated) {
        case 0:
        	relPos = { {0, 0}, {-1, 0}, {-2, 0}, {-3, 0} };
                rotated = 1;
        case 1:
                relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} }; 
                rotated = 0;
    }
}
// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> clone() const override {
    return std::make_unique<IBlock>(*this);
}
