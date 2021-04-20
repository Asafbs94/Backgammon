#ifndef BACKGAMMON_GAME_BOARD_H
#define BACKGAMMON_GAME_BOARD_H


enum Color {
    White = 'W', Black = 'B', None = '|'
}; // setting colors for the players and discs to match

struct Player {
    Color color;
    explicit Player(Color color) : color(color){}

    int roll_dice(unsigned int R) {
        return (R % 6) + 1;
    }

    std::string getColorString() const {
        return color == Black ? "Black" : "White";
    }

}; // implements the game players

struct DiscGroup {
    int count;
    Color color;

    explicit DiscGroup(int count = 0, Color color = None) : count(count), color(color) {}
}; // presents the discs groups on the board (the pointy triangles)

class Game_board {
private:
    DiscGroup discs[27];
    unsigned int& x; // for seed making. as requested at the pdf assignment
    bool player_turn_flag; // false for black turn, true for white.
    bool blocked_moves; // will be true if there is no possible moves
    int dice1,dice2; // implements the game board dices
    int ejected_white,ejected_black; // counter for the ejected discs. will help to declare the winner
    static const int OUT_OF_PLAY = 0; // index for ejected discs
    static const int WHITE_EATEN = 25; // index for eaten white discs
    static const int BLACK_EATEN = 26  ; // index for eaten black discs


    //print function helpers
    int max_group(bool top) const;

    void print_top_row(int index) const;

    void print_bot_row(int index) const;
    //
    bool is_blocked () const;

    void initial_roll(Player black, Player white); // will return true if black won the init. roll, false otherwise.

    unsigned int seed_generator(); // generates the seed for the dices roll, made for the auto-tester

    void print(bool flip = false) const; // prints the board , false for black pov, true for white pov

    void disc_movement(Player player); // moves the discs on the board

    bool check_legal_movement(Player player, int move_from,int move_to); // checks if the disc movement is legal

    int get_discs_count(int index) const; // returns the count of the discs in the struct

    bool check_possible_eat(Player player, int move_from, int move_to); //checks if the player can "eat" each other

    bool check_eject_allow(Player player) ; //checks if the player can eject the discs,by checking the players discs index.

    void white_index_converter(Player player, int& move_from, int& move_to) ; // converts the indexs for the white POV

    bool check_eaten_removal(Player player,int move_from, int move_to); //checks if the player can remove his disc from eaten bar

    unsigned int is_double() const; // will give the player 4 moves if double rolled

    bool check_win() const; // will be flagged true if player won

    bool check_possible_move(Player player); // checking if the player is blocked for movement

public:
    explicit Game_board(unsigned int &x); //ctor , sets the seed for the game to allow auto-check
    void start(); // starts the game.
};

#endif //BACKGAMMON_GAME_BOARD_H
/**
 ASCII Backgammon game

 Seed init, required for auto check output,will set the results of the dices

 The winner of the initial roll will start the game

 W - WHITE GAME DISCS
 B - BLACK GAME DISCS

 Index for eaten white players = 25
 index for eaten black players = 26
 index for discs out of play = 0

                12 11 10  9  8  7     6  5  4  3  2  1
                +------------------+-+------------------+
                + W  |  |  |  B  | + + B  |  |  |  |  W +
                + W  |  |  |  B  | + + B  |  |  |  |  W +
                + W  |  |  |  B  | + + B  |  |  |  |  | +
                + W  |  |  |  |  | + + B  |  |  |  |  | +
                + W  |  |  |  |  | + + B  |  |  |  |  | +
                +                  + +                  +
                + B  |  |  |  |  | + + W  |  |  |  |  | +
                + B  |  |  |  |  | + + W  |  |  |  |  | +
                + B  |  |  |  W  | + + W  |  |  |  |  | +
                + B  |  |  |  W  | + + W  |  |  |  |  B +
                + B  |  |  |  W  | + + W  |  |  |  |  B +
                +------------------+-+------------------+
                13 14 15 16 17 18    19 20 21 22 23 24



 **/
