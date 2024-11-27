#include "block.h"
#include "command_interpreter.h"
#include <iostream>
#include <algorithm>

using namespace std;

pair<int, string> CommandInterpreter::getNextCommand() {
    string command;
    cin >> command;
    if (command.size() > 0) {
        int multiplier = getMultiplier(command);
        string parsed = parseCommand(command);
        return {multiplier, parsed};
    }
    return {0, ""};
}

string CommandInterpreter::removeLeadingNumbers(const string& input) {
    size_t pos = 0;
    while (pos < input.length() && isdigit(input[pos], std::locale())) {
        pos++;
    }
    return input.substr(pos);
}

bool CommandInterpreter::startsWith(const string& str, const string& prefix) {
    if (prefix.length() > str.length()) return false;
    return str.compare(0, prefix.length(), prefix) == 0;
}

string CommandInterpreter::parseCommand(const string& input) {
    const vector<pair<string, string>> commandList = {
        {"lef", "left"},
        {"ri", "right"},
        {"dow", "down"},
        {"clo", "clockwise"},
        {"co", "counterclockwise"},
        {"dro", "drop"},
        {"levelu", "levelup"},
        {"leveld", "leveldown"},
        {"n", "norandom file"},
        {"ra", "random"},
        {"s", "sequence file"},
        {"I", "I"},
        {"J", "J"},
        {"L", "L"},
        {"O", "O"},
        {"S", "S"},
        {"Z", "Z"},
        {"T", "T"},
        {"re", "restart"}
    };
    
    string processedInput = removeLeadingNumbers(input);
    
    if (processedInput.empty()) {
        return "none";
    }
    
    for (const auto& pair : commandList) {
        const string& prefix = pair.first;
        const string& command = pair.second;
        
        if (startsWith(processedInput, prefix)) {
            return command;
        }
    }
    
    return "none";
}

int CommandInterpreter::getMultiplier(string command) {
    int multiplier = 1;
    size_t pos = 0;

    while (pos < command.length() && isdigit(command[pos], std::locale())) {
        multiplier = multiplier * 10 + (command[pos] - '0');
        ++pos;
    }

    return multiplier > 1 ? multiplier : 1; 
}
