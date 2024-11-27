#include "game_controller.h"

GameController::GameController(bool textMode) :
    player1Turn(true),
    p1Effect('N'),
    p1forceBlock('N'),
    p2Effect('N'),
    p2forceBlock('N') {
    
    // Initialize Level instances for each player
    std::unique_ptr<Level> level1 = std::make_unique<Level0>("sequence1.txt");
    std::unique_ptr<Level> level2 = std::make_unique<Level0>("sequence2.txt"); // You can choose different levels

    // Initialize Board instances with the respective Level instances 
    player1 = std::make_unique<Board>(std::move(level1), textMode, "sequence1.txt");
    player2 = std::make_unique<Board>(std::move(level2), textMode, "sequence2.txt");
    
    curPlayer = player1.get();

    // Initialize TextDisplay with both boards and the selected mode
    display = std::make_unique<TextDisplay>(*player1, *player2, textMode);
}

void GameController::playGame() {
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

	// Display current game state
        display->display();

        // Get next command
        std::pair<int, std::string> nextCommand = interpreter.getNextCommand();
        std::string fullCommand = nextCommand.second;
        int multiplier = nextCommand.first;

        std::cout << "COMMAND: " << fullCommand << " (x" << multiplier << ")" << std::endl;

        // Process commands with multipliers
        for (int i = 0; i < multiplier; ++i) {
            if (fullCommand == "left") {
                curPlayer->moveBlockLeft();
            } else if (fullCommand == "right") {
                curPlayer->moveBlockRight();
            } else if (fullCommand == "down") {
            	curPlayer->moveBlockDown();


                if (curPlayer->isCurrentBlockLocked()) {

                    handlePostDrop();

                    if (curPlayer->isGameOver()) {
                        restartGame();
                        break;  
                    }

                    break;  
                }
	    } else if (fullCommand == "drop") {
                curPlayer->dropBlock();

                if (curPlayer->isGameOver()) {
                    std::cout << "Game over for current player!" << std::endl;
                    restartGame();
                    gameOver = true;
                    break;
                }

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
                std::string file;
                std::cin >> file;
                curPlayer->setLevelFile(file);
                break;
            } else if (fullCommand == "random") {
                curPlayer->setRandom(true);
                break;
            } else if (fullCommand == "sequence") {
                std::string file;
                std::cin >> file;
                interpreter.readFile(file);
                break;
            } else {
                std::cout << "Invalid command. Please try again." << std::endl;
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
    std::cout << "Game over! Final scores:" << std::endl;
    display->display();
}

void GameController::applyEffect(Board* player, char effect, char forceBlock) {
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

bool GameController::isBlockType(const std::string& command) {
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
    curPlayer = player1.get();
}

GameController::~GameController() = default;
