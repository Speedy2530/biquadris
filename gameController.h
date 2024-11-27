#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"

using namespace std;

class gameController {
    int curPlayer;
    vector<Board> players;
    vector<int> scores;
    vector<char> curEffect;

    public:
        void getPlayer();

};

#endif