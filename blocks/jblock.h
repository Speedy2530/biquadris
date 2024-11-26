#ifndef JBLOCK_H
#define JBLOCK_H

#include "../block.h"

using namespace std;

class JBlock : public Block {
    char shape;

    public:
        JBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() override;
};

#endif
