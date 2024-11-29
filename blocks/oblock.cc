#include "oblock.h"

using namespace std;

OBlock::OBlock(bool isCurr) : Block{isCurr, 0, false, 0}, shape{'O'} {
    relPos = { {0, 0}, {0, 1}, {-1, 0}, {-1, 1} };
}

vector <pair <int, int> > OBlock::getRelPos() const {
    return relPos;
}

char OBlock::getShape() const { return 'O'; }

void OBlock::rotate(string /*dir*/) {
    rotated = 0; // might need to know actual rotated? fix this if needed
}

unique_ptr<Block> OBlock::clone() const {
    return std::make_unique<OBlock>(*this);
}

