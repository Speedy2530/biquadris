#include "block.h"
#include "command_interpreter.h"
#include <iostream>
#include <algorithm>

using namespace std;

void CommandInterpreter::callMethod(string command, Block& block) {
    // Normalize the command to lowercase
    transform(command.begin(), command.end(), command.begin(), ::tolower);

    // Match full commands or abbreviations
    if (command == "left" || command == "l" || command == "lef") {
        // Handle "left" command
    } else if (command == "right" || command == "r" || command == "ri") {
        // Handle "right" command
    } else if (command == "down" || command == "dn" || command == "do") {
        // Handle "down" command
    } else if (command == "clockwise" || command == "c" || command == "cl") {
	    block.rotate("clockwise");
	    // Handle "clockwise" command
    } else if (command == "counterclockwise" || command == "cc" || command == "co") {
	    block.rotate("counterclockwise");
	    // Handle "counterclockwise" command
    } else if (command == "drop" || command == "dp" || command == "dr") {
        // Handle "drop" command
    } else if (command == "levelup" || command == "lu") {
        // Handle "levelup" command
    } else if (command == "leveldown" || command == "ld") {
        // Handle "leveldown" command
    } else if (command == "norandom" || command == "nr" || command == "no") {
        // Handle "norandom" command
    } else if (command == "random" || command == "rm" || command == "ra") {
        // Handle "random" command
    } else if (command == "sequence" || command == "s" || command == "se") {
        // Handle "sequence" command
    } else if (command == "i" || command == "j" || command == "l" || command == "o" || command == "s" || command == "z" || command == "t") {
        // Handle block type commands (I, J, L, etc.)
    } else if (command == "restart" || command == "re") {
        // Handle "restart" command
    } else {
        cout << "Incorrect Command. Refer to the documentation." << endl;
    }
}

string CommandInterpreter::fullCommandName(string command) {
    // Map abbreviated commands to full names
    if (command == "l" || command == "lef") return "left";
    if (command == "r" || command == "ri") return "right";
    if (command == "dn" || command == "do") return "down";
    if (command == "c" || command == "cl") return "clockwise";
    if (command == "cc" || command == "co") return "counterclockwise";
    if (command == "dp" || command == "dr") return "drop";
    if (command == "lu") return "levelup";
    if (command == "ld") return "leveldown";
    if (command == "nr" || command == "no") return "norandom";
    if (command == "rm" || command == "ra") return "random";
    if (command == "s" || command == "se") return "sequence";
    if (command == "re") return "restart";
    return command; // Return as-is if no match
}

int CommandInterpreter::getMultiplier(string command, Block& block) {
    int multiplier = 1;
    size_t pos = 0;

    // Extract the numeric multiplier (e.g., "2left" -> 2)
    while (pos < command.length() && isdigit(command[pos])) {
        multiplier = multiplier * 10 + (command[pos] - '0');
        ++pos;
    }

    // Call the method with the stripped command and pass the Block reference
    if (pos < command.length()) {
        callMethod(command.substr(pos, command.length()), block);
    }

    return multiplier > 1 ? multiplier : 1; // Default multiplier is 1 if no number found
}
