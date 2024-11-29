#ifndef TBLOCK_H
#define TBLOCK_H

#include "../block.h"

using namespace std;

class TBlock : public Block {
    char shape;

    public:
        TBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif

