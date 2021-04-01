#include "view.h"

class Gui : public View {
public:
	void draw() override;
	void stop() override;
	void runloop() override;
	void drawEmpty(Coord pos) override;
	void drawRab(Coord pos) override;
	void drawSnake(Coord head) override;
	void drawSnake(Coord head, Coord tail) override;
	void drawSnake(std::list<Coord> body) override;
	Coord getSize() const override;
	void subscribeKey(std::function<void(int)> callkey) override;
	void subscribeTimer(std::function<void()> calltimer, int period) override;
	Gui();
};
