#ifndef ASTERISK_H
#define ASTERISK_H

#include "../block.h"

using namespace std;

class AsteriskBlock : public Block {
    char shape;

    public:
        AsteriskBlock(bool isCurr = false);
        vector <pair <int, int> > getRelPos() const override;
        char getShape() const override;
        void rotate(string dir) override;
        unique_ptr<Block> clone() const override;
};

#endif
