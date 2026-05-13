#include "AI.h"

using namespace std;
 
AI::AI(string name, char symbol) : Player(name, symbol, PlayerType::COMPUTER), depth(0) {
    aiSymbol = symbol;
    opponentSymbol = (symbol == 'X' ? 'O' : 'X');
}

Move<char>* AI::get_move(Player<char>* player) {
    Board<char>* board = get_board_ptr();
    auto matrix = board->get_board_matrix();
    auto start = chrono::high_resolution_clock::now();

    AiMove best = getBestMove(matrix, true, 0, 7, -100000, 100000);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "AI took: " << elapsed.count() << " seconds\n";

    return new Move<char>(best.x, best.y, aiSymbol);
}

bool AI::fake_is_win(char sym, const vector<vector<char>>& b)
{
    int rows = b.size();
    int cols = b[0].size();

    // Check rows
    for (int i = 0; i < rows; i++)
        for (int j = 0; j <= cols - 3; j++)
            if (b[i][j] == sym && b[i][j + 1] == sym && b[i][j + 2] == sym)
                return true;

    // Check columns
    for (int j = 0; j < cols; j++)
        for (int i = 0; i <= rows - 3; i++)
            if (b[i][j] == sym && b[i + 1][j] == sym && b[i + 2][j] == sym)
                return true;

    // Check main diagonals
    for (int i = 0; i <= rows - 3; i++)
        for (int j = 0; j <= cols - 3; j++)
            if (b[i][j] == sym && b[i + 1][j + 1] == sym && b[i + 2][j + 2] == sym)
                return true;

    // Check anti-diagonals
    for (int i = 0; i <= rows - 3; i++)
        for (int j = 2; j < cols; j++)
            if (b[i][j] == sym && b[i + 1][j - 1] == sym && b[i + 2][j - 2] == sym)
                return true;

    return false;
}

bool AI::boardFull(const vector<vector<char>>& b)
{
    for (auto& row : b)
        for (auto& c : row)
            if (c == blankSymbol)
                return false;
    return true;
}

AiMove AI::getBestMove(const vector<vector<char>>& board, bool maximizing, int depth, int max_depth, int alpha, int beta)
{
    vector<vector<char>> boardCopy = board;

    char trackingSymbol = maximizing ? aiSymbol : opponentSymbol;

    if (boardCopy.size() <= 3) {
        max_depth = 10;
    }
    else
        max_depth = 7;

    // Terminal state checks
    if (fake_is_win(aiSymbol, boardCopy))
        return { -1, -1, 10 - depth };

    if (fake_is_win(opponentSymbol, boardCopy))
        return { -1, -1, -10 + depth };

    if (boardFull(boardCopy))
        return { -1, -1, 0 };

    if (depth >= max_depth)
        return { -1,-1,0 };

    AiMove bestMove;
    bestMove.score = maximizing ? -100000 : 100000;

    for (int x = 0; x < boardCopy.size(); x++)
    {
        for (int y = 0; y < boardCopy[x].size(); y++)
        {
            if (boardCopy[x][y] == blankSymbol) {

                boardCopy[x][y] = trackingSymbol;

                AiMove result = getBestMove(boardCopy, !maximizing, depth + 1, max_depth, alpha, beta);

                boardCopy[x][y] = blankSymbol;

                if (maximizing) {
                    if (result.score > bestMove.score) {
                        bestMove = { x, y, result.score };
                    }
                    alpha = max(alpha, result.score);

                    // Prune here
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