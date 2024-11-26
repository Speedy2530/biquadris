#include "level0.h"
#include "block.h"

using namespace std;

Level0::Level0(const string& file) : Level(0) {
    readFile(file);
}

unique_ptr<Block> Level0::makeNextBlock() {
    return makeBlockFromFile();
}


