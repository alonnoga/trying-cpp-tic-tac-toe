#include "game-ui.hpp"

namespace GameUI {

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

		UIState state;

		Code cellToFTXUICell(const GameLogic::Cell& cell) {
			if (cell == " ") return "EMPTY"s;
			if (cell == "X") return "X"s;
			if (cell == "O") return "O"s;
		}

		ButtonOption getButtonOptions() {
			ButtonOption option{};
			option.transform = [](const EntryState& s) {
				std::string content;
				auto borderStyle = s.focused ? borderStyled(LIGHT, Color::BlueLight) : border;
				if (s.label == "EMPTY") {
					return text("   ") | borderStyle | center;
				}
				if (s.label == "X") {
					return text(" X ") | borderStyle | center;
				}
				if (s.label == "O") {
					return text(" O ") | borderStyle | center;
				}
				if (s.label == "X_COLORED") {
					return text(" X ") | borderStyled(LIGHT, Color::Green) | center;
				}
				if (s.label == "O_COLORED") {
					return text(" O ") | borderStyled(LIGHT, Color::Green) | center;
				}
				};
			return option;
		}
	}

	void init(const GameLogic::Board& board, const GameLogic::Player& startingPlayer) {
		using namespace internal;

		state.uiBoard = UIBoard(board.size(), std::vector<Code>(board[0].size(), "EMPTY"s));
		for (size_t row = 0; row < board.size(); ++row) {
			for (size_t col = 0; col < board[row].size(); ++col) {
				state.uiBoard[row][col] = cellToFTXUICell(board[row][col]);
			}
		}

		state.activePlayer = startingPlayer;
	}

	void handleGameEvent(const GameLogic::Event& event) {
		using namespace internal;

		if (auto putEvent = std::get_if<GameLogic::PutEvent>(&event)) {
			state.uiBoard[putEvent->y][putEvent->x] = cellToFTXUICell(putEvent->piece);
			return;
		}
		if (auto turnChangedEvent = std::get_if<GameLogic::TurnChangedEvent>(&event)) {
			state.activePlayer = turnChangedEvent->player;
			return;
		}
		if (auto winEvent = std::get_if<GameLogic::WinEvent>(&event)) {
			for (auto& pos : winEvent->sequence) {
				state.uiBoard[pos.y][pos.x] = winEvent->winner == "X" ? "X_COLORED" : "O_COLORED";
				state.gameWon = true;
			}
		}
	}

	void render(std::function<void(int x, int y)> onChange) {
		using namespace internal;

		std::vector<std::vector<Component>> lines(state.uiBoard.size());

		for (size_t rowIndex = 0; rowIndex < lines.size(); ++rowIndex) {
			const auto& row = state.uiBoard[rowIndex];
			auto rowOfButtons = std::vector<Component>(row.size());
			for (size_t colIndex = 0; colIndex < rowOfButtons.size(); ++colIndex) {
				auto& code = row[colIndex];
				rowOfButtons[colIndex] = Button(&code, [colIndex, rowIndex, &onChange] { if (!state.gameWon) onChange(colIndex, rowIndex); }, getButtonOptions());
			}
			lines[rowIndex] = std::move(rowOfButtons);
		}


		auto grid = GridContainer(lines);

		auto ui = Renderer(grid, [&] {
			auto message = state.gameWon ? "Player: " + state.activePlayer + " wins!" : "Player: " + state.activePlayer + "'s turn";
			return vbox({
				text(message),
				separator(),
				vbox({ filler(), grid->Render() | center, filler()}) | flex,
				}) | border;
			});

		auto screen = ScreenInteractive::FixedSize(40, 20);
		screen.Loop(ui);
	}
}
