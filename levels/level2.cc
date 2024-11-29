#include "level2.h"
#include "../block.h"

Level2::Level2() : Level(2, vector<double>(7, 1.0 / 7)) {}

unique_ptr<Block> Level2::makeNextBlock(int /*blocksSinceClear*/) {
    return makeRandomBlock();
}

