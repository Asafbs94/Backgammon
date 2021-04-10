#include <iostream>
#include <sstream>
#include "Board.h"
#include "Player.h"
using namespace std;

unsigned int seed_maker(unsigned int &X) {
    const unsigned int a = 22695477;
    const unsigned int c = 1;
    X = a * X + c;
    return (X & 0x7fffffff) >> 16;
}

int main() {
    Board b;
    Player *white = new Player("White");
    Player *black = new Player("Black");
    unsigned int x=3;
    unsigned int dice1,dice2,initial_roll_white,initial_roll_black,move_from,move_to;
    bool player_turn_flag,game_state;
//    cout << "Enter seed" << endl;
//    cin >> x;
    initial_roll_white = white->roll_dice(seed_maker(x));
    initial_roll_black = black->roll_dice(seed_maker(x));
    cout<<"White player casts "<<initial_roll_white<<",";
    cout<<" black player casts "<<initial_roll_black<<endl;
    game_state= true;
    if (initial_roll_black > initial_roll_white){
        cout<<"Black plays first."<<endl;
        player_turn_flag = false;
    }
    else{
        cout<<"White plays first."<<endl;
        player_turn_flag = true;
    }
    while (game_state) {
        b.print(player_turn_flag);
        if (!player_turn_flag){
            dice1 = black->roll_dice(seed_maker(x));
            dice2 = black->roll_dice(seed_maker(x));
            cout<<"Black rolls "<<dice1<<"-";
            cout<<dice2<<endl;
            b.disc_movement(black,dice1,dice2);
            player_turn_flag = true;
        }
        else{
            dice1 = white->roll_dice(seed_maker(x));
            dice2 = white->roll_dice(seed_maker(x));
            cout<<"White rolls "<<dice1<<"-";
            cout<<dice2<<endl;
            cout<<"Enter White move:"<<endl;
            cin>>move_from;
            cin>>move_to;

            player_turn_flag = false;
        }
        break;
    }

    return 0;
}

