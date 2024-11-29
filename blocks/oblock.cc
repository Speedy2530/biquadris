#include "oblock.h"

using namespace std;

OBlock::OBlock(int level) : Block{level, false, 0, 'O'} {
    relPos = { {0, 0}, {0, 1}, {-1, 0}, {-1, 1} };
}

vector <pair <int, int> > OBlock::getRelPos() const {
    return relPos;
}

void OBlock::rotate(string /*dir*/) {
    rotated = 0; // might need to know actual rotated? fix this if needed
}

