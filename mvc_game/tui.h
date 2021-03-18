#include "view.h"
#include <termios.h>
#include <list>

class Tui : public View {
	std::list<KeyFn>  callkey_;
	TimerFn calltimer_;
	int period_;
	termios term;
	bool loop_flag_ = true;

	void clear();
	void chgPos(int x = 0, int y = 0);
	void chgPosRel(int x, int y = 0);
	void savePos();
	void restorePos();
	void drawHorLine(int len);
	void drawVerLine(int len);
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
	Tui();
	~Tui();
};
