#include "level4.h"
#include "../block.h"
#include "../blocks/asterisk.h"

Level4::Level4(const string& file) : Level(4, {1.0/9, 1.0/9, 1.0/9, 1.0/9, 2.0/9, 1.0/9, 2.0/9}) {
    readFile(file);
}

unique_ptr<Block> Level4::makeNextBlock(int blocksSinceClear) {
    if (blocksSinceClear != 0 && blocksSinceClear % 5 == 0) {
        return make_unique<AsteriskBlock>(4);
    }
    else if (isRand) {
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
