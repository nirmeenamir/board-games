#include "Game 5.h"

Misere::Misere() : Board(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Misere::update_board(Move<char>* move)
{
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

bool Misere::is_win(Player<char>* player)
{
    return game_is_over(player) && !is_lose(player);
}

bool Misere::is_draw(Player<char>* player)
{

    return (n_moves == 9 && !is_win(player));
}

bool Misere::game_is_over(Player<char>* player)
{
    return is_lose(player) && n_moves == 9;
}

bool Misere::is_lose(Player<char>* player)
{
    const char sym = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

Misere_UI::Misere_UI() : UI<char>("Welcome to Misere by C- Bosses ", 3) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type)
{
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

Move<char>* Misere_UI::get_move(Player<char>* player)
{
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nYour turn, " << player->get_name() << "!\n";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        char aiSymbol = player->get_symbol();
        char opponentSymbol = (aiSymbol == 'X' ? 'O' : 'X');

        // Get best move using minimax with alpha-beta pruning
        MisereMove best = getBestMove(matrix, true, 0, 10, -100000, 100000);

        return new Move<char>(best.x, best.y, aiSymbol);
    }

    return nullptr;
}

// ========== AI Logic Functions ==========

bool Misere_UI::hasThreeInRow(char sym, const vector<vector<char>>& b) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == sym && b[i][1] == sym && b[i][2] == sym)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (b[0][i] == sym && b[1][i] == sym && b[2][i] == sym)
            return true;
    }

    // Check diagonals
    if (b[0][0] == sym && b[1][1] == sym && b[2][2] == sym)
        return true;
    if (b[0][2] == sym && b[1][1] == sym && b[2][0] == sym)
        return true;

    return false;
}

bool Misere_UI::boardFull(const vector<vector<char>>& b) {
    for (auto& row :b)
    {
        for (auto& col : row)
        {
            if (col == '.')
                return false;
        }
    }
    return true;
}

MisereMove Misere_UI::getBestMove(const vector<vector<char>>& board,
    bool maximizing, int depth, int max_depth, int alpha, int beta) {
    vector<vector<char>> boardCopy = board;

    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;

    // Terminal state checks
    if (hasThreeInRow(opponentSymbol, boardCopy))
        return { -1, -1, 10 - depth }; // prefer loosing sooner

    if (hasThreeInRow(aiSymbol, boardCopy))
        return { -1, -1, -10 + depth }; // prefer winning later

    if (boardFull(boardCopy))
        return { -1, -1, 0 }; // Terminal state for a draw while Recursing

    if (depth >= max_depth)
        return { -1,-1,0 }; // No score after too many tried
                            // This saves time

    MisereMove bestMove;
    bestMove.score = maximizing ? INT_MIN : INT_MAX;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++) {
            if (boardCopy[x][y] == '.') {

                boardCopy[x][y] = trackingSymbol;

                MisereMove result = getBestMove(boardCopy, !maximizing, depth + 1, max_depth, alpha, beta);

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
