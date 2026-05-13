#include <iostream>
#include "Instructions.h"

using namespace std;

void displayAllInstructions() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "GAME INSTRUCTIONS MENU\n";
    cout << string(60, '=') << "\n\n";

    int choice;
    do {
        cout << "Select a game to view instructions:\n";
        cout << "1. SUS\n";
        cout << "2. Four in a row Tic Tac Toe\n";
        cout << "3. 5x5 Tic Tac Toe\n";
        cout << "4.  Word Tic Tac Toe\n";
        cout << "5. Misere Tic Tac Toe\n";
        cout << "7. 4x4 Tic Tac Toe (Extended Version)\n";
        cout << "8. Pyramid Tic Tac Toe\n";
        cout << "9. Numerical Tic Tac Toe\n";
        cout << "10. Obstacles Tic Tac Toe \n";
        cout << "112. Return to Main Menu\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            displaySUSInstructions();
            break;
        case 2:
            displayForInRowInstructions();
            break;
        case 3:
            display5x5Instructions();
            break;
        case 4:
            displayWordsInstructions();
            break;
        case 5:
            displayMisereInstructions();
            break;
        case 7:
            display4x4Instructions();
            break;
        case 8:
            displayPyramidInstructions();
            break;
        case 9:
            displayNumericalInstructions();
            break;
        case 10:
            displayObstaclesInstructions();
            break;
        case 11:
            displayInfinityInstructions();
            break;
        case 112:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1-5.\n";
        }
        if (choice >= 1 && choice <= 12) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 112);
}

void displaySUSInstructions() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "           SUS GAME INSTRUCTIONS\n";
    cout << string(50, '=') << "\n";
    cout << "OBJECTIVE:\n";
    cout << "   Form the sequence \"S-U-S\" to score points!\n\n";

    cout << "BOARD:\n";
    cout << "   3x3 grid\n\n";

    cout << "HOW TO PLAY:\n";
    cout << "   • Players take turns placing either \"S\" or \"U\" on the board\n";
    cout << "   • You must use the SAME letter each turn\n";
    cout << "   • Score 1 point for each \"S-U-S\" sequence you create\n";
    cout << "   • Sequences can be horizontal, vertical, or diagonal\n\n";

    cout << "WINNING:\n";
    cout << "   • Game ends when board is full\n";
    cout << "   • Player with most \"S-U-S\" sequences wins!\n\n";

    cout << "TIP: Plan your moves to create multiple overlapping sequences!\n";
}

void display5x5Instructions() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "       5x5 TIC-TAC-TOE INSTRUCTIONS\n";
    cout << string(50, '=') << "\n";
    cout << "OBJECTIVE:\n";
    cout << "   Create the most three-in-a-row sequences!\n\n";

    cout << "BOARD:\n";
    cout << "   5x5 grid (larger than classic Tic-Tac-Toe)\n\n";

    cout << "HOW TO PLAY:\n";
    cout << "   • Players take turns placing X and O on empty squares\n";
    cout << "   • Game continues until only ONE square remains empty\n";
    cout << "   • Total of 24 moves (12 for each player)\n\n";

    cout << "WINNING:\n";
    cout << "   • Count all three-in-a-row sequences for each player\n";
    cout << "   • Player with most sequences wins!\n";
    cout << "   • Sequences can overlap and count multiple times\n\n";

    cout << "TIP: Focus on creating patterns that form multiple lines!\n";
}

void displayMisereInstructions() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "      MISERE TIC-TAC-TOE INSTRUCTIONS\n";
    cout << string(50, '=') << "\n";
    cout << "OBJECTIVE:\n";
    cout << "   Force your opponent to get three-in-a-row!\n\n";

    cout << "BOARD:\n";
    cout << "   Standard 3x3 grid\n\n";

    cout << "HOW TO PLAY:\n";
    cout << "   • Players take turns placing X and O\n";
    cout << "   • AVOID placing three of your marks in a row\n";
    cout << "   • This includes rows, columns, and diagonals\n\n";

    cout << "WINNING:\n";
    cout << "   • You LOSE if you complete a line of three\n";
    cout << "   • If board fills with no three-in-a-row -> DRAW\n";
    cout << "   • Strategy: Force opponent into bad positions!\n\n";

    cout << "TIP: Sometimes blocking your opponent can force them to win!\n";
}

