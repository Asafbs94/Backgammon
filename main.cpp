#include <iostream>
#include <cstdlib>
#include "Game_board.h"

using namespace std;


int main() {


    bool player_turn_flag; // true for black turn, false for white.
    unsigned int seed;

    Player white = Player(White);
    Player black = Player(Black);

    cout << "Enter seed" << endl;  //receive a seed for generating random numbers
    cin >> seed;
    if (cin.fail()) {
        cout << "Missing user input - quiting game." << endl;
        exit(0);
    }
    Game_board b(seed);

    if (b.initial_roll(black, white)) {

        cout << "Black plays first." << endl;
        player_turn_flag = false;
    } else {
        cout << "White plays first." << endl;
        player_turn_flag = true;
    }


    while (!b.check_win()) {

        if (!cin) {
            break;
        }
        b.print(player_turn_flag);
        if (!player_turn_flag) {
            b.dice1 = black.roll_dice(b.seed_generator());
            b.dice2 = black.roll_dice(b.seed_generator());
            cout << "Black rolls " << b.dice1 << "-";
            cout << b.dice2 << "." << endl;
            for (unsigned int i = 0; i < b.is_double(); i++) {
                b.disc_movement(black);
                if (b.is_blocked()){
                    b.blocked_moves = false;
                    break;
                }
                if (b.is_double() == 0) {
                    return 0;

                }
            }

            player_turn_flag = true;
        } else {
            b.dice1 = white.roll_dice(b.seed_generator());
            b.dice2 = white.roll_dice(b.seed_generator());

            cout << "White rolls " << b.dice1 << "-";

            cout << b.dice2 << "." << endl;

            for (unsigned int i = 0; i < b.is_double(); i++) {
                b.disc_movement(white);
                if (b.is_double() == 0) {
                    return 0;
                }
            }
            player_turn_flag = false;

        }

    }
    return 0;
}
