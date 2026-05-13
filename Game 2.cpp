#include "Game 2.h"

using namespace std;

G2_Board::G2_Board() : Board(6, 7) {

	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}
bool G2_Board::update_board(Move<char>* move) {

	int col = move->get_x();      
	char mark = move->get_symbol();

	if (col < 0 || col >= columns)
		return false;

	for (int row = rows - 1; row >= 0; row--) {
		if (board[row][col] == blank_symbol) {
			board[row][col] = toupper(mark);
			n_moves++;
			return true;
		}
	}
	return false;
}
bool G2_Board::is_column_available(int col) {
	if (col < 0 || col >= columns) return false;
	return board[0][col] == blank_symbol;   
}

bool G2_Board::is_win(Player<char>*player) {

	char symbol = toupper(player->get_symbol());

    // Check horizontal
    for (int r = 0; r < 6; r++)
        for (int c = 0; c <= 7 - 4; c++)
            if (board[r][c] == symbol && board[r][c + 1] == symbol &&
                board[r][c + 2] == symbol && board[r][c + 3] == symbol)
                return true;

    // Check vertical
    for (int c = 0; c < 7; c++)
        for (int r = 0; r <= 6 - 4; r++)
            if (board[r][c] == symbol && board[r + 1][c] == symbol &&
                board[r + 2][c] == symbol && board[r + 3][c] == symbol)
                return true;

    // Check diagonal
    for (int r = 0; r <= 6 - 4; r++)
        for (int c = 0; c <= 7 - 4; c++)
            if (board[r][c] == symbol && board[r + 1][c + 1] == symbol &&
                board[r + 2][c + 2] == symbol && board[r + 3][c + 3] == symbol)
                return true;

    // Check anti-diagonal
    for (int r = 0; r <= 6 - 4; r++)
        for (int c = 3; c < 7; c++)
            if (board[r][c] == symbol && board[r + 1][c - 1] == symbol &&
                board[r + 2][c - 2] == symbol && board[r + 3][c - 3] == symbol)
                return true;

	return false;
}

bool G2_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}
bool G2_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
bool G2_Board::is_lose(Player<char>* player) {
	return !is_win(player) && n_moves == rows * columns;
}

G2_UI::G2_UI() : UI<char>("Welcome to Connect 4 Tic Tac Toe!", 4) {}

Player<char>* G2_UI::create_player(string& name, char symbol, PlayerType type) {

    if (type == PlayerType::COMPUTER) {
        cout << "Smart Computer Player: " << name << " (" << symbol << ")\n";
        aiSymbol = symbol;
        opponentSymbol = (symbol == 'X' ? 'O' : 'X');
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* G2_UI::get_move(Player<char>* player) {
    int col;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nEnter column (0 - 6): ";
        cin >> col;
        return new Move<char>(col, 0, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        cout << "\nAI is thinking...\n";

        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        // FIXED: Added chrono:: namespace
        auto start = chrono::high_resolution_clock::now();

        Connect4 best = getBestMove(matrix, true, 0, 6, -100000, 100000);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "AI took: " << elapsed.count() << " seconds\n";

        return new Move<char>(best.col, 0, player->get_symbol());
    }
    return nullptr;
}

// ========== AI Logic Functions ==========

bool G2_UI::Connect_4(char sym, const vector<vector<char>>& b) {
    // Check horizontal
    for (int r = 0; r < 6; r++)
        for (int c = 0; c <= 7 - 4; c++)
            if (b[r][c] == sym && b[r][c + 1] == sym &&
                b[r][c + 2] == sym && b[r][c + 3] == sym)
                return true;

    // Check vertical
    for (int c = 0; c < 7; c++)
        for (int r = 0; r <= 6 - 4; r++)
            if (b[r][c] == sym && b[r + 1][c] == sym &&
                b[r + 2][c] == sym && b[r + 3][c] == sym)
                return true;

    // Check diagonal
    for (int r = 0; r <= 6 - 4; r++)
        for (int c = 0; c <= 7 - 4; c++)
            if (b[r][c] == sym && b[r + 1][c + 1] == sym &&
                b[r + 2][c + 2] == sym && b[r + 3][c + 3] == sym)
                return true;

    // Check anti-diagonal
    for (int r = 0; r <= 6 - 4; r++)
        for (int c = 3; c < 7; c++)
            if (b[r][c] == sym && b[r + 1][c - 1] == sym &&
                b[r + 2][c - 2] == sym && b[r + 3][c - 3] == sym)
                return true;

    return false;
}

bool G2_UI::boardFull(const vector<vector<char>>& b) {
    for (auto& row : b)
        for (auto& col : row)
            if (col == '.')
                return false;
    return true;
}

bool G2_UI::isColumnAvailable(const vector<vector<char>>& b, int col) {
    if (col < 0 || col >= 7) return false;
    return b[0][col] == '.';
}

int G2_UI::dropPiece(vector<vector<char>>& b, int col, char sym) {
    if (col < 0 || col >= 7)
        return -1;

    for (int row = 5; row >= 0; row--) {
        if (b[row][col] == '.') {
            b[row][col] = toupper(sym);
            return row;
        }
    }
    return -1;  // Column full
}

void G2_UI::removePiece(vector<vector<char>>& b, int row, int col) {
    b[row][col] = '.';
}

Connect4 G2_UI::getBestMove(const vector<vector<char>>& board,
    bool maximizing, int depth, int max_depth, int alpha, int beta) {

    vector<vector<char>> boardCopy = board;
    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;

    // Terminal state checks
    if (Connect_4(aiSymbol, boardCopy))
        return { -1, 10 - depth };  // AI wins -> GOOD (Prefer winning sooner)

    if (Connect_4(opponentSymbol, boardCopy))
        return { -1, -10 + depth }; // Opponent wins = BAD

    if (boardFull(boardCopy))
        return { -1, 0 };  // Draw

    if (depth >= max_depth)
        return { -1, 0 };

    Connect4 bestMove;
    bestMove.score = maximizing ? -100000 : 100000;

    for (int col = 0; col < 7; col++) {
        if (isColumnAvailable(boardCopy, col)) {

            int row = dropPiece(boardCopy, col, trackingSymbol);

            if (row != -1) {

                Connect4 result = getBestMove(boardCopy, !maximizing,
                    depth + 1, max_depth, alpha, beta);

                removePiece(boardCopy, row, col);

                if (maximizing) {
                    if (result.score > bestMove.score) {
                        bestMove = { col, result.score };
                    }
                    alpha = max(alpha, result.score);

                    if (beta <= alpha) {
                        return bestMove;
                    }
                }
                else {
                    if (result.score < bestMove.score) {
                        bestMove = { col, result.score };
                    }
                    beta = min(beta, result.score);

                    if (beta <= alpha) {
                        return bestMove;
                    }
                }
            }
        }
    }
    return bestMove;
}