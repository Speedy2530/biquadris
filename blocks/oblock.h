#ifndef OBLOCK_H
#define OBLOCK_H

#include "../block.h"

using namespace std;

class OBlock : public Block {

    public:
        OBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

