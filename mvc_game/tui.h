#include "view.h"

class Tui : public View {
	void clear();
	void chgPos(int x = 0, int y = 0);
	void chgPosRel(int x, int y = 0);
	void savePos();
	void restorePos();
	void drawHorLine(int len);
	void drawVerLine(int len);
public:
	void draw() override;
	void run() override;
	void drawRab(Coord pos) override;
	void drawSnake(Coord head, Coord tail) override;
	void drawSnake(std::list<Coord> body) override;
	Coord getSize() const override;
	Tui();
};
