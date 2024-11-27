#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "command_interpreter.h"
#include <memory>
#include <cstdlib>

class gameController {
    bool player1Turn;
    std::unique_ptr<Board> player1;
    std::unique_ptr<Board> player2;
    Board* curPlayer;  
    char p1Effect, p1forceBlock;
    char p2Effect, p2forceBlock;
    CommandInterpreter interpreter;

public:
    gameController();
    void playGame();
    void restartGame();

private:
    void applyEffect(Board* player, char effect, char forceBlock);
    void handlePostDrop();
    bool isBlockType(const std::string& command);
};

#endif
