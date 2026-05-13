#include "Game 1.h"
#include <iostream>

using namespace std;

G1_Board::G1_Board() : Board(3, 3) {

	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}
bool G1_Board::update_board(Move<char>* move) {
	int x = move->get_x();
	int y = move->get_y();
	char mark = move->get_symbol();
	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == blank_symbol || mark == 0)) {
		if (mark == 0) {
			n_moves--;
			board[x][y] = blank_symbol;
		}
		else {
			n_moves++;
			board[x][y] = toupper(mark);
		}

		return true;
	}
	return false;
}

bool G1_Board::is_draw(Player<char>* player)
{
	return (n_moves == rows * columns && !is_win(player));
}

bool G1_Board::game_is_over(Player<char>* player)
{
	return is_win(player) || is_draw(player);
}

bool G1_Board::is_win(Player<char>* player)
{
	char sym = player->get_symbol();
	auto sus = [](char a, char b, char c) {
		return a == 'S' && b == 'U' && c == 'S';
		};

	if (toupper(sym) == 'X' || toupper(sym) == 'S') {
		for (int i = 0; i < rows; i++)
		{
			if (sus(board[i][0], board[i][1], board[i][2])) count1++;
			if (sus(board[0][i], board[1][i], board[2][i])) count1++;
		}
		if (sus(board[0][0], board[1][1], board[2][2])) count1++;
		if (sus(board[0][2], board[1][1], board[2][0])) count1++;
	}
	else {
		for (int i = 0; i < rows; i++)
		{
			if (sus(board[i][0], board[i][1], board[i][2])) count2++;
			if (sus(board[0][i], board[1][i], board[2][i])) count2++;
		}
		if (sus(board[0][0], board[1][1], board[2][2])) count2++;
		if (sus(board[0][2], board[1][1], board[2][0])) count2++;
	}
	return count1 > count2 && n_moves == 9;
}

G1_UI::G1_UI() : UI<char>("Welcome to SUS Tic-Tac-Toe by C- Bosses", 4), depth(0){}

int G1_UI::count_SUS_for_player(char playerSymbol, const vector<vector<char>>& b) {
	int count = 0;
	auto is_SUS_with_middle = [&](char a, char b, char c) {
		return a == 'S' && b == playerSymbol && c == 'S';
		};

	// Rows
	for (int i = 0; i < 3; i++) {
		if (is_SUS_with_middle(b[i][0], b[i][1], b[i][2])) count++;
	}
	// Columns
	for (int j = 0; j < 3; j++) {
		if (is_SUS_with_middle(b[0][j], b[1][j], b[2][j])) count++;
	}
	// Diagonals
	if (is_SUS_with_middle(b[0][0], b[1][1], b[2][2])) count++;
	if (is_SUS_with_middle(b[0][2], b[1][1], b[2][0])) count++;

	return count;
}

int G1_UI::countTotalSUS(const vector<vector<char>>& b) {
	int count = 0;
	auto sus = [](char a, char b, char c) {
		return a == 'S' && b == 'U' && c == 'S';
		};

	// Rows
	for (int i = 0; i < 3; i++) {
		if (sus(b[i][0], b[i][1], b[i][2])) count++;
	}
	// Columns
	for (int j = 0; j < 3; j++) {
		if (sus(b[0][j], b[1][j], b[2][j])) count++;
	}
	// Diagonals
	if (sus(b[0][0], b[1][1], b[2][2])) count++;
	if (sus(b[0][2], b[1][1], b[2][0])) count++;

	return count;
}

Player<char>* G1_UI::create_player(string& name, char symbol, PlayerType type) {

	if (type == PlayerType::COMPUTER) {
		cout << "Smart Computer Player: " << name << " (" << symbol << ")\n";
		aiSymbol = symbol;
		opponentSymbol = (symbol == 'X' ? 'U' : 'S');
		return new Player<char>(name, symbol, type);
	}
	else if (type == PlayerType::HUMAN) {
		cout << "Human Player: " << name << " (" << symbol << ")\n";
		return new Player<char>(name, symbol, type);
	}
	return nullptr;
}

Move<char>* G1_UI::get_move(Player<char>* player) {
	int x, y;
	char c;
	if (toupper(player->get_symbol()) == 'X') {
		c = 'S';
	}
	else
		c = 'U';
	if (player->get_type() == PlayerType::HUMAN) {
		cout << "\nPlease enter your move " << player->get_name() << " x and y (0 to 2) : ";
		cin >> x >> y;
		return new Move<char>(x, y, c);
	}
	else if (player->get_type() == PlayerType::COMPUTER) {
		Board<char>* board = player->get_board_ptr();
		auto matrix = board->get_board_matrix();

		// Get best move using minimax with alpha-beta pruning
		SUS best = getBestMove(matrix, true, 0, 9, -100000, 100000);

		return new Move<char>(best.x, best.y, c);
	}
}

bool G1_UI::boardFull(const vector<vector<char>>& b)
{
	for (auto& row : b)
		for (auto& c : row)
			if (c == '.')
				return false;
	return true;
}

SUS G1_UI::getBestMove(const vector<vector<char>>& board, bool maximizing, int depth, int max_depth, int alpha, int beta)
{
	vector<vector<char>> boardCopy = board;

	// Terminal state checks
	if (boardFull(boardCopy)) {
		int aiScore = count_SUS_for_player(aiSymbol, boardCopy);
		int oppoScore = count_SUS_for_player(opponentSymbol, boardCopy);
		int finalScore = aiScore - oppoScore;
		return { -1, -1, finalScore };
	}

	if (depth >= max_depth)
		return { -1,-1,0 };

	SUS bestMove;
	bestMove.score = maximizing ? -100000 : 100000;
	char symbols[] = { 'S', 'U' };

	for (char sym : symbols) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (boardCopy[x][y] == '.') {

					int susCountBefore = countTotalSUS(boardCopy);

					boardCopy[x][y] = sym;

					int susCountAfter = countTotalSUS(boardCopy);

					int finalSUS = susCountAfter - susCountBefore;

					SUS result = getBestMove(boardCopy, !maximizing,
						depth + 1, max_depth, alpha, beta);

					if (maximizing) {
						result.score += finalSUS * 10;
					}
					else {
						result.score -= finalSUS * 10;
					}

					boardCopy[x][y] = '.';

					if (maximizing) {
						if (result.score > bestMove.score) {
							bestMove = { x, y, result.score };
						}
						alpha = max(alpha, result.score);
						if (beta <= alpha) {
							return bestMove;
						}
					}
					else {
						if (result.score < bestMove.score) {
							bestMove = { x, y, result.score };
						}
						beta = min(beta, result.score);
						if (beta <= alpha) {
							return bestMove;
						}
					}
				}
			}
		}
	}

	return bestMove;
}