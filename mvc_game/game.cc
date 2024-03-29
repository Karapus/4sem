#include "game.h"
#include "view.h"
#include <cctype>
#include <random>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <iostream>

namespace {

std::default_random_engine rand_gen{static_cast<unsigned>(time(0))};
}

Coord nextCord(Coord pos, Direction dir) {
	switch (dir) {
		case X_INC:
			++pos.x;
			return pos;
		case X_DEC:
			--pos.x;
			return pos;
		case Y_INC:
			++pos.y;
			return pos;
		case Y_DEC:
			--pos.y;
			return pos;
		case DIRS_N:
		default:
			return pos;
	}
}

Game::Game(unsigned rabs_n, unsigned snks_l, unsigned period) :
	rabs_n_(rabs_n),
	snakes_l_(snks_l)
{
	auto view = View::get();
	view->subscribeTimer(std::bind(&Game::tick, this), period);
	view->subscribeKey([=](int key){
			if (std::toupper(key) == 'Q')
				view->stop();
			});
}

Snake &Game::makeSnake() {
	std::list<Coord> body;
	body.push_back(getFreePos());
	auto dir = X_INC;
	for (unsigned i = 0; i < snakes_l_; i++)
		body.push_back(body.back());
	snakes_.push_back(Snake(std::move(body), dir));
	return snakes_.back();
}

Snake::Snake(std::list<Coord> &&body, Direction dir) : cords_(body), dir_(dir) {
}

Rabbit::Rabbit(Coord p) : pos(p) {
}

bool Game::checkIfFree(Coord cord) const {
	auto rab_pred = [&](auto rab){ return rab.pos == cord;};
	return std::none_of(rabbits_.cbegin(), rabbits_.cend(), rab_pred)
		&& checkIfCanMove(cord);
}

bool Game::checkIfCanMove(Coord cord) const {
	auto snake_pred = [&](auto snake){
		auto body = snake.getCords();
		return std::none_of(body.cbegin(), body.cend(), 
				[&](auto pos){return pos == cord; }); };
	return std::all_of(snakes_.cbegin(), snakes_.cend(), snake_pred);
}

Coord Game::getFreePos() const {
	Coord sz = View::get()->getSize();
	Coord cord;
	auto x_distr = std::uniform_int_distribution<int>(0, sz.x);
	auto y_distr = std::uniform_int_distribution<int>(0, sz.y);
	do {
		cord.x = x_distr(rand_gen);
		cord.y = y_distr(rand_gen);
	} while (!checkIfFree(cord));
	return cord;
}


void Game::tick() {
	auto view = View::get();
	auto sz = view->getSize();
	rabbits_.remove_if([=](auto r)
			{ return !r.pos.inside(sz) && (view->drawEmpty(r.pos), true); }
		);
	while (rabbits_.size() < rabs_n_)
		rabbits_.emplace_back(getFreePos());
	for (auto r : rabbits_) {
		view->drawRab(r.pos);
	}
	for (auto&& snake : snakes_) {
		if (!snake.can_move) {
			continue;
		}
		auto next = nextCord(snake.cords_.front(), snake.dir_);
		auto pred = [=] (auto &&s) {
			auto &b = s.cords_;
			return std::find(b.cbegin(), b.cend(), next) != b.cend();
		};
		if (	(next.x < 0 && snake.dir_ == X_DEC )	||
			(next.x > sz.x && snake.dir_ == X_INC)	||
			(next.y < 0 && snake.dir_ == Y_DEC)	||
			(next.y > sz.y && snake.dir_ == Y_INC)	||
			std::find_if(snakes_.cbegin(), snakes_.cend(), pred) != snakes_.cend())
		{
			killers_.emplace_back(&snake);
		} else {
			auto rab_it = std::find(rabbits_.begin(), rabbits_.end(), next);
			if (rab_it != rabbits_.end()) {
				snake.cords_.emplace_front(next);
				view->drawSnake(snake.cords_.front(), snake.clr_);
				rabbits_.erase(rab_it);
			} else {
				snake.cords_.emplace_front(next);
				view->drawSnake(snake.cords_.front(), snake.cords_.back(), snake.clr_);
				snake.cords_.pop_back();
			}
		}
		for (auto &&killer : killers_)
			killer();
	}
}

bool operator == (Coord lhs, Coord rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
bool operator == (Rabbit lhs, Rabbit rhs) {
	return lhs.pos == rhs.pos;
}
