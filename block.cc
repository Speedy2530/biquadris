#include "block.h"
#include <iostream>

using namespace std;

virtual void Block::print() const {
    char grid[4][4] = { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };

    for (const auto& pos : relPos) {
        grid[pos.first + 3][pos.second + 0] = getShape();
    }

    // Print the grid
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}