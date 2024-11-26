#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include "blocks/all_blocks.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cctype>

class Block;

class Level {
    protected:
        int levelNum;
        bool isRand;
        int seed;
        size_t currIdx;
        vector<char> seq;
        vector<double> probs;
    public:
        Level(int levelNum, const std::vector<double>& probs = {});
        virtual ~Level() = default;

        // default implementation gets block FROM FILE
        std::unique_ptr<Block> makeBlockFromFile();
        std::unique_ptr<Block> makeRandomBlock();
        virtual std::unique_ptr<Block> makeNextBlock() = 0;
        void readFile(const string& file);
        int randomIndex();
        void setSeed(int seed);
        void setRand(bool isRand);
        virtual void onBlockPlaced(bool clearedRows) {}
        virtual void afterMotion(int player) {};

        int getLevelNum() const { return levelNum; };
};

#endif
