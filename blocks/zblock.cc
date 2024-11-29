#include "zblock.h"

using namespace std;

ZBlock::ZBlock(int level) : Block{level, false, 0, 'Z'} {
    relPos = { {-1, 0}, {-1, 1}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > ZBlock::getRelPos() const {
    return relPos;
}

void ZBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0: // Rotate 0° -> 90°
                relPos = { {0, 0}, {-1, 0}, {-1, 1}, {-2, 1} }; // Vertical Z
                rotated = 1;
                break;
            case 1: // Rotate 90° -> 0°
                relPos = { {-1, 0}, {-1, 1}, {0, 1}, {0, 2} }; // Horizontal Z
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

