#include <bits/stdc++.h>
#define DOWN 0
#define RIGHT 1
#define UP 2
#define LEFT 3

using namespace std;
typedef long long ll;
typedef vector<int>	t_day_req;
typedef struct {
	int W, D, N;
	vector<t_day_req> req;
} t_data;
typedef struct {
	int x;
	int y;
} t_coord;
typedef struct {
	bool top;
	bool left;
} t_sep;
typedef struct {
	t_coord start;
	t_coord end;
	int vec;
} t_square;
typedef vector<t_square> t_sq_arrangement;
typedef vector<vector<t_sep>> t_sep_arrangement;
class DayPlan {
	public:
		t_sq_arrangement square;
		t_sep_arrangement separater;
		DayPlan(t_data &data) {
			square = t_sq_arrangement(data.N);
			separater = t_sep_arrangement(data.W + 1, vector<t_sep>(data.W + 1));
		}
		void set_sep();
};
void DayPlan::set_sep() {
	for (int i=0; i<separater.size(); i++) {
		separater[i][0].top = true;
		separater[i][0].left = true;
		separater[i][separater[i].size() - 1].top = true;
		separater[i][separater[i].size() - 1].left = true;
	}
	for (int i=0; i<square.size(); i++) {
		for (int x=square[i].start.x; x<square[i].end.x; x++) {
			separater[x][square[i].start.y].top = true;
			separater[x][square[i].end.y + 1].top = true;
		}
		for (int y=square[i].start.y; y<square[i].end.y; y++) {
			separater[square[i].start.x][y].left = true;
			separater[square[i].end.x + 1][y].left = true;
		}
	}
}
typedef vector<DayPlan> t_plan;
void print_plan(t_plan &plan) {
	for (auto &day_plan : plan) {
		for (auto &sq: day_plan.square) {
			cout << sq.start.y << " " << sq.start.x << " " << sq.end.y << " " << sq.end.x << endl;
		}
	}
}

bool occupied(t_square &sq, t_sq_arrangement &sq_arr, int index)
{
	for (int i=index; i<sq_arr.size(); i++) {
		if (sq.start.x < sq_arr[i].end.x && sq.end.x > sq_arr[i].start.x &&
			sq.start.y < sq_arr[i].end.y && sq.end.y > sq_arr[i].start.y) {
			return true;
		}
	}
	return false;
}

t_square find_space(t_data &data, t_sq_arrangement &sq_arr, int index, int req)
{
	int unit = data.W / 5;
	t_square sq;
	
	if (index == data.W - 1) {
		sq.start.x = 0;
		sq.start.y = 0;
	} else {
		if (sq_arr[index + 1].vec <= RIGHT) {
			sq.start.x = sq_arr[index + 1].start.x;
			sq.start.y = sq_arr[index + 1].end.y;
		} else {
			sq.end.x = sq_arr[index + 1].start.x;
			sq.start.y = sq_arr[index + 1].end.y;
		}
	}
	cerr << "no space found" << endl;
	exit(1);
	return sq;
}

DayPlan make_day_plan(t_data &data, DayPlan &prev, t_day_req &req) {
	cerr << "make_day_plan" << endl;
	DayPlan plan = DayPlan(data);
	for (int i=data.N-1; i>=0; i--) {
		cerr << "req[" << i << "]=" << req[i] << endl;
		plan.square[i] = find_space(data, plan.square, i, req[i]);
	}
	return plan;
}

int main() {
	// input
	t_data data;
	cin >> data.W >> data.D >> data.N;
	data.req = vector<t_day_req>(data.D, t_day_req(data.N));
	for (int i=0; i<data.D; i++) {
		for (int j=0; j<data.N; j++) {
			cin >> data.req[i][j];
		}
	}
	cerr << "input done" << endl;

	// solve
	t_plan plan = t_plan(data.D, DayPlan(data));
	plan[0] = make_day_plan(data, plan[0], data.req[0]);
	for (int i=1; i<data.D; i++) {
		plan[i] = make_day_plan(data, plan[i-1], data.req[i]);
	}
	print_plan(plan);
}
