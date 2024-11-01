#include <bits/stdc++.h>
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

#define N 5
class Clane;
class SquareState;
class Data;
typedef vector<vector<SquareState>> Map;
typedef vector<Clane> Clanes;
typedef vector<queue<int>> ConQueues;
typedef unordered_map<int, char> SquareLog;

class Data {
	public:
		int			remain_con;
		Map			map;
		int			turn;
		Clanes		clanes;
		ConQueues	queues;
		int			export_log[N] = {-1};

		Data(void) :
			remain_con(25),
			turn(0),
			map(5, vector<SquareState>(5)),
			clanes(5),
			queues(5, queue<int>())
			{
			}
		void	proceed(void);
		void	input(void);
		void	output(void);
		bool	to_export(int con) {
			return export_log[con/N] == con-1 || export_log[con/N] == -1;
		}
};

class Target {
	public:
		int dist;
		int con;
		// -1: none, 0-4: queue, 5: board
		int pos;
		Target(int d, int c, int p) : dist(d), pos(p), con(c) {}
};

class Plan {
	public:
		vector<vector<int>>	queues;
		vector<int>			board;
		deque<Target>		targets;
		int					exported;
		Plan(void) : queues(5, vector<int>()), exported(0) {
		}
		int	find_target(void) {
			vector<Target> candidates;
			for (int x=0; x<5; x++) {
				for (int y=0; y<5; y++) {
					if (queues[y].size() > x)
						continue;
					if (queues[y][x] / N == 0 || 1 << queues[y][x] - 1 & exported) {
						candidates.push_back(Target(x, queues[y][x], y));
					}
				}
				if (candidates.size() > 0) {
					break;
				}
			}
			return 0;
		}
};

class SquareState {
	public:
		int			is_con;
		// if exist value is index, else -1
		Clane*		is_clane;
		SquareLog	log;
		SquareState() : is_con(-1), is_clane(NULL) {}
		int		pick_con(void);
		bool	put_con(int index);
		bool	passable(int turn, Clane &clane, char action);
		void	clane_in(Clane &clane);
		void	clane_out(void);
};

class Clane {
	public:
		int		index;
		Point	pos;
		bool 	is_broken;
		bool 	is_large;
		int		has_con;
		string	actions;
		Clane() : is_broken(false), is_large(false), has_con(-1), actions("") {}
		bool	P(Data &data);
		bool	Q(Data &data);
		bool	U(Data &data);
		bool	D(Data &data);
		bool	L(Data &data);
		bool	R(Data &data);
		void	dot(Data &data);
		bool	B(Data &data);
};

/* SquareState member func */
inline int		SquareState::pick_con(void) {
	int tmp = is_con;
	is_con = -1;
	return tmp;
}
inline bool		SquareState::put_con(int index) {
	if (is_con >= 0) {
		return false;
	} else {
		is_con = index;
		return true;
	}
}
void	SquareState::clane_in(Clane &clane) {
	is_clane = &clane;
}
void	SquareState::clane_out(void) {
	is_clane = NULL;
}
bool	SquareState::passable(int turn, Clane &clane, char action) {
	if (is_clane) {
		return false;
	} else if (!clane.is_large && is_con >= 0 && clane.has_con >= 0) {
		return false;
	}
	return true;
}

/* Clane member func */
inline bool Clane::P(Data &data) {
	if (has_con >= 0) {
		return false;
	}
	has_con = data.map[pos.y][pos.x].pick_con();
	if (has_con < 0) {
		return false;
	}
	actions.push_back('P');
	return true;
}
inline bool Clane::Q(Data &data) {
	if (has_con < 0) {
		return false;
	}
	if (!data.map[pos.y][pos.x].put_con(has_con))
		return false;
	has_con = -1;
	actions.push_back('Q');
	return true;
}
bool Clane::U(Data &data) {
	if (pos.y == 0) {
		return false;
	} else if (data.map[pos.y - 1][pos.x].passable(data.turn, *this, 'U')) {
		data.map[pos.y][pos.x].clane_out();
		pos.y--;
		data.map[pos.y][pos.x].clane_in(*this);
		actions.push_back('U');
		return true;
	}
	return false;
}
bool Clane::D(Data &data) {
	if (pos.y == N - 1) {
		return false;
	} else if (data.map[pos.y + 1][pos.x].passable(data.turn, *this, 'D')) {
		data.map[pos.y][pos.x].clane_out();
		pos.y++;
		data.map[pos.y][pos.x].clane_in(*this);
		actions.push_back('D');
		return true;
	}
	return false;
}
bool Clane::L(Data &data) {
	if (pos.x == 0) {
		return false;
	} else if (data.map[pos.y][pos.x - 1].passable(data.turn, *this, 'L')) {
		data.map[pos.y][pos.x].clane_out();
		pos.x--;
		data.map[pos.y][pos.x].clane_in(*this);
		actions.push_back('L');
		return true;
	}
	return false;
}
bool Clane::R(Data &data) {
	if (pos.x == N - 1) {
		return false;
	} else if (data.map[pos.y][pos.x + 1].passable(data.turn, *this, 'R')) {
		data.map[pos.y][pos.x].clane_out();
		pos.x++;
		data.map[pos.y][pos.x].clane_in(*this);
		actions.push_back('R');
		return true;
	}
	return false;
}
void Clane::dot(Data &data) {
	actions.push_back('.');
}
bool Clane::B(Data &data) {
	if (is_broken || has_con >= 0) {
		return false;
	} else {
		is_broken = true;
		actions.push_back('B');
		return true;
	}
}