void display4x4Instructions() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "       4x4 TIC-TAC-TOE INSTRUCTIONS\n";
    cout << string(50, '=') << "\n";
    cout << "OBJECTIVE:\n";
    cout << "   Align three tokens in a row by moving them!\n\n";

    cout << "BOARD & SETUP:\n";
    cout << "   • 4x4 grid\n";
    cout << "   • Each player starts with 4 tokens\n";
    cout << "   • Tokens begin in specific starting positions\n\n";

    cout << "HOW TO PLAY:\n";
    cout << "   • On your turn, move ONE of your tokens\n";
    cout << "   • Movement: Horizontal or Vertical to adjacent empty square\n";
    cout << "   • NO diagonal moves\n";
    cout << "   • NO jumping over other tokens\n\n";

    cout << "WINNING:\n";
    cout << "   • First to align three tokens in row, column, or diagonal WINS!\n";
    cout << "   • Only three-in-a-row counts (not four)\n\n";

    cout << "TIP: Control the center and create multiple threats!\n";
}

void displayNumericalInstructions() {
    cout << "=== 3x3 Magic Number Game Instructions ===\n\n";

    cout << "Introduction:\n";
    cout << "A mathematical variant where players use numbers with the objective of making a line sum to 15.\n\n";

    cout << "Board:\n";
    cout << "A 3x3 grid.\n\n";

    cout << "Rules:\n";
    cout << "1. Player 1 uses odd numbers: 1, 3, 5, 7, 9.\n";
    cout << "2. Player 2 uses even numbers: 2, 4, 6, 8.\n";
    cout << "3. Players alternate placing one number in an empty cell.\n";
    cout << "4. Each number can be used only once per game.\n\n";

    cout << "Winning Condition:\n";
    cout << "A player wins by placing three numbers in a row, column, or diagonal that add up to exactly 15.\n";
    cout << "If all cells are filled and no line sums to 15, the game is a draw.\n\n";

    cout << "Good luck and think strategically!\n";
}

void displayPyramidInstructions() {
    cout << "=== Pyramid Tic-Tac-Toe Instructions ===\n\n";
    cout << "Introduction:\n";
    cout << "A Tic-Tac-Toe variant played on a pyramid-shaped game board.\n\n";

    cout << "Board:\n";
    cout << "The board has a pyramid structure:\n";
    cout << "  - Base row: 5 squares\n";
    cout << "  - Middle row: 3 squares\n";
    cout << "  - Top row: 1 square\n\n";

    cout << "Rules:\n";
    cout << "  1. Two players take turns placing their marks ('X' or 'O') on empty squares.\n";
    cout << "  2. Only one mark can occupy a square at a time.\n";
    cout << "  3. Players alternate turns until one wins or all squares are filled.\n\n";

    cout << "Winning Condition:\n";
    cout << "  The first player to align three of their marks in a straight line (horizontally, vertically, or diagonally) wins.\n\n";

    cout << "Good luck and have fun!\n";
}

void displayObstaclesInstructions() {
    cout << "=== Obstacles Tic-Tac-Toe Instructions ===\n\n";

    cout << "Introduction:\n";
    cout << "A dynamic Tic-Tac-Toe variant where obstacle cells are randomly added to the board, blocking squares.\n\n";

    cout << "Board:\n";
    cout << "  - A 6x6 grid.\n\n";

    cout << "Rules:\n";
    cout << "  1. Two players take turns placing their marks ('X' or 'O') on empty squares.\n";
    cout << "  2. After each round (one turn per player), two new obstacle cells are randomly added to the board.\n";
    cout << "  3. Obstacle cells cannot be used by either player.\n\n";

    cout << "Winning Condition:\n";
    cout << "  - The first player to align four of their marks in a row (horizontally, vertically, or diagonally) wins.\n";
    cout << "  - If the board fills completely without a winner, the game is a draw.\n\n";

    cout << "Strategy Tip: Watch for new obstacles as they can block potential winning lines!\n";
}

