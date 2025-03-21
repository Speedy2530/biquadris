#include "jblock.h"

using namespace std;

JBlock::JBlock(int level) : Block{level, false, 0, 'J'} {
    relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} };  // Imagine the bottom left was {0, 0}
}

vector <pair <int, int> > JBlock::getRelPos() const {
    return relPos;
}

void JBlock::rotate(string dir) {
    if (dir == "clockwise") {
        switch (rotated) {
            case 0:
                relPos = { {-2, 0}, {-2, 1}, {-1, 0}, {0, 0} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 2} };
                rotated = 2;
                break;
            case 2:
                relPos = { {0, 0}, {-2, 1}, {-1, 1}, {0, 1} };
                rotated = 3;
                break;
            case 3:
                relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} };
                rotated = 0;
                break;
        }
    } else if (dir == "counterclockwise") {
        switch (rotated) {
            case 0:
                relPos = { {0, 0}, {-2, 1}, {-1, 1}, {0, 1} };
                rotated = 3;
                break;
            case 3:
                relPos = { {-2, 0}, {-2, 1}, {-1, 0}, {0, 0} };
                rotated = 2;
                break;
            case 2:
                relPos = { {-1, 0}, {-1, 1}, {-1, 2}, {0, 2} };
                rotated = 1;
                break;
            case 1:
                relPos = { {-1, 0}, {0, 0}, {0, 1}, {0, 2} };
                rotated = 0;
                break;
        }
    }
}
