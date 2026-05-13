#pragma once
#include "BoardGame_Classes.h"
#include "AI.h"
using namespace std;

class Tic_4 : public Board<char> {
private:
    char emptyCell = '.';

public:
    Tic_4();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; } ;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Tic_4_UI : public UI<char> {
public:
    Tic_4_UI();
    ~Tic_4_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};
