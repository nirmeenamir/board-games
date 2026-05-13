#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

// Struct to work on moves
struct AiMove {
	AiMove() : x(-1), y(-1), score(0) {}
	AiMove(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
	int x;
	int y;
	int score;
};

class AI : public Player<char>
{
private:
	char aiSymbol;
	char opponentSymbol;
	char blankSymbol = '.';

	int depth;

	AiMove getBestMove(const vector<vector<char>>& board, bool maximizing, int depth, int max_depth, int alpha, int beta);
	bool boardFull(const vector<vector<char>>& b);
public:

	AI(string name, char symbol);
	~AI() {};

	bool fake_is_win(char sym, const vector<vector<char>>& b);
	virtual Move<char>* get_move(Player<char>* player);
};