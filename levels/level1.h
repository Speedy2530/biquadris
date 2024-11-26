#ifndef LEVEL1_H
#define LEVEL1_H

#include "../level.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Level1 : public Level {

    public:
        Level1();
        unique_ptr<Block> makeNextBlock() override;
};

#endif 