void displayInfinityInstructions() {
    cout << "================ Infinity Tic-Tac-Toe Instructions ================\n";
    cout << "Introduction:\n";
    cout << "A high-tempo variant of Tic-Tac-Toe where the board constantly evolves.\n";
    cout << "Players compete on a 3x3 grid, but older marks periodically fade out,\n";
    cout << "forcing dynamic decision-making and continuous strategic pivots.\n\n";

    cout << "Board:\n";
    cout << "- Standard 3x3 grid.\n\n";

    cout << "Rules:\n";
    cout << "- Players alternate turns placing their marks ('X' or 'O').\n";
    cout << "- Every three total moves, the *oldest* mark on the board is automatically removed.\n";
    cout << "- This creates a rolling 3-move memory window where only the most recent marks survive.\n";
    cout << "- If the board fills, old marks will continue disappearing as new ones are added.\n\n";

    cout << "Winning Condition:\n";
    cout << "- A player wins by aligning three of their marks horizontally, vertically, or diagonally.\n";
    cout << "- The alignment must occur *before* any of the involved marks vanish.\n\n";

    cout << "Strategic Insight:\n";
    cout << "- Time your plays; every mark has an expiration timer.\n";
    cout << "- Build momentum across cycles and anticipate which cell will clear next.\n";
    cout << "==================================================================\n";
}

void displayWordsInstructions() {
    cout << "================ Word Tic-Tac-Toe ================\n";
    cout << "Objective:\n";
    cout << "  Form a valid 3-letter English word horizontally,\n";
    cout << "  vertically, or diagonally before your opponent.\n\n";

    cout << "Board:\n";
    cout << "  - Standard 3x3 grid.\n\n";

    cout << "Rules:\n";
    cout << "  1. Players take turns placing ONE letter (A–Z) into any empty cell.\n";
    cout << "  2. You may build on top of letters already placed on the board to\n";
    cout << "     complete a valid 3-letter word.\n";
    cout << "  3. A word is considered valid only if it appears in dic.txt.\n\n";

    cout << "Winning Condition:\n";
    cout << "  - First player to create a valid 3-letter word in any row,\n";
    cout << "    column, or diagonal wins.\n\n";

    cout << "Draw Condition:\n";
    cout << "  - If the board fills completely with no valid word formed,\n";
    cout << "    the game ends in a draw.\n\n";

    cout << "Additional Notes:\n";
    cout << "  - All valid 3-letter words must be stored in dic.txt.\n";
    cout << "  - Letter input is case-insensitive.\n";
    cout << "==================================================\n";
}

void displayForInRowInstructions()
{
    cout << "==================== Four-in-a-Row ====================\n";
    cout << "Game Overview:\n";
    cout << "  • This is a grid-based version of Connect Four.\n";
    cout << "  • The board consists of 6 rows and 7 columns.\n\n";

    cout << "How to Play:\n";
    cout << "  1. Players take turns placing their symbol ('X' or 'O').\n";
    cout << "  2. A move is made by selecting a column (0–6).\n";
    cout << "  3. Your symbol automatically occupies the lowest available\n";
    cout << "     cell in that column.\n\n";

    cout << "Winning Conditions:\n";
    cout << "  • First player to connect FOUR symbols wins.\n";
    cout << "  • Valid connections include:\n";
    cout << "      - Horizontal (left/right)\n";
    cout << "      - Vertical (up/down)\n";
    cout << "      - Diagonal (up-right / down-right)\n\n";

    cout << "Draw Condition:\n";
    cout << "  • If the board fills up with no winning line, the match is a draw.\n\n";

    cout << "========================================================\n";
}
