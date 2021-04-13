#ifndef BACKGAMMON_BOARD_H
#define BACKGAMMON_BOARD_H

using namespace std;

enum Color {
    White = 'W', Black = 'B', None = '|'
};

struct Player{
    Color color;
    explicit Player(Color color):color(color){};
    unsigned int roll_dice(unsigned int R){
        return (R%6)+1;
    }
    string getcolor(){
        if (color =='B'){
            return "Black";
        }
        return "White";
    }
};

struct DiscGroup {
    int count;
    Color color;
    explicit DiscGroup(int count = 0, Color color = None) : count(count), color(color) {}
};

class Board {
private:
    DiscGroup discs[27];
    static const int OUT_OF_PLAY = 0;
    static const int WHITE_EATEN = 26;
    static const int BLACK_EATEN = 25;
public:
    Board();

    int max_group(bool top) const;

    void print(bool flip = false) const;

    void print_top_row(int index) const;

    void print_bot_row(int index) const;

    void disc_movement(Player player,unsigned int dice1,unsigned int dice2);

    bool check_legal_movement(Player player,unsigned int dice1,unsigned int dice2,unsigned move_from,unsigned int move_to) const;

    int get_discs_count(int index) const;

    bool check_eat(Player player,unsigned move_from,unsigned int move_to);

    bool check_ejecetion(Player player) const;
};

#endif //BACKGAMMON_BOARD_H
