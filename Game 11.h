#pragma once

#include <vector>
#include "BoardGame_Classes.h"
#include "AI.h"
using namespace std;

class G11_Board : public Board<char>{

private:
	char emptyCell = '.';

    // deleteing tracker to get current position from a vec
    int deleted = 0;

    // vector to store position for deleting
    vector<pair<int, int>> vec;

public:
	G11_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool fullBoard();

};

class G11_UI : public UI<char> {

public:
    G11_UI();
    ~G11_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

