#ifndef LEVEL2_H
#define LEVEL2_H

#include "../level.h"

using namespace std;

class Level2 : public Level {

    public:
        Level2();
        unique_ptr<Block> makeNextBlock();
};

#endif 
