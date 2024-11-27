#include "game_controller.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[]) {
    bool textMode = true; // Default to text mode

    // Optional: Accept a command-line argument to set display mode
    if (argc > 1) {
        std::string modeArg = argv[1];
        if (modeArg == "graphics" || modeArg == "xwindow") {
            textMode = false;
        } else if (modeArg == "text") {
            textMode = true;
        } else {
            std::cout << "Unknown mode: " << modeArg << ". Defaulting to text mode." << std::endl;
        }
    }

    // Initialize GameController with the selected display mode
    GameController controller(textMode);

    // Start the game loop
    controller.playGame();

    return 0;
}

