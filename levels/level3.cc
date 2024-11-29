#include "level3.h"
#include "../block.h"

Level3::Level3(const string& file) : Level(3, {1.0/9, 1.0/9, 1.0/9, 1.0/9, 2.0/9, 1.0/9, 2.0/9}) {
    readFile(file);
}

unique_ptr<Block> Level3::makeNextBlock(int /*blocksSinceClear*/) {
    if (isRand) {
        auto block = makeRandomBlock();
        block->setHeavy(true);
        return block;
    }
    else {
        auto block = makeBlockFromFile();
        block->setHeavy(true);
        return block;
    }
}

