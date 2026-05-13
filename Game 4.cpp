#include "Game 4.h"

using namespace std;

// loading the names file
unordered_set<string> G4_Board::loadDictionary() {
    ifstream file("dic.txt"); // Please make sure you enter the right path of the file

    if (!file.is_open())
        return dict;

    string word;
    while (file >> word) {
        if (word.size() == 3)
            dict.insert(word);
    }

    return dict;
}

G4_Board::G4_Board() : Board<char>(3, 3){
    // Load the dictionary
    loadDictionary();

    // Initialize the board with empty cells
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = emptyCell;
}

bool G4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if the move is within bounds and the cell is empty
    if (x >= 0 && x < columns && y >= 0 && y < rows && board[x][y] == emptyCell) {
        board[x][y] = toupper(symbol);
        n_moves++;
        return true;
    }
    return false;
}

bool G4_Board::is_win(Player<char>* player) {

    // Check rows
    for (int i = 0; i < rows; ++i) {
        string row = "";
        row.push_back(board[i][0]);
        row.push_back(board[i][1]);
        row.push_back(board[i][2]);
        if (is_valid_word(row)) return true;
    }

    // Check columns
    for (int i = 0; i < columns; i++)
    {
        string col = "";
        col.push_back(board[0][i]);
        col.push_back(board[1][i]);
        col.push_back(board[2][i]);
        if (is_valid_word(col)) return true;
    }

    // Check Diagonal
    string diag = "";
    diag.push_back(board[0][0]);
    diag.push_back(board[1][1]);
    diag.push_back(board[2][2]);
    if (is_valid_word(diag)) return true;

    // Check anti Diagonal
    string anti_diag = "";
    anti_diag.push_back(board[0][2]);
    anti_diag.push_back(board[1][1]);
    anti_diag.push_back(board[2][0]);
    if (is_valid_word(anti_diag)) return true;

    return false;
}

bool G4_Board::is_valid_word(const string& word)
{
    if (dict.count(word) > 0) return true;
    else return false;
}

bool G4_Board::is_draw(Player<char>* player) {
    return (n_moves == rows * columns && !is_win(player));
}

bool G4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

G4_UI::G4_UI() : UI("Welcome to Word Tic-tac-toe by C- Bosses", 4), depth(0) {}

Player<char>* G4_UI::create_player(string& name, char symbol, PlayerType type) {
    if(type == PlayerType::COMPUTER) {
        cout << "Smart Computer Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
        }
    return nullptr;
}

Move<char>* G4_UI::get_move(Player<char>* player) {
    int x, y;
    char c;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): " << player->get_name() << " ";
        cin >> x >> y;
        cout << "\nPlease enter you character: " << player->get_name() << " ";
        cin >> c;
        return new Move<char>(x, y, c);
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        auto matrix = board->get_board_matrix();

        // Get best move using minimax with alpha-beta pruning
        WordAI best = getBestMove(matrix, true, 0, 7, INT_MIN, INT_MAX);

        return new Move<char>(best.x, best.y, letter);
    }
    return nullptr;
}

bool G4_UI::fake_is_win(const vector<vector<char>>& boardCopy) {

    // Check rows
    for (int i = 0; i < rows; ++i) {
        string row = "";
        row.push_back(boardCopy[i][0]);
        row.push_back(boardCopy[i][1]);
        row.push_back(boardCopy[i][2]);
        if (is_valid_word(row)) return true;
    }

    // Check columns
    for (int i = 0; i < columns; i++)
    {
        string col = "";
        col.push_back(boardCopy[0][i]);
        col.push_back(boardCopy[1][i]);
        col.push_back(boardCopy[2][i]);
        if (is_valid_word(col)) return true;
    }

    // Check Diagonal
    string diag = "";
    diag.push_back(boardCopy[0][0]);
    diag.push_back(boardCopy[1][1]);
    diag.push_back(boardCopy[2][2]);
    if (is_valid_word(diag)) return true;

    // Check anti Diagonal
    string anti_diag = "";
    anti_diag.push_back(boardCopy[0][2]);
    anti_diag.push_back(boardCopy[1][1]);
    anti_diag.push_back(boardCopy[2][0]);
    if (is_valid_word(anti_diag)) return true;

    return false;
}

bool G4_UI::boardFull(const vector<vector<char>>& board) {
    for (auto& row : board)
        for (auto& c : row)
            if (c == '.')
                return false;
    return true;
}

WordAI G4_UI::getBestMove(vector<vector<char>>& b, bool maximizing, int depth, int max_depth, 
    int alpha, int beta) {

    vector<vector<char>> boardCopy = b;
    
    if (fake_is_win(boardCopy)) {
        return maximizing
            ? WordAI(-1, -1,  10 - depth)
            : WordAI(-1, -1, -10 + depth);
    }

    if (boardFull(boardCopy))
        return { -1, -1, 0 }; // draw

    if (depth >= max_depth)
        return { -1 , -1, 0 }; // terminal state

    WordAI bestMove;
    bestMove.score = maximizing ? INT_MIN : INT_MAX;
    char alphabet[] = { 'A', 'E', 'I', 'O', 'U', 'R', 'S', 'T', 'N', 'L' };
    for (int x = 0; x < boardCopy.size(); x++)
    {
        for (int y = 0; y < boardCopy[x].size(); y++)
        {
            if (boardCopy[x][y] == '.') {
                for (auto& sym : alphabet) {

                    boardCopy[x][y] = sym;

                    WordAI result = getBestMove(boardCopy, !maximizing, depth + 1, max_depth, alpha, beta);

                    boardCopy[x][y] = '.';

                    if (maximizing) {
                        if (result.score > bestMove.score) {
                            bestMove = { x, y, result.score };
                            letter = sym;
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

