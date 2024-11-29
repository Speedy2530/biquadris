#include "block.h"
#include <iostream>

using namespace std;

void Block::print() const {
    char grid[2][4] = { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };

    for (const auto& [relRow, relCol] : relPos) {
        grid[relRow+1][relCol] = getShape();
    }

    // Print the grid
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int Block::idCounter = 0;

