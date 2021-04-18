#include <iostream>
#include <sstream>
#include "Gameboard.h"
using namespace std;


int main() {


    bool player_turn_flag; // true for black turn, false for white.
    bool game_state; // game state flag, will turn false if one of the players won.
    unsigned int seed;

    Player white = Player(White);
    Player black = Player(Black);

    cout << "Enter seed" << endl;  //receive a seed for generating random numbers
    cin >> seed;
    Gameboard b(seed);


    if (b.initial_roll(black,white)){

        cout<<"Black plays first."<<endl;
        player_turn_flag = false;
    }
    else
        {
        cout<<"White plays first."<<endl;
        player_turn_flag = true;
    }


    while (game_state) {
        if (!cin){
            break;
        }
        b.print(player_turn_flag);
        if (!player_turn_flag){
            b.dice1 = black.roll_dice(b.seed_generator());
            b.dice2 = black.roll_dice(b.seed_generator());
            cout<<"Black rolls "<<b.dice1<<"-";
            cout<<b.dice2<<endl;

            for(int i=0; i<b.is_double();i++)
            {
                b.disc_movement(black, b.dice1, b.dice2);
            }
            player_turn_flag = true;
        }
        else{
                b.dice1 = white.roll_dice(b.seed_generator());
                b.dice2 = white.roll_dice(b.seed_generator());
                cout<<"White rolls "<<b.dice1<<"-";
                cout<<b.dice2<<endl;

                for(int i=0; i<b.is_double();i++)
                {
                    b.disc_movement(white, b.dice1, b.dice2);
                }
            player_turn_flag = false;
        }
        game_state = true;
    }
    return 0;
}

