#ifndef LEVEL3_H
#define LEVEL3_H

#include "../level.h"

using namespace std;

class Level3 : public Level {

    public:
        Level3(const string& file);
        unique_ptr<Block> makeNextBlock(int blocksSinceClear = 0) override;
};

#endif

