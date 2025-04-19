#include "game-logic.hpp"
#include "game-ui.hpp"

int main() {
	GameUI::init(GameLogic::getBoard(), GameLogic::getActivePlayer());
	GameUI::render([](int x, int y) {
		GameLogic::onChange(x, y, GameUI::handleGameEvent);
		});

	return EXIT_SUCCESS;
}
