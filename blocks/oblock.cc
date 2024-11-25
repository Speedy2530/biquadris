#include "oblock.h"

using namespace std;

OBlock::OBlock(bool isCurr) : Block{isCurr}, shape{'O'} {
    relPos.emplace_back(0, 0); 
    relPos.emplace_back(0, 1); 
    relPos.emplace_back(1, 0); 
    relPos.emplace_back(1, 1); 
}

vector <pair <int, int> > OBlock::getRelativePositions() const override {
    return relativePositions;
}

char OBlock::getShape() const override { return 'O'; }

void OBlock::rotate(string direction) {
    // Nothing needed since it's symmetric
}

unique_ptr<Block> clone() const override {
    return std::make_unique<OBlock>(*this);
}
