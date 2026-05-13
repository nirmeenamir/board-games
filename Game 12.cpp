#include <iostream>
#include <iomanip>
#include "Game 12.h"

using namespace std;

Ultimate_TicTacToe::Ultimate_TicTacToe() : Board<char>(9, 9) {
    // Initialize vec as 9 sub-boards, each 3x3, filled with emptyCell
    vec = vector<vector<vector<char>>>(9, vector<vector<char>>(3, vector<char>(3, emptyCell)));

    // Initialize main board
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mainBoard[i][j] = emptyCell;

    // Initialize the display board matrix (9x9) with empty cells
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = emptyCell;

    lastPlayedBoard = -1;  // No board played yet
}

void Ultimate_TicTacToe::syncBoardMatrix() {
    // Sync the vec structure to the board matrix for display
    for (int boardIndex = 0; boardIndex < 9; boardIndex++) {
        int mainRow = boardIndex / 3;
        int mainCol = boardIndex % 3;

        for (int subRow = 0; subRow < 3; subRow++) {
            for (int subCol = 0; subCol < 3; subCol++) {
                int y = mainRow * 3 + subRow;
                int x = mainCol * 3 + subCol;
                board[y][x] = vec[boardIndex][subRow][subCol];
            }
        }
    }
}

bool Ultimate_TicTacToe::isSubBoardWon(int boardIndex) {
    int mainRow = boardIndex / 3;
    int mainCol = boardIndex % 3;
    return mainBoard[mainRow][mainCol] != emptyCell;
}

bool Ultimate_TicTacToe::isBoardAvailable(int boardIndex) {
    if (boardIndex < 0 || boardIndex > 8)
        return false;
    return !isSubBoardWon(boardIndex) && !isSubBoardFull(boardIndex);
}

char Ultimate_TicTacToe::checkSubBoardWinner(int boardIndex) {
    auto& subBoard = vec[boardIndex];

    // Check rows
    for (int i = 0; i < 3; i++)
        if (subBoard[i][0] != emptyCell &&
            subBoard[i][0] == subBoard[i][1] &&
            subBoard[i][1] == subBoard[i][2])
            return subBoard[i][0];

    // Check columns
    for (int j = 0; j < 3; j++)
        if (subBoard[0][j] != emptyCell &&
            subBoard[0][j] == subBoard[1][j] &&
            subBoard[1][j] == subBoard[2][j])
            return subBoard[0][j];

    // Check main diagonal
    if (subBoard[0][0] != emptyCell &&
        subBoard[0][0] == subBoard[1][1] &&
        subBoard[1][1] == subBoard[2][2])
        return subBoard[0][0];

    // Check anti-diagonal
    if (subBoard[0][2] != emptyCell &&
        subBoard[0][2] == subBoard[1][1] &&
        subBoard[1][1] == subBoard[2][0])
        return subBoard[0][2];

    return emptyCell;
}

bool Ultimate_TicTacToe::isSubBoardFull(int boardIndex) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (vec[boardIndex][i][j] == emptyCell)
                return false;
    return true;
}

bool Ultimate_TicTacToe::update_board(Move<char>* move) {
    // x = boardIndex (0-8), y = position within board (0-8)
    int boardIndex = move->get_x();
    int position = move->get_y();
    char symbol = move->get_symbol();

    // Validate boardIndex
    if (boardIndex < 0 || boardIndex > 8)
        return false;

    // Validate position
    if (position < 0 || position > 8)
        return false;

    // Check if the sub-board is already won or full
    if (!isBoardAvailable(boardIndex))
        return false;

    // Convert position (0-8) to row and column within the sub-board
    int row = position / 3;
    int col = position % 3;

    // Check if the cell is empty
    if (vec[boardIndex][row][col] != emptyCell)
        return false;

    // Make the move
    vec[boardIndex][row][col] = toupper(symbol);
    n_moves++;

    // Update lastPlayedBoard
    lastPlayedBoard = boardIndex;

    // Check if this sub-board is now won
    char winner = checkSubBoardWinner(boardIndex);
    int mainRow = boardIndex / 3;
    int mainCol = boardIndex % 3;

    if (winner != emptyCell) {
        mainBoard[mainRow][mainCol] = winner;
    }
    else if (isSubBoardFull(boardIndex)) {
        mainBoard[mainRow][mainCol] = 'T';  // Tie
    }

    // Sync the vec to board matrix for display
    syncBoardMatrix();

    return true;
}

