#ifndef ASTERISK_H
#define ASTERISK_H

#include "../block.h"
#include <iostream>

using namespace std;

class AsteriskBlock : public Block {

    public:
        AsteriskBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
        void print() const override;
};

#endif

