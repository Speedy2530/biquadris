#ifndef IBLOCK_H
#define IBLOCK_H

#include "../block.h"

using namespace std;

class IBlock : public Block {

    public:
        IBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

