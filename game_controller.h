#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "command_interpreter.h"

using namespace std;

class gameController {
    bool player1;
    unique_ptr<Board> player1;
    unique_ptr<Board> player2;
    CommandInterpreter interpreter;
    
    public:
        gameController(unique_ptr<Board> player1, unique_ptr<Board> player2);

};

#endif