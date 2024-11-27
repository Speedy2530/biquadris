#include <iostream>
#include <memory>
#include "./blocks/jblock.h"
#include "command_interpreter.h"

using namespace std;

int main() {
    // Initialize the command interpreter and a block (e.g., IBlock)
    CommandInterpreter interpreter;
    unique_ptr<Block> block = make_unique<JBlock>(true);

    cout << "Welcome to Biquadris Block Tester!" << endl;
    cout << "Enter commands to rotate and manipulate the block. Type EOF (Ctrl+D) to exit." << endl;

    string command;
    while (true) {
        cout << "Current Block:" << endl;
        block->print();

        cout << "Enter command: ";
        if (!(cin >> command)) {  // Detect EOF or input error
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }

        // Process command using CommandInterpreter
        interpreter.callMethod(command, *block);

        cout << "Block After Command:" << endl;
        block->print();
    }

    return 0;
}

