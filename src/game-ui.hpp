#ifndef GAME_UI_H
#define GAME_UI_H

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "grid-container.hpp"
#include "game-logic.hpp"

namespace GameUI {
	void init(const GameLogic::Board& board, const GameLogic::Player& startingPlayer);
	void handleGameEvent(const GameLogic::Event& event);
	void render(std::function<void(int x, int y)> onChange);

	namespace internal {
		using namespace ftxui;
		// a string "code" representing an ftxui button configuration
		using Code = std::string; // X, O, EMPTY, X_COLORED, O_COLORED
		using UIBoard = std::vector<std::vector<Code>>;
		using namespace std::string_literals;

		struct UIState {
			UIBoard uiBoard;
			std::string activePlayer;
			bool gameWon = false;
		};

		extern UIState state;

		Code cellToFTXUICell(const GameLogic::Cell& cell);
		ButtonOption getButtonOptions();
	}
}

#endif
