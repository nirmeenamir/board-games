#pragma once
#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

struct Diamond_AI {
    Diamond_AI() : x(0), y(0), score(0) {}
    Diamond_AI(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
	int x;
	int y;
	int score;
};

class Diamond : public Board<char> {
private:
    char blank_symbol = '.';

public:

    Diamond();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Diamond_UI : public UI<char> {
private:
    char aiSymbol, opponentSymbol;

    int max_depth = 6;
    bool minimax_win3(char sym, vector<vector<char>>& board);
    bool minimax_win4(char sym, vector<vector<char>>& board);
    bool boardFull(const vector<vector<char>>& board);
    Diamond_AI getBestMove(const vector<vector<char>>& board,
        bool maximizing, int depth, int alpha, int beta);
public:

    Diamond_UI();
    ~Diamond_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);

    void display_board_matrix(const vector<vector<char>>& matrix) const;
};
