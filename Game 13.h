#pragma once

#include "BoardGame_Classes.h"

using namespace std;

class G13_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<char>> vec;
public:
	G13_Board();
    bool update_board(Move<char>* move);
    bool game_is_over(Player<char>* player);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player);

    void customDisplayer(vector<vector<char>> v);
};

class G13_UI : public UI<char> {

public:
    G13_UI();
    ~G13_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};