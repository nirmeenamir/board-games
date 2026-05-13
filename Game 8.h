#ifndef G8_H
#define G8_H

#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

struct Pyramid {
    Pyramid() : x(0), y(0), score(0) {}
    Pyramid(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
    int x;
    int y;
    int score;
};

class G8_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    G8_Board();
    bool update_board(Move<char>* move);
    bool game_is_over(Player<char>* player);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player);
};
class G8_UI : public UI<char> {
private:
    char aiSymbol, opponentSymbol;

    int score1 = 0;
    int score2 = 0;
    int max_depth = 10;
    bool minimax_win(char sym, vector<vector<char>>& board);
    bool boardFull(const vector<vector<char>>& board);
    Pyramid getBestMove(const vector<vector<char>>& board,
        bool maximizing, int depth, int alpha, int beta);

public:
    G8_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
    void display_board_matrix(const vector<vector<char>>& matrix) const override;

};
#endif