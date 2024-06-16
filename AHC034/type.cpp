#include "lib.cpp"

#define N 20

int _;

typedef enum e_dir {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
} t_dir;
string dir_to_str(t_dir dir) {
	switch (dir) {
		case UP:
			return "U";
		case RIGHT:
			return "R";
		case DOWN:
			return "D";
		case LEFT:
			return "L";
	}
	return "";
}
 
class SquareData {
public:
	Point pos;
	int height;
};
class Square5 {
public:
	Point pos;
	int totalHeight;
	int remain_sq;
	Square5(void) : pos(Point(0, 0)), totalHeight(0), remain_sq(25) {};
};
class Map {
public:
	vector<vector<SquareData>> map;
	vector<vector<Square5>> map5;
	SquareData& getPoint(Point p) {
		return map[p.y][p.x];
	}
	Square5& getPoint5(Point p) {
		return map5[p.y / 5][p.x / 5];
	}
	Map(void);
};
Map::Map(void) : map(vector<vector<SquareData>>(N, vector<SquareData>(N))),
	map5(vector<vector<Square5>>(4, vector<Square5>(4))) {};

class Car {
public:
	Point pos;
	int gravel;
	Car(void) : pos(Point(0, 0)), gravel(0) {};
};

class Data {
public:
	int cost;
	int remain_square;
	Car car;
	Map map;
	string ans;
	deque<Square5*> plan5;
	Data(void);
	bool move(t_dir dir);
	bool load(int val);
	bool unload(int val);
	bool is_finished(void);
};
Data::Data(void): cost(0), remain_square(N * N), car(Car()), map(Map()), ans("") {
	cin >> _;
	auto& m = map.map;
	auto& m5 = map.map5;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			m[i][j].pos = Point(j, i);
			m5[i / 5][j / 5].pos = Point(j / 5 * 5, i / 5 * 5);
			cin >> m[i][j].height;
			m5[i / 5][j / 5].totalHeight += m[i][j].height;
			if (m[i][j].height == 0) {
				--remain_square;
				--m5[i / 5][j / 5].remain_sq;
			}
		}
	}
}
bool Data::move(t_dir dir) {
	Point next = car.pos;
	switch (dir) {
		case UP:
			next.y--;
			break;
		case RIGHT:
			next.x++;
			break;
		case DOWN:
			next.y++;
			break;
		case LEFT:
			next.x--;
			break;
	}
	if (next.x < 0 || next.x >= N || next.y < 0 || next.y >= N) {
		return false;
	}
	cost += car.gravel + 100;
	car.pos = next;
	ans += dir_to_str(dir) + '\n';
	return true;
}
bool Data::load(int val) {
	map.getPoint(car.pos).height -= val;
	car.gravel += val;
	cost += val;
	ans += "+" + to_string(val) + '\n';
	if (map.getPoint(car.pos).height == 0) {
		--remain_square;
		map.getPoint5(car.pos).remain_sq--;
	}
	return true;
}
bool Data::unload(int val) {
	val = abs(val);
	if (car.gravel < val || val == 0) {
		return false;
	}
	map.getPoint(car.pos).height += val;
	car.gravel -= val;
	cost += val;
	ans += "-" + to_string(val) + '\n';
	if (map.getPoint(car.pos).height ==0) {
		--remain_square;
		--map.getPoint5(car.pos).remain_sq;
	}
	return true;
}
bool Data::is_finished(void) {
	return remain_square == 0;
}
