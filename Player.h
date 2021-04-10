#ifndef BACKGAMMON_PLAYER_H
#define BACKGAMMON_PLAYER_H
#include <iostream>
using namespace std;
class Player{

public:
    string color;
    Player(string color);
    unsigned int roll_dice(unsigned int R);
};
#endif //BACKGAMMON_PLAYER_H
