#include "view.h"
#include <cstdio>
#include <sys/ioctl.h>

class Tui : public View {
//	winsize size_;
	void clear();
	void chgPos(int x = 0, int y = 0);
	void chgPosRel(int x, int y = 0);
	void savePos();
	void restorePos();
	void drawHorLine(int len);
	void drawVerLine(int len);
public:
	void draw() override;
	void run();
	Tui();
};
