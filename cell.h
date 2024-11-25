#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>

using namespace std;

class Cell {
    int row;
    int col;
    char shape; // ' ' if not filled
    bool locked; // if the block dropped
    bool blind;
    //std::shared_ptr<Block> block;  block that it point to

    public:
        Cell(int r, int c, char s);

        // Accessors
        int getRow() const;
        int getCol() const;
        char getShape() const;
        bool isFilled() const;
        bool isLocked() const;
        bool isBlind() const;

        // Mutators
        void setFill(char s);
        void setLocked(bool lock);
        void setBlind(bool b);

        // Display
        void display() const;

        //void setBlock(std::shared_ptr<Block>) 
};

#endif
