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
        size_t currIdx;
        vector<char> seq;
        vector<double> probs;
        mt19937 gen;
    public:
        Level(int levelNum, const std::vector<double>& probs = {});
        virtual ~Level() = default;

        // default implementation gets block FROM FILE
        std::unique_ptr<Block> makeBlockFromFile();
        std::unique_ptr<Block> makeRandomBlock();
        unique_ptr<Block> blockFromIndex(int idx);
        unique_ptr<Block> blockFromShape(char shape);
        virtual std::unique_ptr<Block> makeNextBlock(int blocksSinceClear = 0) = 0;
        void readFile(const string& file);
        int randomIndex();
        void setSeed(int seed);
        void setRand(bool isRand);
        virtual void onBlockPlaced(bool /*clearedRows*/) {}
        virtual void afterMotion(int /*player*/) {};

        int getLevelNum() const { return levelNum; };
};

#endif
