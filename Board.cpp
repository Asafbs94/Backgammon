#include <iostream>
#include "Board.h"

using namespace std;


Board::Board() {
    discs[WHITE_EATEN] = DiscGroup(0, White);
    discs[1] = DiscGroup(2, White);
    discs[6] = DiscGroup(5, Black);
    discs[8] = DiscGroup(3, Black);
    discs[12] = DiscGroup(5, White);
    discs[24] = DiscGroup(2, Black);
    discs[19] = DiscGroup(5, White);
    discs[17] = DiscGroup(3, White);
    discs[13] = DiscGroup(5, Black);
    discs[BLACK_EATEN] = DiscGroup(0, Black);
}

int Board::max_group(bool top) const
    {
        int extra = top ? 0 : 13;
        int max = 0;
        for (int i = extra; i < 13 + extra; i++) {
            if (discs[i].count > max) {
                max = discs[i].count;
            }
        }
        return max;
    }

void Board::print(bool flip) const {
    if (flip) {
        cout << " 24 23 22 21 20 19    18 17 16 15 14 13" << endl;
    } else {
        cout << " 12 11 10  9  8  7     6  5  4  3  2  1" << endl;
    }
    cout << "+------------------+-+------------------+" << endl;
    int max = max_group(true);
    max = max < 5 ? 5 : max;
    for (int i = 0; i < max; i++) {
        print_top_row(i);
    }
    cout << "+                  + +                  +" << endl;
    max = max_group(false);
    max = max < 5 ? 5 : max;
    for (int i = max - 1; i >= 0; i--) {
        print_bot_row(i);
    }
    cout << "+------------------+-+------------------+" << endl;
    if (flip) {
        cout << "  1  2  3  4  5  6     7  8  9  10 11 12" << endl;
    } else {
        cout << " 13 14 15 16 17 18    19 20 21 22 23 24" << endl;
    }

}

void Board::print_top_row(int index) const {
    cout << "+";

    for (int i = 12; i >= 7; i--) {
        char letter = discs[i].count > index ? discs[i].color : None;
        cout << " " << letter << " ";
    }
    char eaten = discs[WHITE_EATEN].count > index ? White : ' ';
    cout << "+" << eaten << "+";
    for (int i = 6; i >= 1; i--) {
        char letter = discs[i].count > index ? discs[i].color : None;
        cout << " " << letter << " ";
    }
    cout << "+" << endl;

}

void Board::print_bot_row(int index) const {
    cout << "+";

    for (int i = 13; i <= 18; i++) {
        char letter = discs[i].count > index ? discs[i].color : None;
        cout << " " << letter << " ";
    }
    char eaten = discs[BLACK_EATEN].count > index ? Black : ' ';
    cout << "+" << eaten << "+";
    for (int i = 19; i <= 24; i++) {
        char letter = discs[i].count > index ? discs[i].color : None;
        cout << " " << letter << " ";
    }
    cout << "+" << endl;
}




