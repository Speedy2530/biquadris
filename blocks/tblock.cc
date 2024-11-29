#include "tblock.h"

using namespace std;

TBlock::TBlock(int level) : Block{level, false, 0, 'T'} {
    relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > TBlock::getRelPos() const {
    return relPos;
}

void TBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0: // Rotate 0° -> 90°
                relPos = { {-2, 1}, {-1, 0}, {-1, 1}, {0, 1} };
                rotated = 1;
                break;
            case 1: // Rotate 90° -> 180°
                relPos = { {-1, 1}, {0, 0}, {0, 1}, {0, 2} };
                rotated = 2;
                break;
            case 2: // Rotate 180° -> 270°
                relPos = { {-2, 0}, {-1, 0}, {-1, 1}, {0, 0} };
                rotated = 3;
                break;
            case 3: // Rotate 270° -> 0°
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} };
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0: // Rotate 0° -> 270°
                relPos = { {-2, 0}, {-1, 0}, {-1, 1}, {0, 0} };
                rotated = 3;
                break;
            case 3: // Rotate 270° -> 180°
                relPos = { {-1, 1}, {0, 0}, {0, 1}, {0, 2} };
                rotated = 2;
                break;
            case 2: // Rotate 180° -> 90°
                relPos = { {-2, 1}, {-1, 0}, {-1, 1}, {0, 1} };
                rotated = 1;
                break;
            case 1: // Rotate 90° -> 0°
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 1} };
                rotated = 0;
                break;
        }
    }
}

