#ifndef SBLOCK_H
#define SBLOCK_H

#include "../block.h"

using namespace std;

class SBlock : public Block {
    char shape;

    public:
        SBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif
