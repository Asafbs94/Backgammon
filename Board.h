#ifndef BACKGAMMON_BOARD_H
#define BACKGAMMON_BOARD_H
#include "Player.h"
using namespace std;

enum Color {
    White = 'W', Black = 'B', None = '|'
};\



struct DiscGroup {
    int count;
    Color color;

    explicit DiscGroup(int count = 0, Color color = None) : count(count), color(color) {}
};

class Board {
private:
    DiscGroup discs[26];
    static const int WHITE_EATEN = 0;
    static const int BLACK_EATEN = 25;
    unsigned int x;
public:
    Board();

    int max_group(bool top) const;

    void print(bool flip = false) const;

    void print_top_row(int index) const;

    void print_bot_row(int index) const;

    void disc_movement(Player* player,unsigned int dice1,unsigned int dice2);

    bool check_legal_movement(Player player,unsigned int dice1,unsigned int dice2,unsigned move_from,unsigned int move_to) const;
};

#endif //BACKGAMMON_BOARD_H