/* Data member func */
void Data::input(void) {
	int tmp;
	cin >> tmp;
	clanes[0].is_large = true;
	for (int i = 0; i < N; i++) {
		export_log[i] = -1;
		cin >> tmp;
		map[i][0].is_con = tmp;
		clanes[i].pos.y = i;
		map[i][0].is_clane = &clanes[i];
		clanes[i].index = i;
		for (int j = 1; j < N; j++) {
			cin >> tmp;
			queues[i].push(tmp);
		}
	}
}
void Data::output(void) {
	for (auto &c : clanes) {
		cout << c.actions << endl;
	}
}
void Data::proceed(void) {
	for (int i=0; i<N; i++) {
		auto &left = map[i][0];
		auto &right = map[i][4];
		if (right.is_con >= 0) {
			remain_con--;
			right.is_con = -1;
		}
		if (left.is_con < 0) {
			if (!queues[i].empty()) {
				left.is_con = queues[i].front();
				queues[i].pop();
			}
		}
	}
	turn++;
}

void do_circulate(Data &data, Clane &cln,
		function<void(Data &, Clane &)> else_f = [](Data &data, Clane &cln) {
			if (cln.pos.x == 2) {
				if (!cln.R(data) && !cln.D(data))
					cln.dot(data);
			} else {
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
			}
		}
	) {
	// 下辺：左向レーン
	if (cln.pos.y == 4 && cln.pos.x > 1) {
		if (!cln.L(data)) {
			cln.dot(data);
		}
	// 右辺：下降レーン
	} else if (cln.pos.x == 4) {
		if (!cln.D(data)) {
			cln.dot(data);
		}
	// 左２辺：上昇レーン
	} else if (cln.pos.x <= 1 && cln.pos.y != 0) {
		if (cln.pos.x == 0) {
			if (!cln.U(data) && !cln.R(data)) {
				cln.dot(data);
			}
		} else {
			if (!cln.U(data)) {
				cln.dot(data);
			}
		}
	// 上辺：右向レーン
	} else if (cln.pos.y == 0) {
		if (!cln.R(data)) {
			cln.dot(data);
		}
	// 中央：貯蔵
	} else {
		else_f(data, cln);
	}
}

void do_pick(Data &data, Clane &cln) {
	if (cln.pos.y > 0 && data.map[cln.pos.y - 1][cln.pos.x].is_con >= 0) {
		if (!cln.U(data) && !cln.P(data)) {
			do_circulate(data, cln);
		}
	} else if (!cln.P(data)) {
		if (cln.pos.x == 1) {
			if (!cln.L(data)) {
				do_circulate(data, cln);
			}
		} else {
			do_circulate(data, cln);
		}
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (!cln.Q(data)) {
			cln.dot(data);
		}
	} else {
		// 第三引数で最適化の余地
		do_circulate(data, cln);
	}
}

void do_clane(Data &data, Clane &cln) {
	if (cln.has_con < 0) {
		do_pick(data, cln);
	} else {
		do_export(data, cln);
	}
}

void sim(Data &data) {
	while (data.turn < 10000) {
		for (auto &cln: data.clanes) {
			do_clane(data, cln);
		}
		data.proceed();
		if (data.remain_con == 0)
			break;
	}
}

int main() {
	Data data;
	data.input();
	sim(data);
	data.output();
	return 0;
}