#include <iostream>
#include "Game 11.h"

G11_Board::G11_Board() : Board(3,3){
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = emptyCell;
}

bool G11_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if the move is within bounds and the cell is empty
    if (x >= 0 && x < columns && y >= 0 && y < rows && board[x][y] == emptyCell) {
        board[x][y] = toupper(symbol);
        n_moves++;
        vec.push_back({ x, y }); // pushing position into vector
        if (n_moves % 3 == 0) { // Here we delete the oldest move for every 3 moves
            int new_x = vec[deleted].first;
            int new_y = vec[deleted].second;
            board[new_x][new_y] = emptyCell;
            deleted++;
        }
        return true;
    }
    return false;
}

// This whole code is similar to the basic one for Tic Tac Toe
// There's no advanced adjustments 

bool G11_Board::is_win(Player<char>* player)
{
    char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != emptyCell;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool G11_Board::fullBoard()
{
    for (auto& row : board)
        for (auto& c : row)
            if (c == emptyCell)
                return false;
    return true;
}

bool G11_Board::is_draw(Player<char>* player)
{
    return (fullBoard() && !is_win(player));
}

bool G11_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}

// UI Implementation
G11_UI::G11_UI() : UI<char>("Welcome to infinity Tic-Tac-Toe by C- Bosses", 3){}

Player<char>* G11_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating ";

    if (type == PlayerType::COMPUTER) {
        cout << "AI Player: " << name << " (" << symbol << ")\n";
        return new AI(name, symbol); // Create AI Player
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
}

Move<char>* G11_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 3): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        cout << "\nAI is thinking...\n";
        AI* aiPlayer = dynamic_cast<AI*>(player); // AI player
        return aiPlayer->get_move(player);
    }
}