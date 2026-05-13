#include <iostream>
#include <vector>
#include <memory>

#include "Game 1.h"
#include "Game 2.h"
#include "Game 3.h"
#include "Game 4.h"
#include "Game 5.h"
#include "Game 6.h"
#include "Game 7.h"
#include "Game 8.h"
#include "Game 9.h"
#include "Game 10.h"
#include "Game 11.h"
#include "Game 12.h"
#include "Game 13.h"
#include "Instructions.h"

using namespace std;

template<typename T>
void choiceGame(Board<T>* board, UI<T>* ui) {

    // Create Players
    Player<T>** players = ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<T> game(board, players, ui);

    // Run
    game.run();

    // Cleanup players
    delete players[0];
    delete players[1];
    delete[] players;
}

void displayMenu() {
    int choice;
    do {
        cout << "\n========================\n";
        cout << "   BOARD GAME MENU\n";
        cout << "========================\n";
        cout << "1. SUS\n";
        cout << "2. Connect 4 Tic Tac Toe\n";
        cout << "3. 5x5 TicTac Toe\n";
        cout << "4. Word Tic Tac Toe\n";
        cout << "5. Misere Tic Tac Toe\n";
        cout << "6. Diamond Tic Tac Toe\n";
        cout << "7. 4x4 Tic-Tac-Toe (Extended Version)\n";
        cout << "8. Pyramid Tic-Tac-Toe\n";
        cout << "9. Numerical Tic-Tac-Toe\n";
        cout << "10. Obstacles Tic-Tac-Toe \n";
        cout << "11. Infinity Tic-Tac-Toe \n";
        cout << "13. Hidden Tic-Tac-Toe \n";
        cout << "110. View Games Instructions\n";
        cout << "111. Exit\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            // Clear the error state
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "Error: That was not a number. Please "
                "enter a number: ";
        }

        Board<char>* board = nullptr;
        UI<char>* ui = nullptr;
        switch (choice) {
        case 1:
            board = new G1_Board();
            ui = new G1_UI();
            break;
        case 2:
            board = new G2_Board();
            ui = new G2_UI();
            break;
        case 3:
            board = new G3_Board();
            ui = new G3_UI();
            break;
        case 4:
            board = new G4_Board();
            ui = new G4_UI();
            break;
        case 5:
            board = new Misere();
            ui = new Misere_UI();
            break;
        case 6:
            board = new Diamond();
            ui = new Diamond_UI();
            break;
        case 7:
            board = new Tic_4();
            ui = new Tic_4_UI();
            break;
        case 8:
            board = new G8_Board();
            ui = new G8_UI();
            break;
        case 9: {
            Board<int>* board_int = new G9_Board();
            UI<int>* ui_int = new G9_UI();
            choiceGame(board_int, ui_int);
            delete board_int;
            delete ui_int;
            break;
        }
        case 10:
            board = new Obstacles();
            ui = new Obstacles_UI();
            break;
        case 11:
            board = new G11_Board();
            ui = new G11_UI();
            break;

        case 12:
            board = new Ultimate_TicTacToe();
            ui = new Ultimate_TicTacToe_UI();
            break;
        case 13:
            board = new G13_Board();
            ui = new G13_UI();
            break;
        case 110:
            displayAllInstructions();
            break;
        case 111:
            cout << "Thank you for playing! Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        if (board && ui) {
            choiceGame(board, ui);
            delete board;
            delete ui;
        }

        cin.ignore(1000, '\n');

    } while (choice != 111);
}

int main() {
    displayMenu();
    return 0;
}