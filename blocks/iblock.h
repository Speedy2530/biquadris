#ifndef IBLOCK_H
#define IBLOCK_H

#include "../block.h"

using namespace std;

class IBlock : public Block {
    char shape;

    public:
        IBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif
