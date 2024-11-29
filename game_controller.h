#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "command_interpreter.h"
#include "textdisplay.h"
#include <memory>
#include <cstdlib>

class GameController {
    bool player1Turn;
    shared_ptr<Board> player1;
    shared_ptr<Board> player2;
    shared_ptr<Board> curPlayer;
    char p1Effect, p1forceBlock;
    char p2Effect, p2forceBlock;
    CommandInterpreter interpreter;
    unique_ptr<TextDisplay> display; // Pointer to TextDisplay
    bool gameOver;

public:
    // Constructor takes a mode flag for display
    GameController(
        bool textMode = true,
        int seed = 0, 
        string scriptfile1 = "sequence1.txt",
        string scriptfile2 = "sequence2.txt",
        int startLevel = 0
    );
    
    // Destructor to clean up TextDisplay
    ~GameController();
    
    // Starts the game loop
    void playGame();
    
    // Resets the game state
    void restartGame();

private:
    // Applies special effects to a player
    void applyEffect(shared_ptr<Board> player, char effect, char forceBlock);
    
    // Handles actions after a block is dropped
    void handlePostDrop();
    
    // Checks if a command is a block type
    bool isBlockType(const std::string& command);
};

#endif

