#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>

using namespace std;

class Cell {
    int row;
    int col;
    char shape; // ' ' if not filled, '?' if blind
    bool locked; // if the block dropped
    bool blind;

    int blockID;
    //std::shared_ptr<Block> block;  block that it point to

    public:
        Cell(int r = 0, int c = 0, char s = ' ', int id = -1);

        // Accessors
        int getRow() const;
        int getCol() const;
        char getShape() const;
        int getBlockID() const;
        bool isFilled() const;
        bool isBlind() const;

        // Mutators
        void fill(char s, int id = -1);
        void setBlind(bool b);
        
        void clear();

        // Display
        void display() const;

        //void setBlock(std::shared_ptr<Block>) 
};

#endif

