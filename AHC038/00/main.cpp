#include "type.hpp"
// start writing code

void solve_game(InGame &game) {
	while (true) {
		Direction to_move = Direction::NONE;
		vector<Direction> to_rotate(game.data.V, Direction::NONE);
		bitset<16> to_pick = 0;
		// 計画
		auto whether_to_move = [&]() {
			// 移動先を計画
			return Direction::UP;
		};
		auto whether_to_pick = [&]() {
			// 取るかどうかを計画
			return true;
		};
		// 実行
		// 更新
	}
}

int main(int argc, char **argv) {
	Data data;
	InGame game(data);

	game.output();

	cerr_time();
	return 0;
}
