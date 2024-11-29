#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "../block.h"

using namespace std;

class ZBlock : public Block {

    public:
        ZBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

