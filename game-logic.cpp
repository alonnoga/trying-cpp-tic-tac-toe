#include "game-logic.hpp"

namespace GameLogic {

	namespace internal {
		auto board = Board{
			{ EMPTY, EMPTY, EMPTY },
			{ EMPTY, EMPTY, EMPTY },
			{ EMPTY, EMPTY, EMPTY },
		};
		auto activePlayer = Player{ X };

		std::optional<WinEvent> checkForWinner(const Board& board) {
			struct Direction {
				int dx;
				int dy;
			};

			auto checkSequence{ [](const Board& board, Position pos, Direction dir) -> std::optional<WinEvent> {
				auto [x, y] = pos;
				auto [dx, dy] = dir;
				auto player = board[y][x];

				if (player == EMPTY) return std::nullopt;

				auto sequence = std::vector<Position>{
					{ x, y },
					{ x + dx, y + dy },
					{ x + dx * 2, y + dy * 2 }
				};


				for (auto& [x, y] : sequence) {
					if (board[y][x] != player) return std::nullopt;
				}

				return WinEvent{.winner = player, .sequence = std::move(sequence)};
				} };

			std::vector<std::pair<Position, Direction>> sequencesToCheck{
				{ { 0, 0 }, { 1, 0 } }, // first row
				{ { 0, 1 }, { 1, 0 } }, // second row
				{ { 0, 2 }, { 1, 0 } }, // third row
				{ { 0, 0 }, { 0, 1 } }, // first column
				{ { 1, 0 }, { 0, 1 } }, // second column
				{ { 2, 0 }, { 0, 1 } }, // third column
				{ { 0, 0 }, { 1, 1 } }, // first diag
				{ { 0, 2 }, { 1, -1 } } // second diag
			};

			for (const auto& seq : sequencesToCheck) {
				auto [pos, dir] = seq;
				auto winner = checkSequence(board, pos, dir);
				if (winner) return winner;
			}

			return std::nullopt;
		}
	}

	void onChange(int x, int y, std::function<void(Event)> onEvent) {
		using namespace internal;

		if (board[y][x] != " ") {
			return;
		}
		board[y][x] = internal::activePlayer;
		onEvent(PutEvent{ .x = x, .y = y, .piece = activePlayer });
		auto winnerOpt = checkForWinner(board);
		if (winnerOpt) {
			onEvent(*winnerOpt);
			return;
		}
		activePlayer = activePlayer == X ? O : X;
		onEvent(TurnChangedEvent{ .player = activePlayer });

		return;
	}


	const Board& getBoard() {
		using namespace internal;

		return board;
	}

	const Player& getActivePlayer() {
		using namespace internal;

		return activePlayer;
	}
};
