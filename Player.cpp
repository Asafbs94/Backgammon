#include "Player.h"
#include <iostream>
using namespace std;
Player::Player(string color) {
    this->color = color;
}

unsigned int Player::roll_dice(unsigned int R) {
    return (R%6)+1;
}
