#include "tui.h"
#include "gui.h"
#include "game.h"
#include <cstring>
#include <memory>

int main(int argc, char **argv) {
	std::unique_ptr<View> ui;
	if (argc == 1 || !std::strcmp(argv[1], "tui")) {
		ui = std::make_unique<Tui>();
	} else {
		ui = std::make_unique<Gui>();
	}
	ui->draw();
	Game game{ui.get()};
	ui->run();
}
