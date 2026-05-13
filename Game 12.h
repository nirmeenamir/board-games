#pragma once
#include "BoardGame_Classes.h"
#include "AI.h"
using namespace std;

class Ultimate_TicTacToe : public Board<char> {
private:
    char emptyCell = '.';
    vector<vector<vector<char>>> vec;  // 9 boards (0-8), each 3x3
    char mainBoard[3][3];              // Tracks which player won each sub-board
    int lastPlayedBoard;               // The last board that was played on (-1 initially)

    bool isSubBoardWon(int boardIndex);
    char checkSubBoardWinner(int boardIndex);
    bool isSubBoardFull(int boardIndex);
    void syncBoardMatrix();  // Syncs vec to board matrix for display

public:
    Ultimate_TicTacToe();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int getLastPlayedBoard() const { return lastPlayedBoard; }
    char getMainBoardCell(int row, int col) const { return mainBoard[row][col]; }
    bool isBoardAvailable(int boardIndex);
};

class Ultimate_TicTacToe_UI : public UI<char> {
public:
    Ultimate_TicTacToe_UI();
    ~Ultimate_TicTacToe_UI() {}

    const Ultimate_TicTacToe* displayer = nullptr;

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const override;
};