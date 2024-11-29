#ifndef OBLOCK_H
#define OBLOCK_H

#include "../block.h"

using namespace std;

class OBlock : public Block {
    char shape;

    public:
        OBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif

