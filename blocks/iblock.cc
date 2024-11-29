#include "iblock.h"

using namespace std;

IBlock::IBlock(int level) : Block{level, false, 0, 'I'} {
    relPos = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > IBlock::getRelPos() const {
    return relPos;
}

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

