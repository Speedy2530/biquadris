#ifndef LEVEL0_H
#define LEVEL0_H

#include "../level.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Level0 : public Level {
    string file;

    public:
        Level0(const string& file);
        unique_ptr<Block> makeNextBlock() override;
        virtual ~Level0();
};

#endif 
