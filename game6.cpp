 

#include <iostream>
#include <iomanip>
#include <cctype>  
#include "game6.h"



using namespace std;

bool Diamond::diamond(int x, int y)
{
    if (x == 0 && y == 3)return true;
    if (x == 1 && (y == 2 || y == 3 || y == 4))return true;
    if (x == 2 && (y == 1 || y == 2 || y == 3 || y == 4 || y == 5)) return true;
    if (x == 3) return true;
    if (x==4 && (y == 1 || y == 2 || y == 3 || y == 4 || y == 5)) return true; 
    if (x == 5 && (y == 2|| y == 3|| y == 4))return true;
    if (x == 6 && (y == 3))return true;

    return false;
}

Diamond::Diamond() : Board(7,7) {  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (diamond(i, j)) {
                board[i][j] = blank_symbol;
            }
            
        }
    }
}




bool Diamond::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (diamond(x, y) && board[x][y] == blank_symbol) {
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

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (diamond(i, j) && diamond(i, j + 1) && diamond(i, j + 2) && board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym) {
                three = true;
            }
        }
    }

    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 3; i++) {
            if (diamond(i, j) && diamond(i + 1, j) && diamond(i + 2, j) &&  board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym) {
                three = true;
            }
        }
    }

    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (diamond(i, j) && diamond(i + 1, j + 1) && diamond(i + 2, j + 2) && board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym) {
                three = true;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (diamond(i, j) && diamond(i, j + 1) && diamond(i, j + 2) && diamond(i, j + 3) && board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym) {
                four = true;
            }
        }
    }
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 4; i++) {
            if (diamond(i, j) && diamond(i + 1, j) && diamond(i + 2, j) && diamond(i + 3, j) && board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym) {
                four = true;
            }
        }
    }
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (diamond(i, j) && diamond(i + 1, j + 1) && diamond(i + 2, j + 2) && diamond(i + 3, j + 3) && board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                four = true;
            }
        }
    }

    if (three && four) {
        return true;
    }
    return false;
}





bool Diamond::is_draw(Player<char>* player) {
    return (n_moves == 25 && !is_win(player));
}

bool Diamond::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}





Diamond_UI::Diamond_UI() : UI<char>("Let's Play Diamond Tic-Tac-Toe", 3) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
 
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 6): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

void Diamond_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    UI<char>::display_board_matrix(matrix);
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

