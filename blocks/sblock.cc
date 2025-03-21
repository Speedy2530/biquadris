#include "sblock.h"

using namespace std;

SBlock::SBlock(int level) : Block{level, false, 0, 'S'} {
    relPos = { {-1, 1}, {-1, 2}, {0, 0}, {0, 1} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > SBlock::getRelPos() const {
    return relPos;
}

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

