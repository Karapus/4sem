#pragma once
#include "view.h"
#include "game.h"
#include <functional>

class BotC {
private:
	Snake& snake_;
	const std::list<Rabbit> &rabs_;
	const std::list<Snake> &snks_;
	
	void Control() {
		auto head = snake_.cords_.front();
		auto rab = rabs_.front().pos;
		if (head.x < rab.x)
			snake_.dir_ = X_INC;
		if (head.x > rab.x)
			snake_.dir_ = X_DEC;
		if (head.y < rab.y)
			snake_.dir_ = Y_INC;
		if (head.y > rab.y)
			snake_.dir_ = Y_DEC;
	}
public:
	BotC(Game &game, View *view) :
		snake_(game.makeSnake()),
		rabs_(game.getRabbits()),
		snks_(game.getSnakes())
	{
		view->subscribeTimer(std::bind(&BotC::Control, this));
	}
};
