#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <string>  
#include <vector>
#include <variant>
#include <utility> // for std::pair
#include <optional>
#include <functional>


namespace GameLogic {
	constexpr std::string_view X = "X";
	constexpr std::string_view O = "O";
	constexpr std::string_view EMPTY = " ";

	using Cell = std::string_view; // one of X, Y, EMPTY
	using Player = std::string_view; // one of X, Y
	using Board = std::vector<std::vector<std::string_view>>;

	struct PutEvent {
		int x;
		int y;
		Player piece;
	};

	struct Position {
		int x;
		int y;
	};

	struct WinEvent {
		Player winner;
		std::vector<Position> sequence;
	};

	struct TurnChangedEvent {
		Player player;
	};

	using Event = std::variant<PutEvent, WinEvent, TurnChangedEvent>;

	void onChange(int x, int y, std::function<void(Event)> onEvent);
	const Board& getBoard();
	const Player& getActivePlayer();

	namespace internal {
		extern Board board;
		extern Player activePlayer;

		std::optional<WinEvent> checkForWinner(const Board& board);
	}
}

#endif