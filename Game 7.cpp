#include <iostream>
#include <iomanip>
#include "Game 7.h"

using namespace std;

Tic_4::Tic_4() : Board<char>(4, 4) {
    // Initialize the board with empty cells
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = emptyCell;
}

bool Tic_4::update_board(Move<char>* move) {
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

bool Tic_4::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Check rows
    for (int i = 0; i < rows; i++)
        for (int j = 0; j <= columns - 3; j++)
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                return true;

    // Check columns
    for (int j = 0; j < columns; j++)
        for (int i = 0; i <= rows - 3; i++)
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                return true;

    // Check main diagonal
    for (int i = 0; i <= rows - 3; i++)
        for (int j = 0; j <= columns - 3; j++)
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                return true;

    // Check anti-diagonal
    for (int i = 0; i <= rows - 3; i++)
        for (int j = 2; j < columns; j++)
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym)
                return true;

    return false;
}

bool Tic_4::is_draw(Player<char>* player) {
    return (n_moves == rows * columns && !is_win(player));
}

bool Tic_4::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// Tic_4_UI Implementation
Tic_4_UI::Tic_4_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe by C- Bosses", 4) {}

Player<char>* Tic_4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating ";

    if (type == PlayerType::COMPUTER) {
        cout << "Smart Computer Player: " << name  << " (" << symbol << ")\n";
        return new AI(name, symbol); // Create AI Player
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
}

Move<char>* Tic_4_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 3): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        cout << "\nAI is thinking...\n";
        AI* aiPlayer = dynamic_cast<AI*>(player);
        return aiPlayer->get_move(player);
    }
}
