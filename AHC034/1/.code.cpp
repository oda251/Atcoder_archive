#include <bits/stdc++.h>
//#include <vector>
//#include <iostream>
//#include <string>
//#include <queue>
//#include <deque>
//#include <unordered_map>
//#include <random>

using namespace std;
typedef long long ll;
class Point {
	public:
		int x;
		int y;
		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point &src) : x(src.x), y(src.y) {}
		void move(int a, int b) { x+=a; y+=b; }
		Point &operator=(const Point &src) {
			x = src.x;
			y = src.y;
			return *this;
		}
		Point operator+(const Point &src) const {
			return Point(x + src.x, y + src.y);
		}
		Point operator-(const Point &src) const {
			return Point(x - src.x, y - src.y);
		}
		Point operator*(const Point &src) const {
			return Point(x * src.x, y * src.y);
		}
		Point operator/(const Point &src) const {
			return Point(x / src.x, y / src.y);
		}
		Point &operator++(void) {
			x++;
			y++;
			return *this;
		}
		Point operator++(int) {
			Point tmp(*this);
			operator++();
			return tmp;
		}
		Point &operator--(void) {
			x--;
			y--;
			return *this;
		}
		Point operator--(int) {
			Point tmp(*this);
			operator--();
			return tmp;
		}
		bool operator==(const Point &src) const {
			return x == src.x && y == src.y;
		}
		bool operator!=(const Point &src) const {
			return x != src.x || y != src.y;
		}
		bool operator>(const Point &src) const {
			return x > src.x && y > src.y;
		}
		bool operator<(const Point &src) const {
			return x < src.x && y < src.y;
		}
		bool operator>=(const Point &src) const {
			return x >= src.x && y >= src.y;
		}
		bool operator<=(const Point &src) const {
			return x <= src.x && y <= src.y;
		}
};
#define HERE cerr << "HERE" << endl
#define HOGE cerr << "HOGE" << endl
#define FUGA cerr << "FUGA" << endl
#define DEBUG(x) cerr << #x << ": " << x << endl
#define EXIT cerr << "EXIT" << endl; exit(0);
#define INF LLONG_MAX
#define range(index, a, b) for(ll index=a; i<b; i++)
#define rrange(index, a, b) for(ll index=a; i>=b; i--)
#define all(a) (a).begin(), (a).end()

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
class Map {
public:
	vector<vector<SquareData>> map;
	SquareData& getPoint(Point p) {
		return map[p.y][p.x];
	}
	Map(void);
};
Map::Map(void) : map(vector<vector<SquareData>>(N, vector<SquareData>(N))) {};

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
	Data(void);
	bool move(t_dir dir);
	bool load(int val);
	bool unload(int val);
	bool is_finished(void);
};
Data::Data(void): cost(0), remain_square(N * N), car(Car()), map(Map()), ans("") {
	cin >> _;
	auto& m = map.map;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			m[i][j].pos = Point(j, i);
			cin >> m[i][j].height;
			if (m[i][j].height == 0) {
				--remain_square;
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
	}
	return true;
}
bool Data::unload(int val) {
	val = abs(val);
	if (car.gravel < val) {
		return false;
	}
	map.getPoint(car.pos).height += val;
	car.gravel -= val;
	cost += val;
	ans += "-" + to_string(val) + '\n';
	if (map.getPoint(car.pos).height ==0) {
		--remain_square;
	}
	return true;
}
bool Data::is_finished(void) {
	return remain_square == 0;
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

int main() {
	clock_t start = clock();
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Data data;
	auto& car = data.car;
	auto& map = data.map;
	bool reversed = false;
	int turn;
	for (turn=0; ; turn++) {
		auto h = map.getPoint(car.pos).height;
		if (h > 0) {
			data.load(h);
		} else if (h < 0) {
			if (!data.unload(h) && car.gravel > 0) {
				data.unload(car.gravel);
			}
		}
		if (reversed == false) {
			if (car.pos.y % 2 == 0) {
				if (!data.move(RIGHT) && !data.move(DOWN)) {
					cerr << "error" << endl;
					exit(1);
				}
			} else {
				if (!data.move(LEFT) && !data.move(DOWN)) {
					reversed = true;
				}
			}
		} else {
			if (car.pos.y % 2 == 0) {
				if (!data.move(LEFT) && !data.move(UP)) {
					reversed = false;
				}
			} else {
				if (!data.move(RIGHT) && !data.move(UP)) {
					cerr << "error" << endl;
					exit(1);
				}
			}
		}
		if (data.is_finished())
			break ;
	}
	cerr << turn << endl;
	cout << data.ans << flush;
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
