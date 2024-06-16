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
		void 	make_plan(void);
		void 	make_plan2(void);
};

class Data {
	public:
		char		broken_count;
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

		Data(void) :
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
		if (c % N == 0 || 1 << c - 1 & exported) {
			return (Target(0, c, 5));
		}
	}
	for (int x=0; x<5; x++) {
		for (int y=0; y<5; y++) {
			if (x >= queues[y].size())
				continue;
			if (queues[y][x] % N == 0 || 1 << queues[y][x] - 1 & exported) {
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
				if (c % N == 0 || 1 << c - 1 & tmp_exported) {
					score++;
				}
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
		if (c % N == 0 || 1 << c - 1 & exported) {
			return (vector<Target>{Target(0, c, 5)});
		}
	}
	for (int x=0; x<5; x++) {
		for (int y=0; y<5; y++) {
			if (x >= queues[y].size())
				continue;
			if (queues[y][x] % N == 0 || 1 << queues[y][x] - 1 & exported) {
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
		unsigned int	tmp_exported;
		for (auto &t : targets) {
			tmp_exported = exported | 1 << t.con;
			score = 0;
			for (auto c : queues[t.pos]) {
				if (c % N == 0 || 1 << c - 1 & tmp_exported) {
					score++;
				}
			}
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
		t = find_target();
	}
}

void Plan::make_plan2(void) {
	vector<Target> ts = find_target2();
	while (!ts.empty()) {
		for (auto t: ts) {
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
			if (cln.pos.y == 4) {
				if (!cln.U(data))
					cln.dot(data);
			} else {
				if (!cln.R(data) && !cln.U(data))
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
					if (!cln.R(data) && !cln.Q(data) && !cln.D(data))
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
					if (!cln.R(data) && !cln.D(data) && !cln.Q(data) && !cln.L(data))
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
					if (!cln.D(data) && !cln.Q(data) && !cln.R(data))
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
					if (!cln.D(data))
						cln.dot(data);
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
			case 2:
				if (cln.pos.y == 4) {
					if (!cln.L(data))
						cln.dot(data);
				} else {
					if (!cln.D(data))
						cln.dot(data);
				}
				break;
			default:
				do_circulate(data, cln);
		}
	}
}

bool min_export(Data &data, Clane &cln) {
	if (cln.pos.y < cln.has_con / N)
		return (cln.D(data) || cln.R(data) || cln.L(data));
	else if (cln.pos.y > cln.has_con / N) 
		return (cln.U(data) || cln.R(data) || cln.L(data));
	else {
		return cln.R(data) || cln.L(data) || cln.U(data) || cln.D(data);
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4
		&& (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))) {
		if (cln.Q(data)) {
			cln.is_working = false;
		} else {
			cln.dot(data);
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
				if (!cln.U(data) && !cln.R(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if ((right.is_con < 0 && right2.is_con < 0)
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
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4
		&& (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))) {
		if (cln.Q(data)) {
			cln.is_working = false;
		} else {
			cln.dot(data);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_clane(Data &data, Clane &cln, void (*dstore)(Data &, Clane &), void (*dexport)(Data &, Clane &)){
	if (cln.is_broken)
		return;
	if (cln.is_working) {
		if (cln.has_con < 0)
			do_pick(data, cln);
		else if (cln.has_con == cln.tgt.con) {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				dexport(data, cln);
			else
				do_circulate(data, cln);
		} else {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				dexport(data, cln);
			else
				dstore(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void sim(Data &data, void (*dstore)(Data &, Clane &), void (*dexport)(Data &, Clane &)) {
	while (data.turn < 250) {
		for (auto &cln: data.clanes) {
			if (!cln.is_working) {
				if (data.plan.plan.size() > 0) {
					Target &tgt = data.plan.plan.front();
					data.wanted |= 1 << tgt.con;
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						data.plan.plan.pop_front();
					}
					//cerr << "tgt, cln: " << tgt.con << " " << cln.index << " | turn: " << data.turn << " | pos: " << cln.tgt.pos << endl;
					cln.is_working = true;
				} else {
					cln.B(data);
				}
			}
			do_clane(data, cln, dstore, dexport);
			//if (cln.actions.size() != data.turn + 1 && cln.actions[cln.actions.size() - 1] != 'B') {
				//cerr << "cln: " << cln.index << " | turn: " << data.turn << " | pos: " << cln.pos.y << " " << cln.pos.x << "|tgt: " << cln.tgt.con << endl;
			//}
		}
		data.proceed();
		if (data.remain_con == 0)
			break;
	}
}

void sims(Data &data) {
	Data best;
	int min_turn = INT_MAX;
	Data tmp;
	void (*dstore)(Data &, Clane &);
	void (*dexport)(Data &, Clane &);
	for (int i=0; i<2; i++) {
	for (int j=0; j<2; j++) {
	for (int k=0; k<2; k++) {
		tmp = data;
		if (i == 1)
			tmp.plan = tmp.plan2;
		if (j == 0)
			dstore = do_store;
		else
			dstore = do_store2;
		if (k == 0)
			dexport = do_export;
		else
			dexport = do_export2;
		sim(tmp, dstore, dexport);
		if (tmp.turn < min_turn) {
			best = tmp;
			min_turn = tmp.turn;
		}
		cerr << "turn: " << tmp.turn << endl;
	}}}
	data = best;
}

int main() {
	Data data;
	data.input();
	sims(data);
	data.output();
	return 0;
}
