#include <iostream>

#include <set>
#include "Game 9.h"

using namespace std;

set<int> s1 = { 1, 3, 5, 7, 9 };
set<int> s2 = { 2, 4, 6, 8 };

// Display function
void displaySet(set<int> s) {
    cout << "(";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it;
        auto next = it;
        if (++next != s.end()) cout << ", ";
    }
    cout << ")\n";
}

G9_Board::G9_Board() : Board(3, 3) {

	for (auto& row : board)
		for (auto& cell : row)
			cell = 0;
}
bool G9_Board::update_board(Move<int>* move) {
	int x = move->get_x();
	int y = move->get_y();
	int mark = move->get_symbol();
	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == 0 || mark == 0)) {
		if (mark == 0) {
			n_moves--;
			board[x][y] = 0;
		}
        else {
            n_moves++;
            board[x][y] = mark;
        }
		return true;
	}
	return false;
}

bool G9_Board::is_win(Player<int>* player) {
    
    auto fif = [](int a, int b, int c) {
        return a != 0 && b != 0 && c != 0 && a + b + c == 15;
        };

    for (int i = 0; i < rows; ++i) {
        if (fif(board[i][0], board[i][1], board[i][2]) ||
            fif(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    if (fif(board[0][0], board[1][1], board[2][2]) ||
        fif(board[0][2], board[1][1], board[2][0]))
        return true;

        return false;
}

bool G9_Board::is_lose(Player<int>*player) {
    (void)player;
    return is_win(player);
}

bool G9_Board::is_draw(Player<int>*player) {
	return (n_moves == 9 && !is_win(player));
}

bool G9_Board::game_is_over(Player<int>* player) {
	return is_win(player) || is_draw(player);
}

G9_UI::G9_UI() : UI<int>("Welcome to 3x3 Magic Game by C - Bosses",3) {}

Player<int>* G9_UI::create_player(string& name, int symbol, PlayerType type) {
        
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << (symbol % 2 == 1 ? " (Even Player)" : " (Odd Player)") << "\n";

    return new G9_Player<int>(name, symbol, type);
}

Move<int>* G9_UI::get_move(Player<int>* player) {
    int x, y, number;
    bool is_valid = false;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nYour turn, " << player->get_name() << "!\n";
        while (!is_valid) {
            cout << "Enter position (x y): ";
            cin >> x >> y;

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "Invalid position! Please enter values between 0 and 2.\n";
                continue;
            }

            auto board_ptr = player->get_board_ptr()->get_board_matrix();
            if (board_ptr[x][y] != 0) {
                cout << "Position (" << x << "," << y << ") is already taken! Choose another position.\n";
                continue;
            }

            if (player->get_symbol() % 2 == 0) {
                displaySet(s1);
                cout << "Enter an odd number: ";
                cin >> number;
                if (s1.find(number) != s1.end()) {
                    is_valid = true;
                    s1.erase(number);
                }
                else {
                    cout << "Invalid number! Allowed numbers: ";
                    displaySet(s1);
                }
            }
            else {
                displaySet(s2);
                cout << "Enter an even number: ";
                cin >> number;
                if (s2.find(number) != s2.end()) {
                    is_valid = true;
                    s2.erase(number);
                }
                else {
                    cout << "Invalid number! Allowed numbers: ";
                    displaySet(s2);
                }
            }
        }
    }
    else {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();

        if (player->get_symbol() % 2 == 0) {
            int odd_numbers[] = { 1,3,5,7,9 };
            number = odd_numbers[rand() % 5];
        }
        else {
            int even_numbers[] = { 2,4,6,8 };
            number = even_numbers[rand() % 4];
        }
        cout << player->get_name() <<" chose position (" << x << "," << y << ") and number " << number << "\n";
    }

    return new G9_Move(x, y, number);
}
