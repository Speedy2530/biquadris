#ifndef LEVEL0_H
#define LEVEL0_H

#include "../level.h"

using namespace std;

class Level0 : public Level {
    string file;

    public:
        Level0(const string& file);
        unique_ptr<Block> makeNextBlock(int blocksSinceClear = 0) override;
	virtual ~Level0();
};

#endif 
