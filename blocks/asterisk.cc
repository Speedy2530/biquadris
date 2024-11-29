#include "asterisk.h"

using namespace std;

AsteriskBlock::AsteriskBlock(int level) : Block{level, false, 0, '*'} {
    relPos = { {0, 5} };
}

vector <pair <int, int> > AsteriskBlock::getRelPos() const {
    return relPos;
}

void AsteriskBlock::rotate(string /*dir*/) {
    rotated = 0; // might need to know actual rotated? fix this if needed
}

void AsteriskBlock::print() const {
    cout << "*" << endl;
}

