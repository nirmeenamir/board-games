#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class Diamond : public Board<char> {
private:
    char blank_symbol = '.'; 

public:
   
    Diamond();

    

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    bool diamond(int x, int y);
};

class Diamond_UI : public UI<char> {
public:
    
    Diamond_UI();

    ~Diamond_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);

   void display_board_matrix(const vector<vector<char>>& matrix) const ;
};

#endif // XO_CLASSES_H
