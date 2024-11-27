#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "block.h"
#include <string>
#include <vector>
using namespace std;

class CommandInterpreter {

public:
    virtual string removeLeadingNumbers(const string& input);
    virtual bool startsWith(const string& str, const string& prefix);
    string parseCommand(const string& input);
    int getMultiplier(const string& command);
    pair<int, string> getNextCommand();
};

#endif
