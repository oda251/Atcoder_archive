#include "type.hpp"
// start writing code

class Solver {
 private:
	static bool compare(InGame &a, InGame &b) {
		if (a.score < 0) a.calcScore();
		if (b.score < 0) b.calcScore();
		return a.score < b.score;
	}
 public:
	InGame init;
  vector<vector<InGame>> logs; // [turn][rand]
	int minScore = INT_MAX;
	InGame* bestGame;
	Solver(Data &data);
};
Solver::Solver(Data &data)
	: init(data),
		logs(1024, vector<InGame>()),
		bestGame(nullptr) {
	logs[0].push_back(init);
}

void solve_game(Data &data) {
	Solver solver(data);
	InGame init(data);
	int turn = 0;
	while (true) {
		for (auto &prev : solver.logs[turn]) {
			InGame cur(prev);
			auto getNearest = [&](){
				vector<Point> ans;
				unordered_set<Point, Point::Hash> visited;
				queue<Point> que;
				que.push(cur.arm.position);
				visited.insert(cur.arm.position);
				while (!que.empty()) {
					Point p = que.front();
					que.pop();
					if (cur.arm.takoyakiCount == 0) {
						if (cur.remainTakoyaki.count(p) > 0) {
							ans.push_back(p);
						}
					} else if (cur.arm.takoyakiCount == cur.arm.leafSize) {
						if (cur.remainDestination.count(p) > 0) {
							ans.push_back(p);
						}
					} else {
						if (cur.remainTakoyaki.count(p) || cur.remainDestination.count(p) > 0) {
							ans.push_back(p);
						}
					}
					if (ans.size() >= 3) {
						break;
					}
					for (char i = 0; i < 4; i++) {
						Point np = p.moved(static_cast<Point::Direction>(i));
						if (visited.count(np) == 0) {
							visited.insert(np);
							que.push(np);
						}
					}
				}
				return ans;
			};
			vector<Point> nearest = getNearest();
			vector<int> dists;
			for (auto p : nearest) {
				dists.push_back(cur.arm.position.getManhattanDistance(p));
			}
			for (char i = 0; i < 5; i++) {
				// 1. 進む
				if (cur.arm.canMove(static_cast<Direction>(i))) continue;
				Point moved = cur.arm.position.moved(static_cast<Point::Direction>(i));
				int dist = cur.arm.position.getManhattanDistance(moved);
				bool canMove = false;
				for (int j=0; j<nearest.size(); j++) {
					if (dist < cur.arm.maxRadius || dists[j] > dist) {
						canMove = true;
						break;
					}
				}
				if (!canMove) continue;
				InGame next(cur);
				next.arm.move(static_cast<Direction>(i));
				// 2. 関節を回転
				auto rotateLeaf = [&](InGame &next, Node &leaf){
					for (int j=0; j<3; j++) {
						switch (j) {
							case 0:
								leaf.rotate(LEFT);
								break;
							case 1:
								leaf.rotate(RIGHT);
								break;
							default:
								break;
						}
						if (leaf.hasTakoyaki && next.remainDestination.count(leaf.position) > 0) {
							next.remainDestination.erase(leaf.position);
							leaf.hasTakoyaki = false;
							next.arm.takoyakiCount--;
							return 1;
						} else if (!leaf.hasTakoyaki && next.remainTakoyaki.count(leaf.position) > 0) {
							next.remainTakoyaki.erase(leaf.position);
							leaf.hasTakoyaki = true;
							next.arm.takoyakiCount++;
							return 1;
						}
						return 0;
					}
				};
				auto rotateJoint = [&](InGame &next, Node &joint){
					int highScore = -1;
					InGame highGame(next.data);
					for (int j=0; j<3; j++) {
						InGame newNext(next);
						switch (j) {
							case 0:
								joint.rotate(LEFT);
								newNext.commandLogs
								break;
							case 1:
								joint.rotate(RIGHT);
								break;
							default:
								break;
						}
						int score = 0;
						for (auto &leaf : next.arm.leafNodes) {
							score += rotateLeaf(newNext, *leaf);
						}
						if (score > highScore) {
							highScore = score;
							highGame = newNext;
						}
					}
					next = highGame;
				};
				for (auto &joint : next.arm.jointNodes) {
					rotateJoint(next, *joint);
				}
				// 3. ログに追加
				solver.logs[turn + 1].push_back(next);
				if (next.remainTakoyaki.empty() && next.remainDestination.empty()) {
					if (solver.minScore > next.score) {
						solver.minScore = next.score;
						solver.bestGame = &solver.logs[turn + 1].back();
						return ;
					}
				}
				sort(solver.logs[turn + 1].begin(), solver.logs[turn + 1].end(), [&](InGame &a, InGame &b){
					return a.score < b.score;
				});
			}
		}
	}
}

int main(int argc, char **argv) {
	Data data;

	cerr_time();
	return 0;
}
