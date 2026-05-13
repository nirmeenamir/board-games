#pragma once
#include "BoardGame_Classes.h"
using namespace std;

class G9_Board : public Board<int> {
private:
    int blank_symbol = 0;

public:
    G9_Board();
    bool update_board(Move<int>* move);
    bool game_is_over(Player<int>* player);
    bool is_win(Player<int>* player);
    bool is_lose(Player<int>* player); 
    bool is_draw(Player<int>* player);
};

template <typename T>
class G9_Player : public Player<T> {
public:
	G9_Player(string n, T s, PlayerType t)
		: Player<T>(n, s, t), count(0) {}

	void add_sum() { count++; }
	int get_count() const { return count; }
	void reset_sum() { count = 0; }

private:
	int count;
};
class G9_Move : public Move<int> {
private:
	int number;
public:
	
    G9_Move(int x, int y, int num)
		: Move<int>(x, y, num) {}

    int get_number() const { return this->get_symbol(); }
};

class G9_UI : public UI<int> {
public:
	G9_UI();
	~G9_UI() {};

	Player<int>* create_player(string& name, int symbol, PlayerType type);
	Move<int>* get_move(Player<int>* player) override;
};