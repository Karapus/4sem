#pragma once
#include "game.h"

class View {
public:
	virtual void draw() = 0;
	virtual void run() = 0;
	virtual void drawRab(Coord pos) = 0;
	virtual void drawSnake(Coord head, Coord tail) = 0;
	virtual void drawSnake(std::list<Coord> body) = 0;
	virtual Coord getSize() const = 0;
	virtual ~View() = default; 
};
