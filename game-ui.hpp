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
}

#endif
