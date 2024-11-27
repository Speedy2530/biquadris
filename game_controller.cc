#include "game_controller.h"

gameController::gameController(unique_ptr<Board> player1, unique_ptr<Board> player2) :
    player1{player1}, player2{player2} {}