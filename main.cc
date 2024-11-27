#include "board.h"
#include "./levels/level0.h"
#include "command_interpreter.h"
#include "xwindow.h" // Include the XWindow class
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    unique_ptr<Level> level0 = make_unique<Level0>("sequence1.txt");

    bool textMode = true;
    string seqFile = "sequence1.txt";
    Board board(move(level0), textMode, seqFile);

    CommandInterpreter interpreter;

    // Initialize XWindow within a try-catch block
    unique_ptr<XWindow> xwindow_ptr;
    try {
        xwindow_ptr = make_unique<XWindow>(board);
        xwindow_ptr->display(); // Initial display
    } catch (const char* msg) {
        cerr << "Error initializing XWindow: " << msg << endl;
        cerr << "Continuing without graphical display." << endl;
        // Optionally, set xwindow_ptr to nullptr or handle accordingly
    }

    cout << "Welcome to Biquadris!" << endl;
    board.display();

    string command;

    // Main game loop
    while (!board.isGameOver()) {
        cout << "\nEnter command: ";

        pair<int, string> nextCommand = interpreter.getNextCommand();
        string fullCommand = nextCommand.second;
        int multiplier = nextCommand.first;

        cout << "COMMAND: " << fullCommand << " (x" << multiplier << ")" << endl;

        // Process commands with multipliers
        for (int i = 0; i < multiplier; ++i) {
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
                // Implement norandom functionality if needed
                cout << "Norandom command is not implemented yet." << endl;
            } else if (fullCommand == "random") {
                // Implement random functionality if needed
                cout << "Random command is not implemented yet." << endl;
            } else if (fullCommand == "sequence") {
                // Implement sequence functionality if needed
                cout << "Sequence command is not implemented yet." << endl;
            } else {
                cout << "Invalid command. Please try again." << endl;
            }

            // Optional: Add a small delay for smoother visualization
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Display updated board state in command-line
        board.display();

        // Update XWindow display if initialized successfully
        if (xwindow_ptr) {
            try {
                xwindow_ptr->display();
            } catch (const char* msg) {
                cerr << "Error updating XWindow: " << msg << endl;
                // Optionally, disable further XWindow updates
                xwindow_ptr.reset();
            }
        }
    }

    cout << "Game over! Final score: " << board.getScore() << endl;
    return 0;
}

