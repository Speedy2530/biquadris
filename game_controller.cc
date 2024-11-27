#include "game_controller.h"

gameController::gameController() :
    player1Turn{true} {
        player1 = make_unique<Board>();
        player2 = make_unique<Board>();
        curPlayer = move(player1);
    }


void gameController::playTurn() {
    auto curCommand = interpreter.getNextCommand();
    int multipler = curCommand.first;
    string command = curCommand.second;

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
        } else if (command == "I" || command == "J" || command == "L" ||
                   command == "O" || command == "S" || command == "Z" ||
                   command == "T") {
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
        curPlayer->display();

        if(curPlayer->isGameOver()){
            restartGame();
        }

        if (curPlayer->getBlocks()[curPlayer->getCurrBlockID()]->isLocked()) {
            if (player1Turn) {
                if (p1Effect == 'b') {
                    curPlayer->setCellsBlind(false);
                }
                p1Effect = 'N';
                player1 = move(curPlayer);
            }
            else{
                if (p2Effect == 'b') {
                    curPlayer->setCellsBlind(false);
                }
                p2Effect = 'N';
                player2 = move(curPlayer);
            }
            player1Turn != player1Turn;
        }

        playTurn();
    }


void gameController::restartGame() {
     if (player1Turn) {
        player1 = move(curPlayer);
    } else {
        player2 = move(curPlayer);
    }

    player1->reset();
    player2->reset();
    p1Effect = 'N';
    p1forceBlock = 'N';
    p2Effect = 'N';
    p2forceBlock = 'N';
    player1Turn = true;
}
