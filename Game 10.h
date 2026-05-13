#pragma once
#include "BoardGame_Classes.h"
using namespace std;

class Obstacles : public Board<char> {
private:
    char blank_symbol = '.'; 
    char obstacle_symbol = '#';
    int moves_count = 0;

    void add_obstacle();

public:
    
    Obstacles();

    
    bool update_board(Move<char>* move);

 
    bool is_win(Player<char>* player);

   
    bool is_lose(Player<char>*) { return false; };

 
    bool is_draw(Player<char>* player);

    
    bool game_is_over(Player<char>* player);
};

class Obstacles_UI : public UI<char> {
public:
   
    Obstacles_UI();

    
    ~Obstacles_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};
