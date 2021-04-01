#include "game.h"
#include "view.h"
#include <cctype>
#include <random>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <iostream>

namespace {
constexpr int INIT_RABBIT_N = 80;
constexpr int INIT_SNAKES_N = 5;
constexpr int INIT_SNAKES_L = 3;
constexpr int INIT_PERIOD = 100;

std::default_random_engine rand_gen{static_cast<unsigned>(time(0))};



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
}

Game::Game(View *v) : view_(v) {
	view_->subscribeTimer(std::bind(&Game::tick, this), INIT_PERIOD);
	view_->subscribeKey([=](int key){
			if (std::toupper(key) == 'Q')
				view_->stop();
			});
}

Snake &Game::makeSnake() {
	std::list<Coord> body;
	body.push_back(getFreePos());
//	auto dir = static_cast<Direction>(std::uniform_int_distribution<int>{0, static_cast<int>(Direction::DIRS_N)}(rand_gen));
	auto dir = X_INC;
	for (int i = 0; i < INIT_SNAKES_L; i++)
		body.push_back(body.back());//nextCord(body.back(), dir));
	snakes_.push_back(Snake(std::move(body), dir));
	return snakes_.back();
}

Snake::Snake(std::list<Coord> &&body, Direction dir) : cords_(body), dir_(dir) {
}

Rabbit::Rabbit(Coord p) : pos(p) {
}

bool Game::checkIfFree(Coord cord) const {
	auto rab_pred = [&](auto rab){ return rab.pos == cord;};
	auto snake_pred = [&](auto snake){
		auto body = snake.getCords();
		return std::any_of(body.cbegin(), body.cend(), 
				[&](auto pos){return pos == cord; }); };
	return std::any_of(rabbits_.cbegin(), rabbits_.cend(), rab_pred) || std::any_of(snakes_.cbegin(), snakes_.cend(), snake_pred);
}

Coord Game::getFreePos() const {
	Coord sz = view_->getSize();
	Coord cord;
	auto x_distr = std::uniform_int_distribution<int>{0, sz.x};
	auto y_distr = std::uniform_int_distribution<int>{0, sz.y};
	do {
		cord.x = x_distr(rand_gen);
		cord.y = y_distr(rand_gen);
	} while (checkIfFree(cord));
	return cord;
}
#if 0
Coord Game::getFreePos(Coord prev_pos) const { 
	Coord cord;
	auto dir_distr = std::uniform_int_distribution<int>{0, static_cast<int>(Direction::DIRS_N)};
	do {
		cord = nextCord(prev_pos, static_cast<Direction>(dir_distr(rand_gen)));
	} while (checkIfFree(cord));
	return cord;
}
#endif
void Game::tick() {
	auto sz = view_->getSize();
	while (rabbits_.size() < INIT_RABBIT_N)
		rabbits_.emplace_back(getFreePos());
	for (auto r : rabbits_) {
		view_->drawRab(r.pos);
	}
	for (auto&& snake : snakes_) {
		auto next = nextCord(snake.cords_.front(), snake.dir_);
		auto pred = [=] (auto &&s) {
			auto &b = s.cords_;
			return std::find(b.cbegin(), b.cend(), next) != b.cend();
		};
		if (next.x < 0 || next.x > sz.x || next.y < 0 || next.y > sz.y
			|| std::find_if(snakes_.cbegin(), snakes_.cend(), pred) != snakes_.cend()) {
			for (auto pos : snake.cords_)
				view_->drawEmpty(pos);
			snake.cords_.clear();
		} else {
			auto rab_it = std::find(rabbits_.begin(), rabbits_.end(), next);
			if (rab_it != rabbits_.end()) {
				snake.cords_.emplace_front(next);
				view_->drawSnake(snake.cords_.front());
				rabbits_.erase(rab_it);
			} else {
				snake.cords_.emplace_front(next);
				view_->drawSnake(snake.cords_.front(), snake.cords_.back());
				snake.cords_.pop_back();
			}
		}
	}
}

bool operator == (Coord lhs, Coord rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
bool operator == (Rabbit lhs, Rabbit rhs) {
	return lhs.pos == rhs.pos;
}
