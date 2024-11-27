#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "block.h"
#include <string>
#include <vector>
using namespace std;

class CommandInterpreter {
    string curCommand;
    int curMultiplier;

public:
    string removeLeadingNumbers(const string& input);
    bool startsWith(const string& str, const string& prefix);
    string parseCommand(const string& input);
    int getMultiplier(string command);
    pair<int, string> getNextCommand();
};

#endif
