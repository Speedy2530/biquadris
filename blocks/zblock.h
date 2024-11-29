#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "../block.h"

using namespace std;

class ZBlock : public Block {
    char shape;

    public:
        ZBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif

