#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>

class Block;

class Level {
    protected:
        int levelNum;
        bool isRand;
    public:
        Level(int levelNum);
        virtual ~Level() = default;

        virtual std::unique_ptr<Block> getNextBlock() = 0;
        virtual void onBlockPlaced(bool clearedRows) {}
        virtual void afterMotion(int player) {};

        int getLevelNum() const { return levelNum; };
};