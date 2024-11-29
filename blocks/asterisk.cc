#include "asterisk.h"

using namespace std;

AsteriskBlock::AsteriskBlock(bool isCurr) : Block{isCurr, 0, false, 0}, shape{'*'} {
    relPos = { {0, 5} };
}

vector <pair <int, int> > AsteriskBlock::getRelPos() const {
    return relPos;
}

char AsteriskBlock::getShape() const { return '*'; }

void AsteriskBlock::rotate(string /*dir*/) {
    rotated = 0; // might need to know actual rotated? fix this if needed
}

unique_ptr<Block> AsteriskBlock::clone() const {
    return std::make_unique<AsteriskBlock>(*this);
}

void AsteriskBlock::print() const {
    cout << "*" << endl;
}

