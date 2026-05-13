#ifndef G1_CLASSES_H
#define G1_CLASSES_H

#include <string>
#include <vector>
#include "BoardGame_Classes.h"

struct SUS {
    SUS() : x(0), y(0), score(0){}
    SUS(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
    int x;
    int y;
    int score;
};

using namespace std;

class G1_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int count1 = 0, count2 = 0;
public:
    G1_Board();
    bool update_board(Move<char>* move);
    bool is_draw(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool game_is_over(Player<char>* player) override;

};

class G1_UI : public UI<char> {
private:
    char aiSymbol;
    char opponentSymbol;

    int player1Score = 0;
    int player2Score = 0;
    int count1 = 0;
    int count2 = 0;
    int depth;

    int count_SUS_for_player(char sym, const vector<vector<char>>& b);
    int countTotalSUS(const vector<vector<char>>& b);
    SUS getBestMove(const vector<vector<char>>& board, bool maximizing, int depth, int max_depth, int alpha, int beta);
    bool boardFull(const vector<vector<char>>& b);
public:
    G1_UI();
    ~G1_UI() override = default;

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif