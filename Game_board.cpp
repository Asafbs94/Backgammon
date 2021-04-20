#include <iostream>
#include "Game_board.h"
#include <cstdlib>

using namespace std;


Game_board::Game_board(unsigned int &x) : x(x),player_turn_flag(false),blocked_moves(false),dice1(0),dice2(0),ejected_white(0),ejected_black(0)
{
    // setting the discs on board
    discs[1] = DiscGroup(2, White);
    discs[6] = DiscGroup(5, Black);
    discs[8] = DiscGroup(3, Black);
    discs[12] = DiscGroup(5, White);
    discs[24] = DiscGroup(2, Black);
    discs[19] = DiscGroup(5, White);
    discs[17] = DiscGroup(3, White);
    discs[13] = DiscGroup(5, Black);
    //the middle bar for "eaten" discs
    discs[BLACK_EATEN] = DiscGroup(0, Black);
    discs[WHITE_EATEN] = DiscGroup(0, White);
}

unsigned int Game_board::seed_generator() {
    const unsigned int a = 22695477;
    const unsigned int c = 1;
    this->x = a * x + c;
    return (x & 0x7fffffff) >> 16;
}

int Game_board::max_group(bool top) const {
    int extra = top ? 0 : 12;
    int max = 0;
    for (int i = extra + 1; i < 13 + extra; i++) {
        if (discs[i].count > max) {
            max = discs[i].count;
        }
    }
    return max;
}

void Game_board::print(bool flip) const {
    if (flip) {
        cout << " 13 14 15 16 17 18    19 20 21 22 23 24" << endl;
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

void Game_board::print_top_row(int index) const {
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

void Game_board::print_bot_row(int index) const {
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

void Game_board::disc_movement(Player player) {
    bool legal_move = false;
    int move_from, move_to;
    while (!legal_move) {
        if (!cin) {
            break;
        }

        if (check_possible_move(player)) {
            cout << "No possible move for " << player.getColorString() << endl;
            blocked_moves = true;
            return;
        }
        cout << "Enter " << player.getColorString() << " move: "<<endl;
        cin >> move_from;
        cin >> move_to;
        if (player.color == Black && move_from == 25) {
            move_from = BLACK_EATEN;
        }
        if (cin.fail()) {
            cout << "Missing user input - quiting game." << endl;
            exit(0);
        }

        if (check_legal_movement(player, move_from, move_to)) {
            if (!check_possible_eat(player, move_from, move_to)) {
                white_index_converter(player, move_from, move_to);

                discs[move_from] = DiscGroup(get_discs_count(move_from) - 1, player.color);
                discs[move_to] = DiscGroup(get_discs_count(move_to) + 1, player.color);

                if (move_to == OUT_OF_PLAY) {
                    player.color == Black ? ejected_black++ : ejected_white++;
                }
                legal_move = true;
            } else {
                legal_move = true;
            }

        } else {
            legal_move = false;
        }
    }
}

bool Game_board::check_legal_movement(Player player, int move_from,
                                      int move_to) {
    unsigned int original_from = move_from;
    unsigned int original_to = move_to;

    int movement = move_from - move_to;
    if (move_from == 26) {
        movement--;
    }
    if (!(move_from == WHITE_EATEN || move_from == BLACK_EATEN)) {
        white_index_converter(player, move_from, move_to);
    }

    if (move_from > 26 || move_from < 0 || move_to > 24 || move_to < 0 || movement > 6 || movement < 0) {
        cout << "Illegal move: From/to out of bounds (from=" << original_from << ", to=" << original_to << ")." << endl;
        return false;
    } else if ((player.color == White && discs[WHITE_EATEN].count > 0 && move_from != WHITE_EATEN) ||
               (player.color == Black && discs[BLACK_EATEN].count > 0 && move_from != BLACK_EATEN)) {
        {
            cout << "Illegal move: Player still has captured piece(s)." << endl;
            return false;
        }
    } else if (discs[move_from].count == 0) {
        cout << "Illegal move: No pieces at from location " << original_from << "." << endl;
        return false;
    } else if (discs[move_to].count > 1 && discs[move_to].color != player.color && move_to != OUT_OF_PLAY) {
        cout << "Illegal move: Cannot capture more that one piece at location " << original_to << "." << endl;
        return false;
    } else if (!check_eject_allow(player) && move_to == OUT_OF_PLAY) {
        cout << "Illegal move: Cannot bear off while not all pieces at home." << endl;
        return false;
    } else if (movement != dice1 && movement != dice2 && move_to != OUT_OF_PLAY) {
        cout << "Illegal move: No value of " << movement << " in dice roll " << endl;
        return false;
    }
    return true;
}

int Game_board::get_discs_count(int index) const {
    return discs[index].count;
}

bool Game_board::check_possible_eat(Player player, int move_from, int move_to) {
    white_index_converter(player, move_from, move_to);
    if (discs[move_to].count == 1 && (discs[move_to].color != player.color)) {
        switch (player.color) {
            case White:
                discs[move_from] = DiscGroup(get_discs_count(move_from) - 1, player.color);
                discs[BLACK_EATEN] = DiscGroup(get_discs_count(BLACK_EATEN) + 1, Black);
                discs[move_to] = DiscGroup(discs[move_to].count, player.color);
                return true;
            case Black:
                discs[move_from] = DiscGroup(get_discs_count(move_from) - 1, player.color);
                discs[WHITE_EATEN] = DiscGroup(get_discs_count(WHITE_EATEN) + 1, White);
                discs[move_to] = DiscGroup(discs[move_to].count, player.color);
                return true;

            case None:
                break;
        }
    }
    return false;
}

bool Game_board::check_eject_allow(Player player) {

    if (discs[25].count > 0 || discs[26].count > 0)
        return false;
    if (player.color == Black)
        for (unsigned int i = 7; i < 24; ++i) {
            if (discs[i].color == player.color && discs[i].count > 0)
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

void Game_board::initial_roll(Player black, Player white) {
    unsigned int initial_roll_white, initial_roll_black;
    do {
        initial_roll_white = white.roll_dice(seed_generator());
        initial_roll_black = black.roll_dice(seed_generator());
        cout << "White player casts " << initial_roll_white << ",";
        cout << " black player casts " << initial_roll_black << endl;
    }
    while (initial_roll_black == initial_roll_white);
    if (initial_roll_black > initial_roll_white) {

        cout << "Black plays first." << endl;
        player_turn_flag = false;

    } else {
        cout << "White plays first." << endl;
        player_turn_flag = true;
    }

}

void Game_board::white_index_converter(Player player, int &move_from, int &move_to) {
    if (move_from == BLACK_EATEN || move_from == WHITE_EATEN) {
        if (player.color == White) {
            move_to = 25 - move_to;
            return;
        }
    } else if (player.color == White && move_to == OUT_OF_PLAY) {
        move_from = 25 - move_from;
        return;
    }
    bool player_color_flag;
    if (player.color == Black) {
        player_color_flag = true;
    } else {
        player_color_flag = false;
    }
    move_from = player_color_flag ? move_from : 25 - move_from;
    move_to = player_color_flag ? move_to : 25 - move_to;

}

bool Game_board::check_eaten_removal(Player player, int move_from, int move_to) {
    if (!(move_from == WHITE_EATEN || move_from == BLACK_EATEN)) {
        white_index_converter(player, move_from, move_to);
    }
    switch (player.color) {
        case Black:
            if ((discs[BLACK_EATEN].count > 0 && discs[move_to].color != White) ||
                (discs[move_to].color == White && discs[move_to].count == 1)) {
                return true;
            } else {
                return false;
            }

        case White:
            if ((discs[WHITE_EATEN].count > 0 && discs[move_to].color != Black) ||
                (discs[move_to].color == Black && discs[move_to].count == 1)) {
                return true;
            } else {
                return false;
            }
        default:
            break;
    }
    return false;
}

unsigned int Game_board::is_double() const {
    if (check_win()){
        return 0;
    }
    return dice1 == dice2 ? 4 : 2;
}

bool Game_board::check_possible_move(Player player) {
    switch (player.color) {
        case White:
            if (discs[WHITE_EATEN].count > 0 && (!check_eaten_removal(player, WHITE_EATEN, dice1) ||
                                                 !check_eaten_removal(player, WHITE_EATEN, dice2)
            )) {
                if ((discs[WHITE_EATEN].count > 1 && discs[dice1].color == Black && discs[dice1].count > 1) ||
                    (discs[dice2].color == Black && discs[dice2].count > 1))
                    return true;
            }
        case Black:
            if (get_discs_count(BLACK_EATEN) > 0 && (!check_eaten_removal(player, BLACK_EATEN, 25 - dice1) ||
                                                     !check_eaten_removal(player, BLACK_EATEN, 25 - dice2)))
                if ((discs[BLACK_EATEN].count > 1 && discs[25 - dice1].color == White && discs[25 - dice1].count > 1) ||
                    (discs[25 - dice2].color == White && discs[25 - dice2].count > 1))
                    return true;
        case None:
            break; // not possible , added to avoid compiler warnings
    }
    return false;
}

bool Game_board::check_win() const {
    if (ejected_black == 15) {
        cout << "Black player wins!" << endl;
        return true;
    } else if (ejected_white == 15) {
        cout << "White player wins!" << endl;
        return false;
    }
    return false;
}

bool Game_board::is_blocked() const {

    return blocked_moves;
}

void Game_board::start() {
    Player white = Player(White);
    Player black = Player(Black);
    initial_roll(black,white);
    while (!check_win()) {

        print(player_turn_flag);
        if (!player_turn_flag) {
            dice1 = black.roll_dice(seed_generator());
            dice2 = black.roll_dice(seed_generator());
            cout << "Black rolls " << dice1 << "-";
            cout << dice2 << "." << endl;
            for (unsigned int i = 0; i < is_double(); i++) {
                disc_movement(black);
                if (is_blocked()) {
                    blocked_moves = false;
                    break;
                }
                if (is_double() == 0) {
                    exit(0);

                }
            }

            player_turn_flag = true;
        } else {
            dice1 = white.roll_dice(seed_generator());
            dice2 = white.roll_dice(seed_generator());

            cout << "White rolls " << dice1 << "-";

            cout << dice2 << "." << endl;

            for (unsigned int i = 0; i < is_double(); i++) {
                disc_movement(white);
                if (is_double() == 0) {
                    exit(0);
                }
            }
            player_turn_flag = false;

        }

    }
}
