#ifndef JBLOCK_H
#define JBLOCK_H

#include "../block.h"

using namespace std;

class JBlock : public Block {

    public:
        JBlock(int level = 0);
        vector <pair <int, int> > getRelPos() const override;
        void rotate(string dir) override;
};

#endif

