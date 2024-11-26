#include "jblock.h"

using namespace std;

JBlock::JBlock(bool isCurr) : Block{isCurr}, shape{'T'} {
    relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > JBlock::getRelPos() const {
    return relPos;
}

char JBlock::getShape() const { return 'T'; }

void JBlock::rotate(string dir) {
    switch(rotated) {
        case 0:
            if (dir == "clockwise") {
                relPos = { {-2, 0}, {-2, 1}, {-1, 0}, {0, 0} };
                rotated = 1;
            }
            else {
                relPos = { {0, 0}, {-2, 1}, {-1, 1}, {0, 1} }; 
                rotated = 3;
            }
        case 1:
            if (dir == "clockwise") {
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 2} }; 
                rotated = 2;
            }
            else {
                relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} }; 
                rotated = 0;
            }
        case 2:
            if (dir == "clockwise") {
                relPos = { {0, 0}, {-2, 1}, {-1, 1}, {0, 1} }; 
                rotated = 3;
            }
            else {
                relPos = { {-2, 0}, {-2, 1}, {-1, 0}, {0, 0} }; 
                rotated = 1;
            }
        case 3: 
            if (dir == "clockwise") {
                relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} };
                rotated = 0;
            }
            else {
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 2} };
                rotated = 2;
            }
    }
}
// For above  v
//essentially, when you add the block to the board, just get its Cell values by adding <3, 0>,
//or whatever the coordinate of the current bottom left is on the board (absRow, absCol).

unique_ptr<Block> JBlock::clone() const {
    return std::make_unique<JBlock>(*this);
}
