#pragma once
#include "view.h"
#include "game.h"
#include <cctype>

class HumanC {
private:
	View *view_;
	Snake& snake;
	void Control(int key) {
		switch (std::toupper(key)) {
			case 'W':
				snake.dir_=Y_DEC;
				return;
			case 'S':
				snake.dir_=Y_INC;
				return;
			case 'A':
				snake.dir_=X_DEC;
				return;
			case 'D':
				snake.dir_=X_INC;
				return;
		}
	}
public:
	HumanC(Game &game, View *view) : view_(view), snake(game.makeSnake()) {
		view_->subscribeKey(std::bind(&HumanC::Control, this, std::placeholders::_1));
	}
};
