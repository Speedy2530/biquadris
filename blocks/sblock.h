#ifndef SBLOCK_H
#define SBLOCK_H

#include "../block.h"

using namespace std;

class SBlock : public Block {

    public:
        SBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

