#include <iostream>
#include "Board.h"

using namespace std;


Board::Board() {
    discs[1] = DiscGroup(2, White);
    discs[6] = DiscGroup(5, Black);
    discs[8] = DiscGroup(3, Black);
    discs[12] = DiscGroup(5, White);
    discs[24] = DiscGroup(2, Black);
    discs[19] = DiscGroup(5, White);
    discs[17] = DiscGroup(3, White);
    discs[13] = DiscGroup(5, Black);
    discs[BLACK_EATEN] = DiscGroup(0, Black);
    discs[WHITE_EATEN] = DiscGroup(0, White);
}

int Board::max_group(bool top) const {
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
        cout << "13 14 15 16 17 18     19 20 21 22 23 24" << endl;
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
        cout << " 12 11 10  9  8  7     6  5  4  3  2  1" << endl;
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

void Board::disc_movement(Player player, unsigned int dice1, unsigned int dice2) {
    bool legal_move = false;
    unsigned int move_from, move_to;
    while (!legal_move) {
        if (!cin) {
            break;
        }
        cout << "Enter " << player.getcolor() << " move:" << endl;
        cin >> move_from;
        cin >> move_to;
        move_from = player.color == Black ? move_from : 25 - move_from;
        move_to = player.color == Black ? move_to : 25 - move_to;
        if (check_legal_movement(player, dice1, dice2, move_from, move_to)) {
            if (!check_eat(player, move_from, move_to)) {
                discs[move_from] = DiscGroup(get_discs_count(move_from) - 1, player.color);
                discs[move_to] = DiscGroup(get_discs_count(move_to) + 1, player.color);
                legal_move = true;
            }

        } else {
            legal_move = false;
        }
    }
}

bool Board::check_legal_movement(Player player, unsigned int dice1, unsigned int dice2, unsigned int move_from,
                                 unsigned int move_to) const {
    int original_to = move_to;
    int original_from = move_from;
    move_from = player.color == Black ? move_from : 25 - move_from;
    move_to = player.color == Black ? move_to : 25 - move_to;
    cout << "FROM:" << move_from << endl;
    cout << "TO:" << move_to << endl;
    cout << discs[move_from].count << endl;
    if ((move_from > 26 || move_from < 1) || (move_to > 25 || move_to <= 0) || (move_from - move_to) > 6 ||
        (move_from - move_to < 1)) {
        cout << "Illegal move: From/to out of bounds (from=" << original_from << ",to=" << original_to << ")." << endl;
        return false;
    } else if (move_from != 25 && (player.color == White && discs[WHITE_EATEN].count > 0) ||
               (player.color == Black && discs[BLACK_EATEN].count > 0)) {
        cout << "Illegal move: Player still has captured piece(s)." << endl;
        return false;
    } else if (discs[move_from].count == 0) {
        cout << "Illegal move: No pieces at from location " << original_from << "." << endl;
        return false;
    } else if (discs[move_to].count > 1 && discs[move_to].color != player.color) {
        cout << "Illegal move: Cannot capture more that one piece at location " << original_from << "." << endl;
        return false;
    } else if (!check_ejecetion(player) && move_to == 0) {
        cout << "Illegal move: Cannot bear off while not all pieces at home ." << endl;
        return false;
    } else if (move_from - move_to != dice1 && move_from - move_to != dice2) {
        cout << "Illegal move: No value of " << move_from - move_to << " in dice roll" << endl;
        return false;
    }
    return true;
}


int Board::get_discs_count(int index) const {
    return discs[index].count;
}

bool Board::check_eat(Player player, unsigned int move_from, unsigned int move_to) {
    if (discs[move_to].count == 1 && (discs[move_to].color != player.color)) {
        discs[move_from] = DiscGroup(get_discs_count(move_from) - 1, player.color);
        if (player.color == White) {
            discs[move_to] = DiscGroup(get_discs_count(move_to) - 1, Black);
            discs[BLACK_EATEN] = DiscGroup(get_discs_count(move_to) + 1, Black);
            return true;
        } else if (player.color == Black) {
            discs[move_to] = DiscGroup(get_discs_count(move_to) - 1, White);
            discs[WHITE_EATEN] = DiscGroup(get_discs_count(move_to) + 1, White);
            return true;
        }
    }
    return false;
}

bool Board::check_ejecetion(Player player) const {
    if (discs[25].count > 0 || discs[26].count > 0)
        return false;
    if (player.color == Black)
        for (unsigned int i = 7; i < 25; ++i) {
            if (discs[i].color == player.color && discs[i].color > 0)
                return false;
        }
    else {
        for (unsigned int i = 18; i > 0; --i) {
            if (discs[i].color == player.color && discs[i].count > 0)
                return false;
        }
    }
    return true;

}
