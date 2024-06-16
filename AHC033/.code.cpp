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

#define N 5
#define MAX_TURN 10000
class Clane;
class SquareState;
class Plan;
class Data;
typedef vector<vector<SquareState>> Map;
typedef vector<Clane> Clanes;
typedef vector<queue<int>> ConQueues;
typedef unordered_map<int, char> SquareLog;

class Target {
	public:
		int dist;
		int con;
		// -1: none, 0-4: queue, 5: board
		int pos;
		Target() : dist(-1), pos(-1), con(-1) {}
		Target(int d, int c, int p) : dist(d), con(c), pos(p) {}
		bool operator==(const Target &other) const {
			return (dist == other.dist && con == other.con && pos == other.pos);
		}
		bool operator!=(const Target &other) const {
			return !(*this == other);
		}
};

class Plan {
	public:
		vector<vector<int>>	queues;
		vector<int>			board;
		deque<Target>		plan;
		unsigned int		exported;
		Plan(void) : queues(5, vector<int>()), exported(0) {
		}
		Target	find_target(void);
		vector<Target>	find_target2(void);
		void	export_tgt(Target &t);
		void 	make_plan(void);
		void 	make_plan2(void);
};

class TargetLog {
	public:
		int		turn;
		Target	tgt;
		int		cln_i;
		TargetLog& operator=(const TargetLog& other) {
			if (this != &other) {
				turn = other.turn;
				tgt = other.tgt;
				cln_i = other.cln_i;
			}
			return *this;
		}
		bool operator==(const TargetLog &other) const {
			return (turn == other.turn && tgt == other.tgt && cln_i == other.cln_i);
		}
};

class Data {
	public:
		int			put_count;
		int			broken_count;
		int			storage;
		int			wanted;
		char		remain_con;
		Map			map;
		Plan		plan;
		Plan		plan2;
		int			turn;
		Clanes		clanes;
		ConQueues	queues;
		int			exported;
		int			exported_count;
		vector<TargetLog> passed_log;
		void (*dstore)(Data &, Clane &);
		void (*dexport)(Data &, Clane &);
		void (*dpick)(Data &, Clane &);
		char		plan_flag;
		int			exported_turn[25];

		Data(void) :
			put_count(0),
			broken_count(0),
			storage(0),
			wanted(0),
			remain_con(25),
			turn(0),
			map(5, vector<SquareState>(5)),
			clanes(5),
			queues(5, queue<int>()),
			exported(0),
			exported_count(0)
			{
			}
		void	proceed(void);
		void	input(void);
		void	output(void);
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
		Target	tgt;
		bool	is_working;
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
	data.storage &= ~(1 << (pos.y * N + pos.x));
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
	data.storage |= 1 << (pos.y * N + pos.x);
	actions.push_back('Q');
	data.put_count++;
	is_working = false;
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
		data.broken_count++;
		data.map[pos.y][pos.x].clane_out();
		actions.push_back('B');
		return true;
	}
}

/* Plan member func */
Target Plan::find_target()  {
	vector<Target> targets;
	for (int c: board) {
		if (c % N == 0 || 1 << (c - 1) & exported) {
			return (Target(0, c, 5));
		}
	}
	for (int x=0; x<5; x++) {
		for (int y=0; y<5; y++) {
			if (x >= queues[y].size())
				continue;
			if (queues[y][x] % N == 0 || 1 << (queues[y][x] - 1) & exported) {
				targets.push_back({Target(x, queues[y][x], y)});
			}
		}
		if (targets.size() > 0) {
			break;
		}
	}
	if (targets.size() > 1) {
		Target			final_t;
		int				score;
		int				max_score = 0;
		unsigned int	tmp_exported;
		for (auto &t : targets) {
			tmp_exported = exported | 1 << t.con;
			score = 0;
			for (auto c : queues[t.pos]) {
				if (c % N == 0 || 1 << (c - 1) & tmp_exported) {
					score++;
				}
				tmp_exported |= 1 << c;
			}
			if (score > max_score) {
				max_score = score;
				final_t = t;
			}
		}
		return (final_t);
	} else if (targets.size() == 1) {
		return (targets[0]);
	} else {
		return (Target());
	}
}

