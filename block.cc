#include "block.h"
#include <iostream>

using namespace std;

void Block::print() const {
    char grid[4][4] = { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };

    for (const auto& [relRow, relCol] : relPos) {
        grid[relRow+3][relCol+2] = getShape();
    }

    // Print the grid
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int Block::idCounter = 0;
