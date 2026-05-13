#include "Game 3.h"

int G3_Board::score_x = 0;
int G3_Board::score_o = 0;
G3_Player::G3_Player(string n, char s, PlayerType t)
    : Player<char>(n, s, t) {}
G3_UI::G3_UI() : UI<char>("G3 - 5x5 Tic Tac Toe", 5) {}
G3_Board::G3_Board() :Board(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool G3_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char Sym = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || Sym == 0)) {

        if (Sym == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y] = toupper(Sym);
        }
        return true;
    }
    return false;
}

void G3_Board::compute_sequnces() {
    score_x = 0;
    score_o = 0;
    // rows
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y <= 2; ++y) {
            if (board[x][y] != blank_symbol && board[x][y] == board[x][y + 1] && board[x][y + 1] == board[x][y + 2]) {
                if (board[x][y] == 'X') score_x++;
                else if (board[x][y] == 'O') score_o++;
            }
        }
    }
    // columns
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x <= 2; ++x) {
            if (board[x][y] != blank_symbol && board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y]) {
                if (board[x][y] == 'X') score_x++;
                else if (board[x][y] == 'O') score_o++;
            }
        }
    }
    // left to right diagonals
    for (int x = 0; x <= 2; ++x) {
        for (int y = 0; y <= 2; ++y) {
            if (board[x][y] != blank_symbol && board[x][y] == board[x + 1][y + 1] && board[x + 1][y + 1] == board[x + 2][y + 2]) {
                if (board[x][y] == 'X') score_x++;
                else if (board[x][y] == 'O') score_o++;
            }
        }
    }
    // right to left diagonals
    for (int x = 0;x <= 2; ++x) {
        for (int y = 2; y < 5; ++y) {
            if (board[x][y] != blank_symbol && board[x][y] == board[x + 1][y - 1] && board[x + 1][y - 1] == board[x + 2][y - 2]) {
                if (board[x][y] == 'X') score_x++;
                else if (board[x][y] == 'O') score_o++;
            }
        }
    }
}

bool G3_Board::is_win(Player<char>* player) {
    if (n_moves < 24) return false;
    if (n_moves > 24) return false;
    compute_sequnces();
    char sym = player->get_symbol();
    if (sym == 'X') return score_x > score_o;
    else if (sym == 'O') return score_o > score_x;
    return false;
}

bool G3_Board::is_draw(Player<char>* player) {
    if (n_moves != 24) return false;
    return score_x == score_o;
}

bool G3_Board::is_lose(Player<char>* player) {
    if (n_moves != 24) return false;
    if (is_win(player)) return false;
    if (is_draw(player)) return false;
    return true;
}

bool G3_Board::game_is_over(Player<char>* player) {
    return n_moves == 24;
}

// G3_Move
G3_Move::G3_Move(int x, int y, char s) : Move <char>(x, y, s) {}

// G3_UI methods
Player<char>* G3_UI::create_player(string& name, char symbol, PlayerType type) {
    char assigned_symbol;

    if (type == PlayerType::COMPUTER) {
        assigned_symbol = (symbol == '\0') ? ((rand() % 2 == 0) ? 'X' : 'O') : symbol;
    }
    else {
        if (symbol == '\0') {
            cout << name << ", choose your symbol (X or O): ";
            cin >> assigned_symbol;
            while (assigned_symbol != 'X' && assigned_symbol != 'O') {
                cout << "Invalid symbol! Choose X or O: ";
                cin >> assigned_symbol;
            }
        }
        else {
            assigned_symbol = symbol;
        }
    }

    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << assigned_symbol << ")\n";

    return new G3_Player(name, assigned_symbol, type);
}

Move<char>* G3_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nYour turn, " << player->get_name() << "!\n";
        cout << "Enter position (x y): ";
        cin >> x >> y;
        return new G3_Move(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        char aiSymbol = player->get_symbol();
        char opponentSymbol = (aiSymbol == 'X' ? 'O' : 'X');

        // Get best move using minimax with alpha-beta pruning
        Five best = getBestMove(matrix, true, 0, 9, INT_MIN, INT_MAX);

        return new Move<char>(best.x, best.y, aiSymbol);
    }
    return nullptr;
}

// ========== AI Logic Functions ==========

bool G3_UI::boardFull(const vector<vector<char>>& board) {
    int count = 0;
    for (auto& row : board) {
        for (auto& col : row) {
            if (col == '.') count++;
        }
    }
    return count <= 1;
}

int G3_UI::minimax_win(const vector<vector<char>>& board, char ai, char opponent) {
    int score = 0;

    // Check rows
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y <= 2; ++y) {
            int aiCount = 0, oppCount = 0;

            if (board[x][y] == ai) aiCount++; else if (board[x][y] == opponent) oppCount++;
            if (board[x][y + 1] == ai) aiCount++; else if (board[x][y + 1] == opponent) oppCount++;
            if (board[x][y + 2] == ai) aiCount++; else if (board[x][y + 2] == opponent) oppCount++;

            if (aiCount == 3) score += 10;
            else if (oppCount == 3) score -= 10;
            else score += aiCount - oppCount;
        }
    }

    // Check columns
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x <= 2; ++x) {
            int aiCount = 0, oppCount = 0;

            if (board[x][y] == ai) aiCount++; else if (board[x][y] == opponent) oppCount++;
            if (board[x + 1][y] == ai) aiCount++; else if (board[x + 1][y] == opponent) oppCount++;
            if (board[x + 2][y] == ai) aiCount++; else if (board[x + 2][y] == opponent) oppCount++;

            if (aiCount == 3) score += 10;
            else if (oppCount == 3) score -= 10;
            else score += aiCount - oppCount;
        }
    }

    // Left-to-right diagonals
    for (int x = 0; x <= 2; ++x) {
        for (int y = 0; y <= 2; ++y) {
            int aiCount = 0, oppCount = 0;

            if (board[x][y] == ai) aiCount++; else if (board[x][y] == opponent) oppCount++;
            if (board[x + 1][y + 1] == ai) aiCount++; else if (board[x + 1][y + 1] == opponent) oppCount++;
            if (board[x + 2][y + 2] == ai) aiCount++; else if (board[x + 2][y + 2] == opponent) oppCount++;

            if (aiCount == 3) score += 10;
            else if (oppCount == 3) score -= 10;
            else score += aiCount - oppCount;
        }
    }

    // Right-to-left diagonals
    for (int x = 0; x <= 2; ++x) {
        for (int y = 2; y < 5; ++y) {
            int aiCount = 0, oppCount = 0;

            if (board[x][y] == ai) aiCount++; else if (board[x][y] == opponent) oppCount++;
            if (board[x + 1][y - 1] == ai) aiCount++; else if (board[x + 1][y - 1] == opponent) oppCount++;
            if (board[x + 2][y - 2] == ai) aiCount++; else if (board[x + 2][y - 2] == opponent) oppCount++;

            if (aiCount == 3) score += 10;
            else if (oppCount == 3) score -= 10;
            else score += aiCount - oppCount;
        }
    }

    return score;
}

Five G3_UI::getBestMove(const vector<vector<char>>& board,
    bool maximizing, int depth, int max_depth, int alpha, int beta) {
    vector<vector<char>> boardCopy = board;

    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;


    if (boardFull(boardCopy) || depth >= max_depth)
        return { -1, -1, minimax_win(boardCopy, aiSymbol, opponentSymbol) };

    Five bestMove;
    bestMove.score = maximizing ? INT_MIN : INT_MAX;

    for (int x = 0; x < boardCopy.size(); x++)
    {
        for (int y = 0; y < boardCopy[x].size(); y++)
        {
            if (boardCopy[x][y] == '.') {

                boardCopy[x][y] = trackingSymbol;

                Five result = getBestMove(boardCopy, !maximizing, depth + 1, max_depth, alpha, beta);

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
    return bestMove;
}