vector<Target> Plan::find_target2()  {
	vector<Target> targets;
	vector<Target> res;
	for (int c: board) {
		if (c % N == 0 || 1 << (c - 1) & exported) {
			return (vector<Target>{Target(0, c, 5)});
		}
	}
	for (int x=0; x<5; x++) {
		for (int y=0; y<5; y++) {
			if (x >= queues[y].size())
				continue;
			if (queues[y][x] % N == 0 || 1 << (queues[y][x] - 1) & exported) {
				targets.push_back({Target(x, queues[y][x], y)});
			}
		}
		if (targets.size() > 0) {
			break;
		}
	}
	if (targets.size() > 1) {
		int				score;
		int				max_score = 0;
		//unsigned int	tmp_exported;
		for (auto &t : targets) {
			//tmp_exported = exported | 1 << t.con;
			score = 0;
			//for (auto c : queues[t.pos]) {
			//	if (c % N == 0 || 1 << (c - 1) & tmp_exported) {
			//		score++;
			//	}
			//}
			if (score > max_score) {
				max_score = score;
				res = {t};
			} else if (score == max_score) {
				res.push_back(t);
			}
		}
		return (res);
	} else {
		return (targets);
	}
}

void Plan::make_plan(void) {
	Target t = find_target();
	while (t.con >= 0) {
		//DEBUG(t.con);
		//cerr << "--- con, pos, disc ---" << t.con << " " << t.pos << " " << t.dist << endl;
		//cerr << "--- board ---" << endl;
		//for (auto &c : board) {
		//	cerr << c << " ";
		//}
		//cerr << endl;
		//cerr << "---- queues -----" << endl;
		//for (auto &q : queues) {
		//	for (auto &c : q) {
		//		cerr << c << " ";
		//	}
		//	cerr << endl;
		//}
		export_tgt(t);
		t = find_target();
	}
}

void Plan::export_tgt(Target &t) {
	plan.push_back(t);
	exported |= 1 << t.con;
	if (t.pos == 5) {
		board.erase(remove(board.begin(), board.end(), t.con), board.end());
	} else if (t.dist > 0) {
		board.insert(board.end(), queues[t.pos].begin(), queues[t.pos].begin() + t.dist);
		queues[t.pos].erase(queues[t.pos].begin(), queues[t.pos].begin() + t.dist + 1);
	} else {
		queues[t.pos].erase(queues[t.pos].begin());
	}
}

void Plan::make_plan2(void) {
	vector<Target> ts = find_target2();
	while (!ts.empty()) {
		for (auto t: ts)
			export_tgt(t);
		ts = find_target2();
	}
}

