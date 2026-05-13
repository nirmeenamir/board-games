#pragma once
#ifndef GAME2_H
#define GAME2_H

#include <iostream>
#include <chrono>
#include <thread>

#include "BoardGame_Classes.h"

using namespace std;
using namespace chrono;

struct Connect4 {
	Connect4() : col(-1), score(0) {}
	Connect4(int Col, int Score) : col(Col), score(Score) {}
	int col;
	int score;
};

class G2_Board : public Board<char> {
private:
	char blank_symbol = '.';

public:
	G2_Board();
	bool update_board(Move<char>* move);
	bool is_column_available(int col);
	bool game_is_over(Player<char>* player);
	bool is_win(Player<char>* player);
	bool is_lose(Player<char>* player);
	bool is_draw(Player<char>* player);
};

class G2_UI : public UI<char> {
private:
	char aiSymbol = '.';
	char opponentSymbol = '.';

	bool Connect_4(char sym, const vector<vector<char>>& b);
	bool boardFull(const vector<vector<char>>& b);
	bool isColumnAvailable(const vector<vector<char>>& b, int col);
	int dropPiece(vector<vector<char>>& b, int col, char symbol);
	void removePiece(vector<vector<char>>& b, int row, int col);
	Connect4 getBestMove(const vector<vector<char>>& board,
		bool maximizing, int depth, int max_depth, int alpha, int beta);
public:
	G2_UI();
	~G2_UI() {};

	Player<char>* create_player(string& name, char symbol, PlayerType type);
	Move<char>* get_move(Player<char>* player);
};

#endif
