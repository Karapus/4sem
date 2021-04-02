#include "tui.h"
#include "gui.h"
#include "game.h"
#include "humanc.h"
#include "botc.h"
#include <cstring>
#include <memory>

int main(int argc, char **argv) {
	std::unique_ptr<View> ui{View::get(argc > 1 ? argv[1] : "tui")};
	ui->draw();
	Game game{ui.get()};
	HumanC huc{game, ui.get()};
	BotC{game, ui.get()};
	ui->runloop();
}
