#include "block.h"
#include <iostream>

using namespace std;

void Block::print() const {
    char grid[4][4] = { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };

    for (const auto& [relRow, relCol] : relPos) {
        int newRow = relRow + 3;
        grid[newRow][relCol] = getShape();
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
