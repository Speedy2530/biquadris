#include "level1.h"
#include "../block.h"

Level1::Level1() : Level(1, {1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/12, 1.0/6, 1.0/12}) {}

unique_ptr<Block> Level1::makeNextBlock(int blocksSinceClear) {
    return makeRandomBlock();
}
