#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "command_interpreter.h"

using namespace std;

class gameController {
    bool player1;
    Board player1;
    Board player2;
    CommandInterpreter commands;
    
    

    public:
        void getPlayer();


};

#endif