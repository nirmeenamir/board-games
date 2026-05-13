#include <iostream>
#include <iomanip>
#include <cctype> 
#include "Game 10.h"

using namespace std;

Obstacles::Obstacles() : Board(6, 6) {
   
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    srand(time(0));
}

bool Obstacles::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol) {
        return false;
    }
    board[x][y] = toupper(mark);
    n_moves++;
    moves_count++;

    if (moves_count >= 2) {
        add_obstacle();
        moves_count = 0;
    }

    return true;
}

void Obstacles::add_obstacle() {
    int obst_added = 0;
    int max_obst = 10;

    while (obst_added < 2 && max_obst >0) {
        int x = rand() % rows;
        int y = rand() % columns;

        if (board[x][y] == blank_symbol) {
            board[x][y] = obstacle_symbol;
            obst_added++;
            n_moves++;
        }
        max_obst--;
    }

}

bool Obstacles::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym && board[i][j + 3] == sym ) {
                return true;
            }
        }
    }

    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 4; ++i) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym && board[i+3][j] == sym) {
                return true;
            }
        }
    }

    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == sym &&
                board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym &&
                board[i + 3][j + 3] == sym) {
                return true;
            }
        }
    }

    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 3; j < columns; ++j) {
            if (board[i][j] == sym &&
                board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym &&
                board[i + 3][j - 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool Obstacles::is_draw(Player<char>* player) {
    return (n_moves == 36 && !is_win(player));
}

bool Obstacles::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Obstacles_UI::Obstacles_UI() : UI<char>("Welcome to Obstacles by C - Bosses", 3) {}

Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type) {
    
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 5): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}