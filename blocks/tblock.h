#ifndef TBLOCK_H
#define TBLOCK_H

#include "../block.h"

using namespace std;

class TBlock : public Block {

    public:
        TBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

