#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "block.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class CommandInterpreter {
    size_t currIdx;
    vector<string> commands;

public:
    string removeLeadingNumbers(const string& input);
    bool startsWith(const string& str, const string& prefix);
    string parseCommand( const vector<pair<string, string>> commandList, const string& input);
    int getMultiplier(const string& command);
    pair<int, string> getNextCommand();
    pair<char, char> getSpecial();
    void readFile(const string& file);
};

#endif
