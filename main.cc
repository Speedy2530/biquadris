#include "game_controller.h"
#include <iostream>
#include <memory>
#include <string>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool textMode = false; 
    int seed = 0;          
    string scriptfile1 = "sequence1.txt"; 
    string scriptfile2 = "sequence2.txt"; 
    int startLevel = 0;    


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-text") {
            textMode = true;
        } else if (arg == "-seed") {
            seed = std::stoi(argv[++i]);
        } else if (arg == "-scriptfile1") {
            scriptfile1 = argv[++i];
        } else if (arg == "-scriptfile2") {
            scriptfile2 = argv[++i];
        } else if (arg == "-startlevel") {
            startLevel = std::stoi(argv[++i]);
        }
    }

    GameController controller(textMode, seed, scriptfile1, scriptfile2, startLevel);
    controller.playGame();

    return 0;
}


