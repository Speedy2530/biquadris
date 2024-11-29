#ifndef LBLOCK_H
#define LBLOCK_H

#include "../block.h"

using namespace std;

class LBlock : public Block {

    public:
        LBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

