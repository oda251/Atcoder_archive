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

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

void make_plan_5(Data &d) {
	deque<Square5*> arr = deque<Square5*>(16);
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			arr[i*4+j] = &(d.map.getPoint5(Point(j*5, i*5)));
		}
	}
	sort(arr.begin(), arr.end(), [](Square5* a, Square5* b) {
		return (*a).totalHeight > (*b).totalHeight;
	});
	int total = 0;
	d.plan5.push_back(arr[0]);
	total += arr[0]->totalHeight;
	arr.pop_front();
	while (!arr.empty()) {
		label:
		int min = 10000;
		int tgt = 0;
		for (int i=arr.size() - 1; i>=0; i--) {
			int tmp = total + arr[i]->totalHeight;
			if (tmp > 0 && tmp < min) {
				min = tmp;
				tgt = i;
			}
		}
		if (min != 10000) {
			d.plan5.push_back(arr[tgt]);
			total += arr[tgt]->totalHeight;
			arr.erase(arr.begin() + tgt);
			goto label;
		}
		if (arr.empty())
			break;
		d.plan5.push_back(arr[0]);
		total += arr[0]->totalHeight;
		arr.pop_front();
	}
}

void move_point(Data &d, Point p) {
	auto &car = d.car;
	auto &map = d.map;
	auto &plan = d.plan5;
	while (true) {
		if (car.pos == p)
			break ;
		if (map.getPoint(car.pos).height > 0) {
			d.load(map.getPoint(car.pos).height);
		} else if (map.getPoint(car.pos).height < 0) {
			if (!d.unload(map.getPoint(car.pos).height) && car.gravel > 0) {
				d.unload(car.gravel);
			}
		}
		if (car.pos.x < p.x) {
			d.move(RIGHT);
		} else if (car.pos.x > p.x) {
			d.move(LEFT);
		} else if (car.pos.y < p.y) {
			d.move(DOWN);
		} else if (car.pos.y > p.y) {
			d.move(UP);
		}
	}
	if (map.getPoint(car.pos).height > 0) {
		d.load(map.getPoint(car.pos).height);
	} else if (map.getPoint(car.pos).height < 0) {
		if (!d.unload(map.getPoint(car.pos).height) && car.gravel > 0) {
			d.unload(car.gravel);
		}
	}
}

void clean_5(Data &d, Square5 &sq) {
	auto &car = d.car;
	auto &map = d.map;
	Point pos5 = Point(car.pos.x % 5, car.pos.y % 5);
	if (pos5 == Point(0, 0)) {
	while (pos5 != Point(4, 4)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(4, 4)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		} else {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		}
		if (pos5 == Point(4, 4)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(4, 4)) {
	while (pos5 != Point(0, 0)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(0, 0)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		} else {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		}
		if (pos5 == Point(0, 0)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(0, 4)) {
	while (pos5 != Point(4, 0)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(4, 0)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		} else {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		}
		if (pos5 == Point(4, 0)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(4, 0)) {
	while (pos5 != Point(0, 4)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(0, 4)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		} else {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		}
		if (pos5 == Point(0, 4)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}}
}
Point choose_point(Data &d, Point pos5) {
	Point p1 = pos5;
	Point p2 = Point(pos5.x + 4, pos5.y);
	Point p3 = Point(pos5.x, pos5.y + 4);
	Point p4 = Point(pos5.x + 4, pos5.y + 4);
	int dist1 = abs(d.car.pos.x - p1.x) + abs(d.car.pos.y - p1.y);
	int dist2 = abs(d.car.pos.x - p2.x) + abs(d.car.pos.y - p2.y);
	int dist3 = abs(d.car.pos.x - p3.x) + abs(d.car.pos.y - p3.y);
	int dist4 = abs(d.car.pos.x - p4.x) + abs(d.car.pos.y - p4.y);
	if (dist1 <= dist2 && dist1 <= dist3 && dist1 <= dist4) {
		return p1;
	} else if (dist2 <= dist1 && dist2 <= dist3 && dist2 <= dist4) {
		return p2;
	} else if (dist3 <= dist1 && dist3 <= dist2 && dist3 <= dist4) {
		return p3;
	} else {
		return p4;
	}
	return p1;
}
void do_plan5(Data &d) {
	auto &car = d.car;
	auto &map = d.map;
	auto &plan = d.plan5;
	label:
	auto sq = plan.front();
	plan.pop_front();
	if ((*sq).remain_sq == 0) {
		if (plan.empty())
		{
			return ;
		}
		goto label;
	}
	plan.push_back(sq);
	Point nex = choose_point(d, (*sq).pos);
	move_point(d, nex);
	clean_5(d, (*sq));
}

void all_clean(Data &data, int turn) {
	auto &map = data.map;
	auto &car = data.car;
	bool reversed = false;
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
}

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
	make_plan_5(data);
	for (turn=0; ; turn++) {
		do_plan5(data);
		if (data.is_finished())
			break ;
	}
	cerr << turn << endl;
	cout << data.ans << flush;
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
