#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int H, W, Q;
enum QueryType { Draw = 1, Check = 2 };
struct Point {
  int r, c;
  bool operator<(const Point &p) const {
    return r < p.r || (r == p.r && c < p.c);
  };
  bool operator==(const Point &p) const {
    return r == p.r && c == p.c;
  };
};
class Grid {
 public:
  vector<vector<char>> grid;
  Grid() {}
  Grid(int H, int W) : grid(H, vector<char>(W, 0)) {}
  void init() {
    grid = vector<vector<char>>(H, vector<char>(W, 0));
  }
  char& operator[](Point &p) {
    return grid[p.r][p.c];
  }
};
struct Query {
  QueryType type;
  Point a, b;
};
vector<Query> queries;
Grid grid;

bool is_reachable(const Query &q) {
  set<Point> seen;
  struct State {
    Point p;
    int dist_actual, dist_heuristic;
  };
  auto grater = [](const State &a, const State &b) {
    return a.dist_actual + a.dist_heuristic > b.dist_actual + b.dist_heuristic;
  };
  priority_queue<State, vector<State>, decltype(grater)> pq(grater);
  pq.push({q.a, 0, abs(q.a.r - q.b.r) + abs(q.a.c - q.b.c)});
  while (!pq.empty()) {
    State s = pq.top();
    pq.pop();
    if (s.p == q.b) {
      return true;
    }
    if (seen.count(s.p)) {
      continue;
    }
    seen.insert(s.p);
    static const int drs[] = {-1, 1, 0, 0};
    static const int dcs[] = {0, 0, -1, 1};
    for (int i=0; i<4; i++) {
      int dr = drs[i], dc = dcs[i];
      Point np = {s.p.r + dr, s.p.c + dc};
      if (np.r < 0 || np.r >= H || np.c < 0 || np.c >= W) {
        continue;
      }
      if (grid[np] == 0) {
        continue;
      }
      pq.push({np, s.dist_actual + 1, abs(np.r - q.b.r) + abs(np.c - q.b.c)});
    }
  }
  return false;
}

int main() {
  cin >> H >> W >> Q;
  queries.resize(Q);
  for (int i=0; i<Q; i++) {
    int tmp;
    cin >> tmp;
    queries[i].type = static_cast<QueryType>(tmp);
    cin >> queries[i].a.r >> queries[i].a.c;
    queries[i].a.r--; queries[i].a.c--;
    if (queries[i].type == Check) {
      cin >> queries[i].b.r >> queries[i].b.c;
      queries[i].b.r--; queries[i].b.c--;
    }
  }
  grid.init();
  for (int i=0; i<Q; i++) {
    if (queries[i].type == Draw) {
      grid[queries[i].a] = 1;
    } else {
      bool cond = grid[queries[i].a] && grid[queries[i].b];
      if (!cond) {
        cout << "No\n";
        continue;
      }
      cond = is_reachable(queries[i]);
      if (cond) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    }
  }
}