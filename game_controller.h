#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "command_interpreter.h"
#include <memory>

using namespace std;

class gameController {
    bool player1Turn;
    unique_ptr<Board> player1;
    unique_ptr<Board> player2;
    char p1Effect, p1forceBlock;
    char p2Effect, p2forceBlock;
    CommandInterpreter interpreter;
    
    public:
        gameController();
        void playTurn();
        void restartGame();

};

#endif