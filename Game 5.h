#pragma once
#include "BoardGame_Classes.h"
using namespace std;

struct MisereMove {
	MisereMove() : x(-1), y(-1), score(0) {}
	MisereMove(int X, int Y, int Score) : x(X), y(Y), score(Score) {}
	int x, y, score;
};

class Misere : public Board<char> {
private :
	char blank_symbol = '.';

public:
	Misere();

	bool update_board(Move<char>* move);
	
	bool is_win(Player<char>* player);

	bool is_draw(Player<char>* player);

	bool game_is_over(Player<char>* player);

	bool is_lose(Player<char>* player) ;
	
};

class Misere_UI : public UI<char> {

private:
	char aiSymbol, opponentSymbol;

	bool hasThreeInRow(char sym, const vector<vector<char>>& b);
	bool boardFull(const vector<vector<char>>& b);
	MisereMove getBestMove(const vector<vector<char>>& board,
		bool maximizing, int depth, int max_depth, int alpha, int beta);

public:
	Misere_UI();
	~Misere_UI() {};

	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);
};