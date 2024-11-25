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
        Cell(int r = 0, int c = 0) : row{r}, col{c}, shape{' '}, locked{false}, blind{false} {}

        // Accessors
        int getRow() const { return row; }
        int getCol() const { return col; }
        char getShape() const { return shape; }
        bool isFilled() const { return shape != ' '; }
        bool isLocked() const { return locked; }
        bool isBlind() const { return blind; }

        // Mutators
        void setFill(char s) { shape = s; }
        void setLocked(bool lock) { locked = lock; }
        void setBlind(bool b) { blind = b; }

        // Display
        void display() const {
            if (!blind) cout << shape : cout << '?';
        }

        //void setBlock(std::shared_ptr<Block>) 
};

#endif