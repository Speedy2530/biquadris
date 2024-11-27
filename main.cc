#include "board.h"
#include "./levels/level0.h"
#include "command_interpreter.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
    unique_ptr<Level> level0 = make_unique<Level0>("sequence1.txt");

    bool textMode = true;
    string seqFile = "sequence1.txt";
    Board board(move(level0), textMode, seqFile);

    CommandInterpreter interpreter;

    cout << "Welcome to Biquadris!" << endl;
    board.display();

    string command;

    // Main game loop
    while (!board.isGameOver()) {
        cout << "\nEnter command: ";

        pair<int, string> nextCommand = interpreter.getNextCommand();
        string fullCommand = nextCommand.second;

	cout << "COMMAND: " << fullCommand << endl;
        // Process commands
        if (fullCommand == "left") {
            board.moveBlockLeft();
        } else if (fullCommand == "right") {
            board.moveBlockRight();
        } else if (fullCommand == "down") {
            board.moveBlockDown();
        } else if (fullCommand == "drop") {
            board.dropBlock();
        } else if (fullCommand == "clockwise") {
            board.rotateBlock("clockwise");
        } else if (fullCommand == "counterclockwise") {
            board.rotateBlock("counterclockwise");
        } else if (fullCommand == "levelup") {
            board.levelUp();
        } else if (fullCommand == "leveldown") {
            board.levelDown();
        } else if (fullCommand == "restart") {
            board.reset();
        } else if (fullCommand == "i" || fullCommand == "j" || fullCommand == "l" ||
                   fullCommand == "o" || fullCommand == "s" || fullCommand == "z" ||
                   fullCommand == "t") {
            char blockType = fullCommand[0];
            board.forceBlock(blockType);
        } else if (fullCommand == "norandom") {
            cout << "Norandom command is not implemented yet." << endl;
        } else if (fullCommand == "random") {
            cout << "Random command is not implemented yet." << endl;
        } else if (fullCommand == "sequence") {
            cout << "Sequence command is not implemented yet." << endl;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }

        // Display updated board state
        board.display();
    }

    cout << "Game over! Final score: " << board.getScore() << endl;
    return 0;
}

