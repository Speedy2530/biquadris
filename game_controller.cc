#include "game_controller.h"

gameController::gameController() :
    player1Turn{true} {
        player1 = make_unique<Board>();
        player2 = make_unique<Board>();
    }


void gameController::playTurn() {
    auto curCommand = interpreter.getNextCommand();
    int multipler = curCommand.first;
    string command = curCommand.second;

    unique_ptr<Board> curPlayer = (player1Turn) ? move(player1) : move(player2);
    if (player1Turn) {
        switch (p1Effect) {
            case 'h':
                curPlayer->getBlocks()[curPlayer->getCurrBlockID()]->setHeavy(true);
                break;
            case 'f':
                curPlayer->forceBlock(p1forceBlock);
                break;
            case 'b':
                curPlayer->setCellsBlind(true);
                break;
        }
    }
    else {
        switch (p2Effect) {
            case 'h':
                curPlayer->getBlocks()[curPlayer->getCurrBlockID()]->setHeavy(true);
                break;
            case 'f':
                curPlayer->forceBlock(p2forceBlock);
                break;
            case 'b':
                curPlayer->setCellsBlind(true);
                break;
        }
    }
    

    if (command == "left") {
            curPlayer->moveBlockLeft();
        } else if (command == "right") {
            curPlayer->moveBlockRight();
        } else if (command == "down") {
            curPlayer->moveBlockDown();
        } else if (command == "drop") {
            curPlayer->dropBlock();
        } else if (command == "clockwise") {
            curPlayer->rotateBlock("clockwise");
        } else if (command == "counterclockwise") {
            curPlayer->rotateBlock("counterclockwise");
        } else if (command == "levelup") {
            curPlayer->levelUp();
        } else if (command == "leveldown") {
            curPlayer->levelDown();
        } else if (command == "restart") {
            curPlayer.reset();
        } else if (command == "i" || command == "j" || command == "l" ||
                   command == "o" || command == "s" || command == "z" ||
                   command == "t") {
            char blockType = command[0];
            curPlayer->forceBlock(blockType);
        } else if (command == "norandom") {
            curPlayer->setRandom(false);
        } else if (command == "random") {
            curPlayer->setRandom(true);
        } else if (command == "sequence") {
            cout << "Sequence command is not implemented yet." << endl;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }

        if (player1Turn) {
            player1 = move(curPlayer);
        }
        else {
            player2 = move(curPlayer);
        }
        curPlayer->display();

        if(curPlayer->isGameOver()){
            restartGame();
        }


        if ()
        player1Turn != player1Turn;
    }


void gameController::restartGame() {
    player1->reset();
    player2->reset();
    p1Effect = '0';
    p1forceBlock = '0';
    p2Effect = '0';
    p2forceBlock = '0';
    player1Turn = true;
}
