#include "Game 13.h"
#include <iostream>

G13_Board::G13_Board() : Board(3, 3), vec(3, vector<char>(3, '.')) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			board[i][j] = blank_symbol;
}

bool G13_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    // Check if the move is within bounds and the cell is empty
    if (x >= 0 && x < columns && y >= 0 && y < rows && vec[x][y] == '.') {
        vec[x][y] = toupper(sym);
        board[x][y] = '?';
        n_moves++;
        return true;
    }
    return false;
}

bool G13_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(vec[i][0], vec[i][1], vec[i][2]) && vec[i][0] == sym) ||
            (all_equal(vec[0][i], vec[1][i], vec[2][i]) && vec[0][i] == sym)) {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    board[i][j] = vec[i][j];
                }
            }
            customDisplayer(vec);
            return true;
        }
    }

    // Check diagonals
    if ((all_equal(vec[0][0], vec[1][1], vec[2][2]) && vec[1][1] == sym) ||
        (all_equal(vec[0][2], vec[1][1], vec[2][0]) && vec[1][1] == sym)) {
        customDisplayer(vec);
        return true;
    }

    return false;
}

bool G13_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

void G13_Board::customDisplayer(vector<vector<char>> v)
{
    // This function is mimicking the display function from the frame work
    // This function is used to display the final result for the hidden cells

    cout << "===========================\n";
    cout << "   The UN-HIDDEN BOARD\n";
    cout << "\n    ";
    for (int j = 0; j < columns; ++j)
        cout << setw(4 + 1) << j;
    cout << "\n   " << string((4 + 2) * columns, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < columns; ++j)
            cout << setw(4) << v[i][j] << " |";
        cout << "\n   " << string((4 + 2) * columns, '-') << "\n";
    }
    cout << endl;
}

bool G13_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

G13_UI::G13_UI() : UI("Welcome to Hidden Tic-tac-toe by C- Bosses", 4) {}

Player<char>* G13_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* G13_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2) " << player->get_name() << " : ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }

    return new Move<char>(x, y, player->get_symbol());
}
