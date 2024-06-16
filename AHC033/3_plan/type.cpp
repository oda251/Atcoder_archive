#include "lib.cpp"

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
		void 	make_plan(void);
};

class Data {
	public:
		int			storage;
		int			wanted;
		int			remain_con;
		Map			map;
		Plan		plan;
		int			turn;
		Clanes		clanes;
		ConQueues	queues;
		int			exported;

		Data(void) :
			storage(0),
			wanted(0),
			remain_con(25),
			turn(0),
			map(5, vector<SquareState>(5)),
			clanes(5),
			queues(5, queue<int>()),
			exported(0)
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

void Plan::make_plan(void) {
	Target t = find_target();
	while (t.con >= 0) {
		DEBUG(t.con);
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
	plan.make_plan();
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
}
void Data::proceed(void) {
	for (int i=0; i<N; i++) {
		auto &left = map[i][0];
		auto &right = map[i][4];
		if (right.is_con >= 0) {
			remain_con--;
			exported |= 1 << right.is_con;
			wanted &= ~(1 << right.is_con);
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
