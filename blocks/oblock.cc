#include "oblock.h"

using namespace std;

OBlock::OBlock(bool isCurr) : Block{isCurr}, shape{'O'} {
    relPos = { {0, 0}, {0, 1}, {-1, 0}, {-1, 1} }
}

vector <pair <int, int> > OBlock::getRelPos() const override {
    return relPos;
}

char OBlock::getShape() const override { return 'O'; }

void OBlock::rotate(string dir) {
    rotated = 0; // might need to know actual rotated? fix this if needed
}

unique_ptr<Block> clone() const override {
    return std::make_unique<OBlock>(*this);
}
