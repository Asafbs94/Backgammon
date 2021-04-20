#include <iostream>
#include <cstdlib>
#include "Game_board.h"
using namespace std;

int main() {
    unsigned int seed;
    cout << "Enter seed" << endl;  //receive a seed for generating random numbers
    cin >> seed;
    if (cin.fail()) {
        cout << "Missing user input - quiting game." << endl;
        exit(0);
    }
    Game_board b(seed); // setting seed for the dices rolls, allows to know the results for the dices.
    b.start(); // start the game
    return 0;
}
