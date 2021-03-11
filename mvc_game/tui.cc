#include "tui.h"
#include <cstdio>
#include <csignal>
#include <termios.h>
#include <sys/ioctl.h>

namespace {

volatile winsize size_;
struct sigaction sa;
void winSizeChgHandler(int sig) {
	ioctl(1, TIOCGWINSZ, &size_);
}

}

Tui::Tui() {
	setbuf(stdout, NULL);
	clear();
	ioctl(1, TIOCGWINSZ, &size_);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = winSizeChgHandler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGWINCH, &sa, NULL);
}

Coord Tui::getSize() const {
	return Coord{size_.ws_col - 2, size_.ws_row - 2};
}

void Tui::clear() {
	std::printf("\e[2J");
}

void Tui::chgPos(int x, int y) {
	std::printf("\e[%d;%dH", y, x);
}

void Tui::chgPosRel(int x, int y) {
	char xc, yc;
	if (x < 0) {
		xc = 'D';
		x = -x;
	} else
		xc = 'C';
	if (y < 0) {
		yc = 'A';
		y = -y;
	} else
		yc = 'B';
	if (x)
		std::printf("\e[%d%c", x, xc);
	if (y)
		std::printf("\e[%d%c", y, yc);
}

void Tui::savePos() {
	std::printf("\e[s");
}

void Tui::restorePos() {
	std::printf("\e[u");
}

void Tui::draw() {
	clear();
	chgPos();
	drawHorLine(size_.ws_col);
	chgPos();
	drawVerLine(size_.ws_row);
	chgPos(size_.ws_col, 0);
	drawVerLine(size_.ws_row - 1);
	chgPos(0, size_.ws_row); 
	drawHorLine(size_.ws_col - 1);
}

void Tui::run() {
	while (std::getchar() != EOF)
		draw();
}

void Tui::drawHorLine(int len) {
	for (int i = 0; i < len; ++i)
		std::putchar('-');
}

void Tui::drawVerLine(int len) {
	for (int i = 0; i < len; ++i) {
		savePos();
		std::putchar('|');
		restorePos();
		chgPosRel(0, 1);
          }

}

void Tui::drawRab(Coord pos) {
	chgPos(pos.x + 1, pos.y + 1);
	putchar('#');
}

void Tui::drawSnake(std::list<Coord> body) {
	for (auto cord : body) {
		chgPos(cord.x + 1, cord.y + 1);
		putchar('o');
	}
}

void Tui::drawSnake(Coord head, Coord tail) {
}
