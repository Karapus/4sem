#pragma once
#include <list>
#include "view.h"

enum Direction {X_INC = 0, X_DEC, Y_INC, Y_DEC, DIRS_N};
Coord nextCord(Coord pos, Direction dir);

struct Rabbit {
	Coord pos;
	Rabbit(Coord p);
};

bool operator == (Coord lhs, Coord rhs);
bool operator == (Rabbit lhs, Rabbit rhs);

class Snake {
	public:
	std::list<Coord> cords_;
	Color clr_ = WHITE;
	Direction dir_;
	auto getCords() const {
		return cords_;
	}
	Snake(std::list<Coord> &&body, Direction dir);
};

class Game final {
	unsigned rabs_n_;
	unsigned snakes_l_;
	std::list<Rabbit> rabbits_;
	std::list<Snake> snakes_;
	Coord getFreePos() const;
	Coord getFreePos(Coord prev_pos) const;
public:
	void tick();
	Game(unsigned rabs_n = 20, unsigned snks_l = 3, unsigned period = 100);
	Snake &makeSnake();
	const auto &getSnakes() const {
		return snakes_;
	}
	const auto &getRabbits() const {
		return rabbits_;
	}
	bool checkIfFree(Coord cord) const;
};
