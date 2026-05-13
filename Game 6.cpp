#include "Game 6.h"

Diamond::Diamond() : Board(7, 7) {
    char diamond[7][7] = {
    {' ', ' ', ' ', blank_symbol, ' ', ' ', ' '},
    {' ', ' ', blank_symbol, blank_symbol, blank_symbol, ' ', ' '},
    {' ', blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol, ' '},
    {blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol},
    {' ', blank_symbol, blank_symbol, blank_symbol, blank_symbol, blank_symbol, ' '},
    {' ', ' ', blank_symbol, blank_symbol, blank_symbol, ' ', ' '},
    {' ', ' ', ' ', blank_symbol, ' ', ' ', ' '}
    };

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = diamond[i][j];
}

bool Diamond::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == blank_symbol) {
        n_moves++;
        board[x][y] = mark;
        return true;
    }

    return false;
}

bool Diamond::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    bool three = false;
    bool four = false;

    // Check horizontal for 3 in a row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym) {
                three = true;
            }
        }
    }

    // Check vertical for 3 in a row
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 3; i++) {
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym) {
                three = true;
            }
        }
    }

    // Check diagonal for 3 in a row
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym) {
                three = true;
            }
        }
    }

    // Check anti-diagonal for 3 in a row
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 2; j < columns; j++) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym) {
                three = true;
            }
        }
    }

    // Check horizontal for 4 in a row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym) {
                four = true;
            }
        }
    }

    // Check vertical for 4 in a row
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 4; i++) {
            if (board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym) {
                four = true;
            }
        }
    }

    // Check diagonal for 4 in a row
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                four = true;
            }
        }
    }

    // Check anti-diagonal for 4 in a row
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym) {
                four = true;
            }
        }
    }

    return (three && four);
}

bool Diamond::is_draw(Player<char>* player) {
    return (n_moves == 25 && !is_win(player));
}

bool Diamond::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ========== UI Logic Functions ==========

Diamond_UI::Diamond_UI() : UI<char>("Let's Play Diamond Tic-Tac-Toe", 4) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {

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

Move<char>* Diamond_UI::get_move(Player<char>* player) {

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << "\nPlease enter your move x and y (0 to 6): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        char aiSymbol = player->get_symbol();
        char opponentSymbol = (aiSymbol == 'X' ? 'O' : 'X');

        // Get best move using minimax with alpha-beta pruning
        Diamond_AI best = getBestMove(matrix, true, 0, INT_MIN, INT_MAX);

        return new Move<char>(best.x, best.y, aiSymbol);
    }
}

void Diamond_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n    0   1   2   3   4   5   6\n";

    cout << "               -+-             \n";
    cout << "0             | " << matrix[0][3] << " | \n";
    cout << "           ---+---+---         \n";
    cout << "1         | " << matrix[1][2] << " | " << matrix[1][3] << " | " << matrix[1][4] << " |  \n";
    cout << "       ---+---+---+---+---     \n";
    cout << "2     | " << matrix[2][1] << " | " << matrix[2][2] << " | " << matrix[2][3] << " | " << matrix[2][4] << " | " << matrix[2][5] << " |   \n";
    cout << "  +---+---+---+---+---+---+---+\n";
    cout << "3 | " << matrix[3][0] << " | " << matrix[3][1] << " | " << matrix[3][2] << " | " << matrix[3][3] << " | " << matrix[3][4] << " | " << matrix[3][5] << " | " << matrix[3][6] << " |\n";
    cout << "  +---+---+---+---+---+---+---+ \n";
    cout << "4     | " << matrix[4][1] << " | " << matrix[4][2] << " | " << matrix[4][3] << " | " << matrix[4][4] << " | " << matrix[4][5] << " |   \n";
    cout << "       ---+---+---+---+---     \n";
    cout << "5         | " << matrix[5][2] << " | " << matrix[5][3] << " | " << matrix[5][4] << " |      \n";
    cout << "           ---+---+---         \n";
    cout << "6             | " << matrix[6][3] << " |   \n";
    cout << "               -+-           \n";
    cout << endl;
}

// ========== AI Logic Functions ==========

bool Diamond_UI::boardFull(const vector<vector<char>>& board) {
    for (auto& row : board)
        for (auto& column : row)
            if (column == '.')
                return false;
    return true;
}

bool Diamond_UI::minimax_win3(char sym, vector<vector<char>>& board) {

    bool three = false;

    // Check horizontal for 3 in a row
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j <= 4; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym) {
                three = true;
            }
        }
    }

    // Check vertical for 3 in a row
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i <= 4; i++) {
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym) {
                three = true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right) for 3 in a row
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym) {
                three = true;
            }
        }
    }

    // Check anti-diagonal (top-right to bottom-left) for 3 in a row
    for (int i = 0; i <= 4; i++) {
        for (int j = 2; j < 7; j++) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym) {
                three = true;
            }
        }
    }

    return three;
}

bool Diamond_UI::minimax_win4(char sym, vector<vector<char>>& board)
{
    bool four = false;

    // Check horizontal for 4 in a row
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j <= 3; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym) {
                four = true;
            }
        }
    }

    // Check vertical for 4 in a row
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i <= 3; i++) {
            if (board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym) {
                four = true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right) for 4 in a row
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                four = true;
            }
        }
    }

    // Check anti-diagonal (top-right to bottom-left) for 4 in a row
    for (int i = 0; i <= 3; i++) {
        for (int j = 3; j < 7; j++) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym) {
                four = true;
            }
        }
    }
    return four;
}

Diamond_AI Diamond_UI::getBestMove(const vector<vector<char>>& board,
    bool maximizing, int depth, int alpha, int beta) {

    vector<vector<char>> boardCopy = board;

    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;

    bool aiWin = minimax_win3(aiSymbol, boardCopy) && minimax_win4(aiSymbol, boardCopy);
    bool oppWin = minimax_win3(opponentSymbol, boardCopy) && minimax_win4(opponentSymbol, boardCopy);

    if (aiWin)
        return { -1, -1, 1000 - depth };
    if (oppWin)
        return { -1, -1, -1000 + depth };

    if (boardFull(boardCopy))
        return { -1, -1, 0 };

    if (depth >= max_depth) {
        int score = 0;
        if (minimax_win3(aiSymbol, boardCopy)) score += 3;
        if (minimax_win4(aiSymbol, boardCopy)) score += 4;
        if (minimax_win3(opponentSymbol, boardCopy)) score -= 3;
        if (minimax_win4(opponentSymbol, boardCopy)) score -= 4;
        return { -1, -1, score };
    }

    Diamond_AI bestMove;
    bestMove.score = maximizing ? INT_MIN : INT_MAX;

    for (int x = 0; x < boardCopy.size(); x++)
    {
        for (int y = 0; y < boardCopy[x].size(); y++)
        {
            if (boardCopy[x][y] == '.') {

                boardCopy[x][y] = trackingSymbol;

                Diamond_AI result = getBestMove(boardCopy, !maximizing, depth + 1, alpha, beta);

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