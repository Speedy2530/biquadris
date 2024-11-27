#include "game_controller.h"

GameController::GameController(bool textMode, int seed, string scriptfile1, string scriptfile2,  int startLevel) :
    player1Turn(true),
    p1Effect('N'),
    p1forceBlock('N'),
    p2Effect('N'),
    p2forceBlock('N'),
    gameOver{false} {

    unique_ptr<Level> level1 = nullptr;
    unique_ptr<Level> level2 = nullptr;
    
    switch (startLevel) {
        case 0:
            level1 = make_unique<Level0>(scriptfile1);
            level2 = make_unique<Level0>(scriptfile2);
        case 1:
            level1 = make_unique<Level1>();
            level2 = make_unique<Level1>();
        case 2:
            level1 = make_unique<Level2>();
            level2 = make_unique<Level2>();
        case 3:
            level1 = make_unique<Level3>(scriptfile1);
            level2 = make_unique<Level3>(scriptfile2);
        case 4:
            level1 = make_unique<Level3>(scriptfile1);
            level2 = make_unique<Level3>(scriptfile2);
    }
    

    player1 = make_shared<Board>(move(level1), textMode, scriptfile1);
    player2 = make_shared<Board>(move(level2), textMode, scriptfile2);

    player1->setSeed(seed);
    player2->setSeed(seed);
    
    curPlayer = player1;

    display = make_unique<TextDisplay>(*player1, *player2, textMode);
}

void GameController::playGame() {
    gameOver = false;
    while (!gameOver) {
        curPlayer = player1Turn ? player1 : player2;

        if (player1Turn) {
            applyEffect(curPlayer, p1Effect, p1forceBlock);
            p1Effect = 'N';  
        } else {
            applyEffect(curPlayer, p2Effect, p2forceBlock);
            p2Effect = 'N';  
        }

	// Display current game state
        display->display();

        // Get next command
        pair<int, string> nextCommand = interpreter.getNextCommand();
        string fullCommand = nextCommand.second;
        int multiplier = nextCommand.first;

        cout << "COMMAND: " << fullCommand << " (x" << multiplier << ")" << endl;

        // Process commands with multipliers
        for (int i = 0; i < multiplier; ++i) {
            if (fullCommand == "left") {
                curPlayer->moveBlockLeft();

                if (curPlayer->wasBlockLockedDuringLastMove()) {
                    cout << "curr block is locked" << endl;
                    handlePostDrop();
                    break;  
                }
            } else if (fullCommand == "right") {
                curPlayer->moveBlockRight();

                if (curPlayer->wasBlockLockedDuringLastMove()) {
                    cout << "curr block is locked" << endl;
                    handlePostDrop();
                    break;  
                }
            } else if (fullCommand == "down") {
            	curPlayer->moveBlockDown();


                if (curPlayer->wasBlockLockedDuringLastMove()) {
                    handlePostDrop();
                    break;  
                }
	    } else if (fullCommand == "drop") {
                curPlayer->dropBlock();

                handlePostDrop();
                break; // Exit multiplier loop after drop
            } else if (fullCommand == "clockwise") {
                curPlayer->rotateBlock("clockwise");
            } else if (fullCommand == "counterclockwise") {
                curPlayer->rotateBlock("counterclockwise");
            } else if (fullCommand == "levelup") {
                curPlayer->levelUp();
            } else if (fullCommand == "leveldown") {
                curPlayer->levelDown();
            } else if (fullCommand == "restart") {
                restartGame();
                break;
            } else if (isBlockType(fullCommand)) {
                char blockType = fullCommand[0];
                curPlayer->forceBlock(blockType);
                break;
            } else if (fullCommand == "norandom") {
                string file;
                cin >> file;
                curPlayer->setLevelFile(file);
                break;
            } else if (fullCommand == "random") {
                curPlayer->setRandom(true);
                break;
            } else if (fullCommand == "sequence") {
                string file;
                cin >> file;
                interpreter.readFile(file);
                break;
            } else {
                cout << "Invalid command. Please try again." << endl;
                break;
            }

            // Update display after each command
        
	    if (curPlayer->isCurrentBlockLocked()) {
                handlePostDrop();

                if (curPlayer->isGameOver()) {
                    restartGame();
                    break;  
                }

                break;  
            }
	}

        //if (gameOver) break;

        // Toggle player turns
        // player1Turn = !player1Turn;
        //curPlayer = player1Turn ? player1.get() : player2.get();
    }

    // Display final game state
    cout << "Game over! Final scores:" << endl;
    display->display();
}

void GameController::applyEffect(shared_ptr<Board> player, char effect, char forceBlock) {
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

void GameController::handlePostDrop() {

    if (curPlayer->isGameOver()) {
        cout << "Game over for current player!" << endl;
        restartGame();
        gameOver = true;
    }

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

    cout << " Switching player turns" << endl;
    curPlayer->setBlockLockedDuringLastMove(false);
    player1Turn = !player1Turn;
}

bool GameController::isBlockType(const string& command) {
    return command == "I" || command == "J" || command == "L" ||
           command == "O" || command == "S" || command == "Z" ||
           command == "T";
}

void GameController::restartGame() {
    player1->reset();
    player2->reset();
    p1Effect = 'N';
    p1forceBlock = 'N';
    p2Effect = 'N';
    p2forceBlock = 'N';
    player1Turn = true;
    curPlayer = player1;
}

GameController::~GameController() = default;
