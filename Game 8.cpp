#include "Game 8.h"

G8_Board::G8_Board() : Board(3, 5) {
    // Initialize the pyramid board
    char pyramid[3][5] = {
        {' ', ' ', blank_symbol, ' ', ' '},
        {' ', blank_symbol, blank_symbol, blank_symbol, ' '},
        {blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol}
    };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = pyramid[i][j];
}

bool G8_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

bool G8_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    vector<vector<pair<int, int>>> wins = {
        // Diagonals
        {{0,2}, {1,1}, {2,0}},
        {{0,2}, {1,2}, {2,2}},
        {{0,2}, {1,3}, {2,4}},

        // Middle row
        {{1,1}, {1,2}, {1,3}},

        // Bottom row combinations
        {{2,0}, {2,1}, {2,2}},
        {{2,1}, {2,2}, {2,3}},
        {{2,2}, {2,3}, {2,4}},

    };

    for (auto& w : wins) {
        if (board[w[0].first][w[0].second] == sym &&
            board[w[1].first][w[1].second] == sym &&
            board[w[2].first][w[2].second] == sym)
            return true;
    }

    return false;
}

bool G8_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool G8_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


G8_UI::G8_UI() : UI<char>("Game-8-Pyramid Tic Tac Toe", 3) {}

Player<char>* G8_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        cout << "Smart Computer Player: " << name << " (" << symbol << ")\n";
        aiSymbol = symbol;
        opponentSymbol = (symbol == 'X' ? 'O' : 'X');
        return new Player<char>(name, symbol, type);
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
    return nullptr;
}

Move<char>* G8_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2 for x, 0 to 4 for y): ";
        cin >> x >> y;

        if (x < 0 || x > 2 || y < 0 || y > 4) {
            cout << "Invalid coordinates! Try again.\n";
            return get_move(player);
        }

        if ((x == 0 && y != 2) ||
            (x == 1 && (y < 1 || y > 3)) ||
            (x == 2 && (y < 0 || y > 4))) {
            cout << "Invalid pyramid position! Try again.\n";
            return get_move(player);
        }
        return new Move<char>(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        char aiSymbol = player->get_symbol();
        char opponentSymbol = (aiSymbol == 'X' ? 'O' : 'X');

        // Get best move using minimax with alpha-beta pruning
        Pyramid best = getBestMove(matrix, true, 0, INT_MIN, INT_MAX);

        return new Move<char>(best.x, best.y, aiSymbol);
    }

}

// ========== AI Logic Functions ==========

bool G8_UI::boardFull(const vector<vector<char>>& board) {
    for (auto& row : board)
        for (auto& column : row)
            if (column == '.')
                return false;
    return true;
}

bool G8_UI::minimax_win(char sym, vector<vector<char>>& board)
{
    vector<vector<pair<int, int>>> wins = {
        // Diagonals
        {{0,2}, {1,1}, {2,0}},
        {{0,2}, {1,2}, {2,2}},
        {{0,2}, {1,3}, {2,4}},

        // Middle row
        {{1,1}, {1,2}, {1,3}},

        // Bottom row combinations
        {{2,0}, {2,1}, {2,2}},
        {{2,1}, {2,2}, {2,3}},
        {{2,2}, {2,3}, {2,4}},

    };

    for (auto& w : wins) {
        if (board[w[0].first][w[0].second] == sym &&
            board[w[1].first][w[1].second] == sym &&
            board[w[2].first][w[2].second] == sym)
            return true;
    }

    return false;
}
Pyramid G8_UI::getBestMove(const vector<vector<char>>& board,
    bool maximizing, int depth, int alpha, int beta) {

    vector<vector<char>> boardCopy = board;

    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;


    if (minimax_win(aiSymbol, boardCopy))
        return { -1, -1, 10 - depth }; // Prefer Winning sooner

    if (minimax_win(opponentSymbol, boardCopy))
        return { -1, -1, -10 + depth }; // Prefer Losing later

    if (boardFull(boardCopy))
        return { -1, -1, 0 }; // Terminal state for a draw while Recursing

    if (depth >= max_depth)
        return { -1,-1, 0 }; // No score after too many tries
                            // This saves time

    Pyramid bestMove;
    bestMove.score = maximizing ? INT_MIN : INT_MAX;

    for (int x = 0; x < boardCopy.size(); x++)
    {
        for (int y = 0; y < boardCopy[x].size(); y++)
        {
            if (boardCopy[x][y] == '.') {

                boardCopy[x][y] = trackingSymbol;

                Pyramid result = getBestMove(boardCopy, !maximizing, depth + 1, alpha, beta);

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

void G8_UI::display_board_matrix(const vector<vector<char>>& matrix) const
{
    cout << "\n         0   1   2   3   4\n\n";

    // Row 0 (single cell at column 2)
    cout << "                -+-\n";
    cout << "0              | " << matrix[0][2] << " |\n";
    cout << "            ---+---+---\n";

    // Row 1 (columns 1–3)
    cout << "1          | "
        << matrix[1][1] << " | "
        << matrix[1][2] << " | "
        << matrix[1][3] << " |\n";
    cout << "        ---+---+---+---+---\n";

    // Row 2 (columns 0–4)
    cout << "2      | "
        << matrix[2][0] << " | "
        << matrix[2][1] << " | "
        << matrix[2][2] << " | "
        << matrix[2][3] << " | "
        << matrix[2][4] << " |\n";
    cout << "        ---+---+---+---+---\n";

    cout << endl;
}
