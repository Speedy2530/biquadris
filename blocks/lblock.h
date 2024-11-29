#ifndef LBLOCK_H
#define LBLOCK_H

#include "../block.h"

using namespace std;

class LBlock : public Block {
    char shape;

    public:
        LBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif

