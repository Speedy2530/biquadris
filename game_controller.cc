#include "game_controller.h"

gameController::gameController() :
    player1Turn{true},
    p1Effect{'N'},
    p1forceBlock{'N'},
    p2Effect{'N'},
    p2forceBlock{'N'} {
    player1 = std::make_unique<Board>();
    player2 = std::make_unique<Board>();
    curPlayer = player1.get();  
}

void gameController::playGame() {
    bool gameOver = false;
    while (!gameOver) {
        curPlayer = player1Turn ? player1.get() : player2.get();

        if (player1Turn) {
            applyEffect(curPlayer, p1Effect, p1forceBlock);
            p1Effect = 'N';  
        } else {
            applyEffect(curPlayer, p2Effect, p2forceBlock);
            p2Effect = 'N';  
        }

        curPlayer->display();


        auto curCommand = interpreter.getNextCommand();
        int multiplier = curCommand.first;
        std::string command = curCommand.second;


        for (int i = 0; i < multiplier; ++i) {
            if (command == "left") {
                curPlayer->moveBlockLeft();
            } else if (command == "right") {
                curPlayer->moveBlockRight();
            } else if (command == "down") {
                curPlayer->moveBlockDown();


                if (curPlayer->isCurrentBlockLocked()) {

                    handlePostDrop();

                    if (curPlayer->isGameOver()) {
                        restartGame();
                        break;  
                    }

                    break;  
                }
            } else if (command == "drop") {
                curPlayer->dropBlock();

                if (curPlayer->isGameOver()) {
                    restartGame();
                    break; 
                }

                handlePostDrop();

                break;  
            } else if (command == "clockwise") {
                curPlayer->rotateBlock("clockwise");
            } else if (command == "counterclockwise") {
                curPlayer->rotateBlock("counterclockwise");
            } else if (command == "levelup") {
                curPlayer->levelUp();
            } else if (command == "leveldown") {
                curPlayer->levelDown();
            } else if (command == "restart") {
                restartGame();
                break;  
            } else if (isBlockType(command)) {
                char blockType = command[0];
                curPlayer->forceBlock(blockType);
                break;  
            } else if (command == "norandom") {
                std::string file;
                std::cin >> file;
                curPlayer->setLevelFile(file);
                break;  
            } else if (command == "random") {
                curPlayer->setRandom(true);
                break;  
            } else if (command == "sequence") {
                std::string file;
                std::cin >> file;
                interpreter.readFile(file);
                break;  
            } else {
                std::cout << "Invalid command. Please try again." << std::endl;
                break;  
            }

            curPlayer->display();

            if (curPlayer->isCurrentBlockLocked()) {
                handlePostDrop();

                if (curPlayer->isGameOver()) {
                    restartGame();
                    break;  
                }

                break;  
            }
        }
    }
}


void gameController::applyEffect(Board* player, char effect, char forceBlock) {
    switch (effect) {
        case 'h':
            player->getBlocks()[player->getCurrBlockID()]->setHeavy(true);
            break;
        case 'f':
            player->forceBlock(forceBlock);
            break;
        case 'b':
            player->setCellsBlind(true);
            break;
        default:
            break;
    }
}

void gameController::handlePostDrop() {

    curPlayer->setCellsBlind(false);

    int linesCleared = curPlayer->getLinesCleared();
    if (linesCleared > 1) {
        auto special = interpreter.getSpecial();
        if (player1Turn) {
            p2Effect = special.first;
            p2forceBlock = special.second;
        } else {
            p1Effect = special.first;
            p1forceBlock = special.second;
        }
    }

    player1Turn = !player1Turn;
}

bool gameController::isBlockType(const std::string& command) {
    return command == "I" || command == "J" || command == "L" ||
           command == "O" || command == "S" || command == "Z" ||
           command == "T";
}

void gameController::restartGame() {
    player1->reset();
    player2->reset();
    p1Effect = 'N';
    p1forceBlock = 'N';
    p2Effect = 'N';
    p2forceBlock = 'N';
    player1Turn = true;
    curPlayer = player1.get();
}
