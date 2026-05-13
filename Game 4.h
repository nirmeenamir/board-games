#pragma once
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>

#include "BoardGame_Classes.h"

using namespace std;

struct WordAI {
    WordAI() : x(0), y(0), score(0) {}
    WordAI(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
    int x;
    int y;
    int score;
};

class G4_Board : public Board<char> {
private:
    char emptyCell = '.';
    unordered_set<string> dict;
    unordered_set<string> loadDictionary();

public:
	G4_Board();

    bool update_board(Move<char>* move);
    bool is_draw(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool game_is_over(Player<char>* player) override;
    bool is_valid_word(const string& word);

};

class G4_UI : public UI<char> , public G4_Board{

private:
    int depth;
    char letter;

public:
    G4_UI();
    ~G4_UI() {};

    WordAI getBestMove(vector<vector<char>>& b, bool maximizing, int depth, int max_depth, int alpha, int beta);
    bool fake_is_win(const vector<vector<char>>& boardCopy);
    bool boardFull(const vector<vector<char>>& b);

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};
