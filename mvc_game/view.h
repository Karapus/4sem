#pragma once
#include "game.h"
#include <functional>

struct View {
	virtual void draw() = 0;
	virtual void stop() = 0;
	virtual void runloop() = 0;
	virtual void drawEmpty(Coord pos) = 0;
	virtual void drawRab(Coord pos) = 0;
	virtual void drawSnake(Coord head) = 0;
	virtual void drawSnake(Coord head, Coord tail) = 0;
	virtual void drawSnake(std::list<Coord> body) = 0;
	using KeyFn = std::function<void(int)>; 
	virtual void subscribeKey(KeyFn callkey) = 0;
	using TimerFn = std::function<void()>; 
	virtual void subscribeTimer(TimerFn calltimer, int period) = 0;
	virtual Coord getSize() const = 0;
	virtual ~View() = default; 
};
