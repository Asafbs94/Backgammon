#ifndef BACKGAMMON_PLAYER_H
#define BACKGAMMON_PLAYER_H
#include <iostream>
#include "Board.h"
using namespace std;
class Player{
private:
    string color;
public:
    unsigned current_dice1_state;
    unsigned current_dice2_state;
    Player(string color);
    unsigned int roll_dice(unsigned int R);
};
#endif //BACKGAMMON_PLAYER_H