bool Ultimate_TicTacToe::is_win(Player<char>* player) {
    // Only check if the last played board resulted in a win on the main board
    if (lastPlayedBoard == -1)
        return false;

    char sym = player->get_symbol();

    // Check rows on main board
    for (int i = 0; i < 3; i++)
        if (mainBoard[i][0] == sym &&
            mainBoard[i][1] == sym &&
            mainBoard[i][2] == sym)
            return true;

    // Check columns on main board
    for (int j = 0; j < 3; j++)
        if (mainBoard[0][j] == sym &&
            mainBoard[1][j] == sym &&
            mainBoard[2][j] == sym)
            return true;

    // Check main diagonal
    if (mainBoard[0][0] == sym &&
        mainBoard[1][1] == sym &&
        mainBoard[2][2] == sym)
        return true;

    // Check anti-diagonal
    if (mainBoard[0][2] == sym &&
        mainBoard[1][1] == sym &&
        mainBoard[2][0] == sym)
        return true;

    return false;
}

bool Ultimate_TicTacToe::is_draw(Player<char>* player) {
    // Check if all sub-boards are won or full
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (mainBoard[i][j] == emptyCell) {
                int boardIndex = i * 3 + j;
                if (!isSubBoardFull(boardIndex))
                    return false;
            }

    // If we get here, all boards are complete, check if no one won
    return !is_win(player);
}

bool Ultimate_TicTacToe::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// Ultimate_TicTacToe_UI Implementation
Ultimate_TicTacToe_UI::Ultimate_TicTacToe_UI()
    : UI<char>("Welcome to Ultimate Tic-Tac-Toe by C- Bosses", 3) {}

Player<char>* Ultimate_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating ";

    if (type == PlayerType::COMPUTER) {
        cout << "Smart Computer Player: " << name << " (" << symbol << ")\n";
        return new AI(name, symbol);
    }
    else if (type == PlayerType::HUMAN) {
        cout << "Human Player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
    return nullptr;
}

Move<char>* Ultimate_TicTacToe_UI::get_move(Player<char>* player) {
    int boardIndex, position;

    if (player->get_type() == PlayerType::HUMAN) {
        Ultimate_TicTacToe* game = dynamic_cast<Ultimate_TicTacToe*>(player->get_board_ptr());

        // Show available boards
        cout << "\nAvailable boards: ";
        for (int i = 0; i < 9; i++) {
            if (game->isBoardAvailable(i))
                cout << i << " ";
        }
        cout << "\n";

        cout << "Enter sub-board number (0-8): ";
        cin >> boardIndex;

        // Validate board selection
        while (!game->isBoardAvailable(boardIndex)) {
            cout << "Board " << boardIndex << " is not available. Choose another: ";
            cin >> boardIndex;
        }

        cout << "Enter position in sub-board (0-8):\n";
        cout << "  0 | 1 | 2\n";
        cout << "  ---------\n";
        cout << "  3 | 4 | 5\n";
        cout << "  ---------\n";
        cout << "  6 | 7 | 8\n";
        cout << "Position: ";
        cin >> position;

        return new Move<char>(boardIndex, position, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        cout << "\nAI is thinking...\n";
        AI* aiPlayer = dynamic_cast<AI*>(player);
        return aiPlayer->get_move(player);
    }
    return nullptr;
}

void Ultimate_TicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n=== ULTIMATE TIC-TAC-TOE ===\n\n";
    for (int i = 0; i < 3; ++i) {
        // Print the row
        for (int j = 0; j < 3; ++j) {
            char dis = displayer ? displayer->getMainBoardCell(i, j) : '.';
            cout << " " << dis << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";

        // Print separator between rows
        if (i < 2) cout << "---+---+---\n";
    }

    cout << "\n";

    // Display all 9 sub-boards
    for (int boardRow = 0; boardRow < 3; boardRow++) {
        // Display each row of sub-boards
        for (int subRow = 0; subRow < 3; subRow++) {
            for (int boardCol = 0; boardCol < 3; boardCol++) {
                int boardIndex = boardRow * 3 + boardCol;

                if (boardCol > 0) cout << "  |  ";

                // Display one row of this sub-board
                for (int subCol = 0; subCol < 3; subCol++) {
                    int y = boardRow * 3 + subRow;
                    int x = boardCol * 3 + subCol;
                    cout << matrix[y][x];
                    if (subCol < 2) cout << " ";
                }
            }
            cout << "\n";
        }

        // Separator between board rows
        if (boardRow < 2) {
            cout << "       |         |          \n";
            cout << "=======+=========+==========\n";
            cout << "       |         |          \n";
        }
    }
    cout << "\n";
}