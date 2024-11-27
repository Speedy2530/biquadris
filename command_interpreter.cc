#include "block.h"
#include "command_interpreter.h"
#include <iostream>
#include <algorithm>

using namespace std;

pair<int, string> CommandInterpreter::getNextCommand() {
    string command;
    cin >> command;
    if(!commands.empty() && currIdx < commands.size()) {
        command = commands[currIdx];
        currIdx++;
    }
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
        {"re", "restart"},
        {"e", "exit"}
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

int CommandInterpreter::getMultiplier(const string& command) {
    int multiplier = 0;   // Initialize to 0 to correctly accumulate digits
    size_t pos = 0;

    // Iterate over the command string and accumulate digits
    while (pos < command.length() && std::isdigit(static_cast<unsigned char>(command[pos]))) {
        multiplier = multiplier * 10 + (command[pos] - '0');
        ++pos;
    }

    // If no digits were found, default to 1
    return (multiplier > 0) ? multiplier : 0;
}

pair<char, char> CommandInterpreter::getSpecial() {
    char action, forceShape;
    cout << "Choose a special effect: heavy, force, or blind (h/f/b)" << endl;
    cin >> action; 
    forceShape = 'N';
    if (action == 'f') {
        cout << "Enter the shape of the block to force: " << endl;
        cin >> forceShape;
    }
    return {action, forceShape};
}

void CommandInterpreter::readFile(const string& file) {
    ifstream infile(file);

    if (!infile.is_open()) {
        cerr << "Error: Cannot open sequence file " << file << endl;
    }

    string command;
    while (infile >> command) {
        commands.push_back(command);
    }
    infile.close();

    if (commands.empty()) {
        cerr << "Warning: Sequence file " << file << " is empty." << endl;
    }
}
