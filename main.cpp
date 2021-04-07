#include <iostream>
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
    unsigned int initial_roll_white,initial_roll_black;
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
            cout<<"Black rolls "<<black->roll_dice(seed_maker(x))<<"-";
            cout<<black->roll_dice(seed_maker(x))<<endl;
            cout<<"Enter Black move:"<<endl;
            player_turn_flag = true;
        }
        else{
            cout<<"White rolls "<<black->roll_dice(seed_maker(x))<<"-";
            cout<<white->roll_dice(seed_maker(x))<<endl;
            cout<<"Enter White move:"<<endl;
            player_turn_flag = false;
        }
        break;
    }

    return 0;
}

