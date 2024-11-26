#ifndef LEVEL3_H
#define LEVEL3_H

#include "../level.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Level3 : public Level {

    public:
        Level3(const string& file);
        unique_ptr<Block> makeNextBlock() override;
};

#endif 