/* Data member func */
void Data::input(void) {
	int tmp;
	cin >> tmp;
	clanes[0].is_large = true;
	for (int i = 0; i < N; i++) {
		clanes[i].pos.y = i;
		map[i][0].is_clane = &clanes[i];
		clanes[i].index = i;
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			queues[i].push(tmp);
			plan.queues[i].push_back(tmp);
		}
	}
	plan2 = plan;
	plan.make_plan();
	plan2.make_plan2();
	for (int i = 0; i < N; i++) {
		tmp = queues[i].front();
		queues[i].pop();
		map[i][0].is_con = tmp;
	}
}
void Data::output(void) {
	for (auto &c : clanes) {
		cout << c.actions << endl;
	}
	cerr << turn << endl;
}
void Data::proceed(void) {
	for (int i=0; i<N; i++) {
		auto &left = map[i][0];
		auto &right = map[i][4];
		if (right.is_con >= 0) {
			remain_con--;
			exported_turn[right.is_con] = turn;
			exported |= 1 << right.is_con;
			exported_count++;
			wanted &= ~(1 << right.is_con);
			right.is_con = -1;
		}
		if (left.is_con < 0 && !(left.is_clane && left.is_clane->has_con >= 0)) {
			if (!queues[i].empty()) {
				left.is_con = queues[i].front();
				queues[i].pop();
			}
		}
	}
	turn++;
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

void do_circulate(Data &data, Clane &cln,
		function<void(Data &, Clane &)> else_f = [](Data &data, Clane &cln) {
			if (cln.pos.x == 2) {
				switch (cln.pos.y) {
					case 1:
						if (!cln.R(data) && !cln.U(data) && !cln.D(data))
							cln.dot(data);
						break;
					case 2:
						if (!cln.R(data) && !cln.D(data) && !cln.L(data))
							cln.dot(data);
						break;
					case 3:
						if (!cln.R(data) && !cln.D(data))
							cln.dot(data);
						break;
				}
			} else {
				switch (cln.pos.y) {
					case 1:
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 2:
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 3:
						if (!cln.R(data) && !cln.D(data) && !cln.U(data))
							cln.dot(data);
						break;
				}
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
			//if (!cln.U(data) && !cln.R(data)) {
			if (!cln.R(data) && !cln.U(data)) {
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

void do_store(Data &data, Clane &cln) {
	int leftmask = (1 << 7) | (1 << 12) | (1 << 17);
	int rightmask = (1 << 8) | (1 << 13) | (1 << 18);
	if (cln.pos.x == 1 && cln.pos.y < 4 && (data.storage & leftmask) != leftmask) {
		if (!cln.R(data)) {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x == 2) {
		if (cln.pos.y == 0) {
			if ((data.storage & leftmask) != leftmask && cln.D(data)) {
			} else {
				do_circulate(data, cln);
			}
		} else if (cln.pos.y == 4) {
			do_circulate(data, cln);
		} else {
			if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {
			} else if (cln.pos.y < 3 && data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {
			} else if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				do_circulate(data, cln);
			}
		}
	} else if (cln.pos.x == 3) {
		if (cln.pos.y == 0) {
			do_circulate(data, cln);
		} else if (cln.pos.y == 4) {
			if ((data.storage & rightmask) != rightmask && cln.U(data)) {
			} else {
				do_circulate(data, cln);
			}
		} else {
			if (cln.pos.y > 1 && data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {
			} else if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				do_circulate(data, cln);
			}
		}
	} else if (cln.pos.x == 4 && cln.pos.y > 0 && (data.storage & rightmask) != rightmask) {
		if (!cln.L(data)) {
			do_circulate(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_store2(Data &data, Clane &cln) {
	switch (cln.pos.x) {
		case 0:
			if (!cln.R(data))
				cln.dot(data);
			break;
		case 1:
			switch (cln.pos.y) {
				case 4:
					if (!cln.U(data))
						cln.dot(data);
					break;
				case 0:
					if (!cln.R(data))
						cln.dot(data);
					break;
				default:
					if ((data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 || data.map[cln.pos.y][cln.pos.x + 2].is_con < 0)
						&& cln.R(data)) {}
					else if (!cln.U(data))
						cln.dot(data);
			}
			break;
		case 2:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 3:
					if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {}
					else if (!cln.Q(data) && !cln.D(data))
						cln.dot(data);
					break;
				case 4:
					if (data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {}
					else {
						if (!cln.L(data))
							cln.dot(data);
					}
					break;
				default:
					if (data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {}
					else if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {}
					else if (!cln.Q(data) && !cln.D(data) && !cln.R(data) && !cln.L(data))
						cln.dot(data);
			}
			break;
		case 3:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 3:
					if (!cln.Q(data) && !cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 4:
					if (data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {}
					else {
						if (!cln.L(data))
							cln.dot(data);
					}
					break;
				default:
					if (data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {}
					else if (!cln.Q(data) && !cln.D(data) && !cln.R(data))
						cln.dot(data);
			}
			break;
		case 4:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data))
						cln.dot(data);
					break;
				case 4:
					if (!cln.L(data))
						cln.dot(data);
					break;
				default:
					if (data.map[cln.pos.y][cln.pos.x - 1].is_con < 0 && cln.L(data)) {}
					else {
						if (!cln.D(data))
							cln.dot(data);
					}
					break;
			}
			break;
	}
}

void do_pick(Data &data, Clane &cln) {
	if ((cln.pos.x == 0 && cln.pos.y == cln.tgt.pos)
		|| data.map[cln.pos.y][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.P(data)) {
			if ((cln.tgt.con != cln.has_con || (cln.tgt.con == cln.has_con && cln.tgt.dist != 0))
				&& (data.wanted & (1 << cln.has_con))) {
				for (auto &c: data.clanes) {
					if (c.tgt.dist == 0 && c.tgt.con == cln.has_con) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			} else if (cln.tgt.dist == 0 && cln.tgt.con != cln.has_con) {
				for (auto &c: data.clanes) {
					if (c.tgt.pos == cln.tgt.pos && c.tgt.dist > 0) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			}
		} else {
			cln.is_working = false;
			do_circulate(data, cln);
		}
	} else if (cln.pos.x > 0 && data.map[cln.pos.y][cln.pos.x - 1].is_con == cln.tgt.con) {
		if (cln.L(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x < 4 && data.map[cln.pos.y][cln.pos.x + 1].is_con == cln.tgt.con) {
		if (cln.R(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y > 0 && data.map[cln.pos.y - 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.U(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y < 4 && data.map[cln.pos.y + 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.D(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.tgt.pos == 5) {
		if (cln.pos.y > 0) {
			switch (cln.pos.x) {
				case 1:
					if (cln.pos.y <= 1) {
						if (!cln.R(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
					break;
				case 2:
					switch (cln.pos.y) {
						case 4:
							if (!cln.L(data))
								cln.dot(data);
							break;
						case 3:
							if (!cln.L(data) && !cln.D(data))
								cln.dot(data);
							break;
						default:
							if (!cln.D(data))
								cln.dot(data);
					}
					break;
				default:
					do_circulate(data, cln);
			}
		} else {
			do_circulate(data, cln);
		}
	} else {
		switch(cln.pos.x) {
			case 0:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 1:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else if (cln.pos.y == 4) {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				}
				break;
			default:
				if (cln.tgt.pos > cln.pos.y) {
					if (!cln.D(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.D(data))
						cln.dot(data);
				}
		}
	}
}

void do_pick2(Data &data, Clane &cln) {
	if ((cln.pos.x == 0 && cln.pos.y == cln.tgt.pos)
		|| data.map[cln.pos.y][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.P(data)) {
			if ((cln.tgt.con != cln.has_con || (cln.tgt.con == cln.has_con && cln.tgt.dist != 0))
				&& (data.wanted & (1 << cln.has_con))) {
				for (auto &c: data.clanes) {
					if (c.tgt.dist == 0 && c.tgt.con == cln.has_con) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			} else if (cln.tgt.dist == 0 && cln.tgt.con != cln.has_con) {
				for (auto &c: data.clanes) {
					if (c.tgt.pos == cln.tgt.pos && c.tgt.dist > 0) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			}
		} else {
			cln.is_working = false;
			do_circulate(data, cln);
		}
	} else if (cln.pos.x > 0 && data.map[cln.pos.y][cln.pos.x - 1].is_con == cln.tgt.con) {
		if (cln.L(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x < 4 && data.map[cln.pos.y][cln.pos.x + 1].is_con == cln.tgt.con) {
		if (cln.R(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y > 0 && data.map[cln.pos.y - 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.U(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y < 4 && data.map[cln.pos.y + 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.D(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.tgt.pos == 5) {
		if (cln.pos.y > 0) {
			switch (cln.pos.x) {
				case 1:
					if (cln.pos.y <= 1) {
						if (!cln.R(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
					break;
				case 2:
					switch (cln.pos.y) {
						case 4:
							if (!cln.L(data))
								cln.dot(data);
							break;
						case 3:
							if (!cln.L(data) && !cln.D(data))
								cln.dot(data);
							break;
						default:
							if (!cln.D(data))
								cln.dot(data);
					}
					break;
				default:
					do_circulate(data, cln);
			}
		} else {
			do_circulate(data, cln);
		}
	} else {
		switch(cln.pos.x) {
			case 0:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 1:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else if (cln.pos.y == 4) {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				}
				break;
			default:
				if (cln.pos.x == 2 && cln.tgt.pos > cln.pos.y) {
					if (!cln.D(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.D(data))
						cln.dot(data);
				}
		}
	}
}

bool min_export(Data &data, Clane &cln) {
	if (cln.pos.y < cln.has_con / N)
		return (cln.D(data) || cln.R(data));
	else if (cln.pos.y > cln.has_con / N) 
		return (cln.U(data) || cln.R(data));
	else {
		return cln.R(data);
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	//} else if (data.exported_count > 20) {
	//	if (!min_export(data, cln)) {
	//		do_circulate(data, cln);
	//	}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

void do_export2(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_export3(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	} else if (data.exported_count > 20) {
		if (!min_export(data, cln)) {
			do_circulate(data, cln);
		}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

void do_export4(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	//} else if (data.exported_count > 20) {
	//	if (!min_export(data, cln)) {
	//		do_circulate(data, cln);
	//	}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 2:
						if (cln.tgt.con / N < 2) {
							if (!cln.U(data) && !cln.R(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					case 2:
						if (cln.tgt.con / N < 2) {
							if (!cln.U(data) && !cln.R(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

bool wait_export(Data &data, Clane &cln) {
	switch (cln.pos.x) {
		case 0:
			cln.dot(data);
			return true;
		case 1:
			switch (cln.pos.y) {
				case 4:
					if (cln.L(data))
						return true;
					break;
				default:
					if (cln.L(data))
						return true;
					else if (cln.R(data))
						return false;
			}
			break;
		case 2:
			switch (cln.pos.y) {
				case 0:
					if (cln.D(data))
						return false;
					break;
				case 4:
					if (cln.U(data))
						return false;
					break;
				default:
					cln.dot(data);
					return true;
			}
			break;
		case 3:
			switch (cln.pos.y) {
				case 0:
					if (cln.D(data))
						return false;
					break;
				case 4:
					if (cln.U(data))
						return false;
					break;
				default:
					cln.dot(data);
					return true;
			}
			break;
		default:
			if (0 < cln.pos.y && cln.pos.y < 4) {
				if (cln.L(data))
					return false;
			}
	}
	data.dexport(data, cln);
	return false;
}

void do_clane(Data &data, Clane &cln){
	if (cln.is_broken)
		return;
	if (cln.is_working) {
		if (cln.has_con < 0)
			data.dpick(data, cln);
		else if (cln.has_con == cln.tgt.con) {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				data.dexport(data, cln);
			else {
				if (cln.pos.y == cln.tgt.con / N && cln.pos.x == 4)
					data.passed_log.push_back({data.turn, cln.tgt, cln.index});
				//do_circulate(data, cln);
				data.dexport(data, cln);
			}
		} else {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				data.dexport(data, cln);
			else
				data.dstore(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void sim(Data &data) {
	while (data.turn < 250) {
		for (auto &cln: data.clanes) {
			if (!cln.is_working) {
				label:
				if (data.plan.plan.size() > 0) {
					Target &tgt = data.plan.plan.front();
					data.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: data.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								data.plan.plan.pop_front();
								goto label;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						data.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(data);
				}
			}
			do_clane(data, cln);
			//if (cln.actions.size() != data.turn + 1 && cln.actions[cln.actions.size() - 1] != 'B') {
				//cerr << "cln: " << cln.index << " | turn: " << data.turn << " | pos: " << cln.pos.y << " " << cln.pos.x << "|tgt: " << cln.tgt.con << endl;
			//}
		}
		for (auto &cln: data.clanes) {
			if (cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(data, cln);
			}
		}
		data.proceed();
		if (data.remain_con == 0)
			break;
	}
}

bool sim_kaizen(Data &dest, Data &src, TargetLog log, int padding = 0) {
	int prev_arive_turn;
	int turn_to_wait;
	// log.cln_iがtgtをlog.tgt.conにするまで進める
	while (dest.clanes[log.cln_i].tgt != log.tgt && dest.turn < 250) {
		for (auto &cln: dest.clanes) {
			if (!cln.is_working) {
				labbel:
				if (dest.plan.plan.size() > 0) {
					Target &tgt = dest.plan.plan.front();
					dest.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: dest.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								dest.plan.plan.pop_front();
								goto labbel;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						dest.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(dest);
				}
			}
			do_clane(dest, cln);
		}
		for (auto &cln: dest.clanes) {
			if (cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(dest, cln);
			}
		}
		dest.proceed();
		if (dest.remain_con == 0)
			break;
	}
	if (dest.turn == 250)
		return false;
	// 必要な計算
	prev_arive_turn = src.exported_turn[log.tgt.con];
	turn_to_wait = src.exported_turn[log.tgt.con - 1] - log.turn + padding;
	// log.cln_i以外はそのまま、log.cln_iのみ待機を試しながら進める
	while (dest.turn < prev_arive_turn && !(dest.exported & (1 << log.tgt.con))) {
		for (auto &cln: dest.clanes) {
			if (cln.index == log.cln_i) {
				if (turn_to_wait > 0) {
					if (wait_export(dest, dest.clanes[log.cln_i])) {
						turn_to_wait--;
					}
				} else {
					do_clane(dest, dest.clanes[log.cln_i]);
				}
				continue;
			}
			if (!cln.is_working) {
				labbbel:
				if (dest.plan.plan.size() > 0) {
					Target &tgt = dest.plan.plan.front();
					dest.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: dest.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								dest.plan.plan.pop_front();
								goto labbbel;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						dest.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(dest);
				}
			}
			do_clane(dest, cln);
		}
		for (auto &cln: dest.clanes) {
			if (cln.index != log.cln_i && cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(dest, cln);
			}
		}
		dest.proceed();
		if (dest.remain_con == 0)
			break;
	}
	// srcより到着ターンが早まったら入れ替え
	if (dest.exported_turn[log.tgt.con] >= prev_arive_turn)
		return false;
	sim(dest);
	if (dest.turn < src.turn) {
		src = dest;
		return true;
	}
	return false;
}

void kaizen(Data &initData, Data &data, vector<TargetLog> logs) {
	Data tmp;
	//cerr << "--- kaizen ---" << endl;
	labebel:
	//for (auto &log: logs) {
	//	cerr << "<" << log.cln_i << "," << log.tgt.con << ">" << " ";
	//}
	//cerr << endl;
	for (auto &log: logs) {
		for (int i=0; i<3; i++) {
			tmp = initData;
			tmp.dexport = data.dexport;
			tmp.dpick = data.dpick;
			tmp.dstore = data.dstore;
			if (data.plan_flag == 1)
				tmp.plan = tmp.plan2;
			if (sim_kaizen(tmp, data, log, i)) {
				DEBUG(data.turn);
				logs = data.passed_log;
				goto labebel;
			}
		}
	}
}

void sims(Data &data) {
	Data best;
	int min_turn = INT_MAX;
	Data tmp;
	for (int i=0; i<2; i++) {
	for (int j=0; j<2; j++) {
	for (int k=0; k<4; k++) {
	for (int l=0; l<2; l++) {
		tmp = data;
		if (i == 0)
			tmp.plan_flag = 0;
		else {
			tmp.plan = tmp.plan2;
			tmp.plan_flag = 1;
		}
		if (j == 0)
			tmp.dstore = do_store;
		else
			tmp.dstore = do_store2;
		if (k == 0)
			tmp.dexport = do_export;
		else if (k == 1)
			tmp.dexport = do_export2;
		else if (k == 2)
			tmp.dexport = do_export3;
		else
			tmp.dexport = do_export4;
		if (l == 0)
			tmp.dpick = do_pick;
		else
			tmp.dpick = do_pick2;
		//cerr << "--- sim ---" << endl;
		sim(tmp);
		//cerr << "turn: " << tmp.turn << endl;
		if (tmp.turn < 250)
			kaizen(data, tmp, tmp.passed_log);
		if (tmp.turn < min_turn) {
			best = tmp;
			min_turn = tmp.turn;
		}
	}}}}
	//kaizen(data, best, best.passed_log);
	data = best;
}

int main() {
	clock_t start = clock();
	Data data;
	data.input();
	sims(data);
	data.output();
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
