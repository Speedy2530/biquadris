#ifndef LEVEL0_H
#define LEVEL0_H

#include "../level.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namspace std;

class Level0 : public Level {
    vector<string> seq;
    size_t currIdx;
    string seqFile;

    public:
        Level0(int levelNum, const string& file);
        unique_ptr<Block> getNextBlock() override;
        int getLevel() const override;
        void onBlockPlaced(bool clearedRows) override;
        void afterMoveOrRotate(int playerID) override;

        void readFile(const string& file);
        virtual ~Level0();
};

#endif 
