#ifndef GAME3_H
#define GAME3_H
#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

struct Five {
    Five() : x(-1), y(-1), score(0) {}
    Five(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
    int x, y, score;
};
class G3_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    G3_Board();
    bool update_board(Move<char>* move) override;
    bool game_is_over(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    void compute_sequnces();
    static int score_x;
    static int score_o;
};

class G3_Player : public Player<char > {
public:
    G3_Player(string n, char s, PlayerType t);
    int get_score() const;
    void reset_score();
    bool vis[5][5];
};

class G3_Move : public Move<char> {
public:
    G3_Move(int x, int y, char symbol);
};

class G3_UI : public UI<char>, G3_Board {
private:
    char aiSymbol, opponentSymbol;

    bool boardFull(const vector<vector<char>>& board);
    int minimax_win(const vector<vector<char>>& board, char ai, char opponent);
    Five getBestMove(const vector<vector<char>>& board,
        bool maximizing, int depth, int max_depth, int alpha, int beta);
public:
    G3_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif