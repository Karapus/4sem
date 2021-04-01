#include "gui.h"

void Gui::draw() {
}

void Gui::stop() {
}

void Gui::runloop() {
}

Gui::Gui() {
}

void Gui::drawEmpty(Coord rab) {
}

void Gui::drawRab(Coord rab) {
}

void Gui::drawSnake(Coord head) {
}

void Gui::drawSnake(Coord head, Coord tail) {
}

void Gui::drawSnake(std::list<Coord> body) {
}

Coord Gui::getSize() const {
	return Coord{};
}

void Gui::subscribeKey(std::function<void(int)> callkey) {
}

void Gui::subscribeTimer(std::function<void()> calltimer, int period) {
}
