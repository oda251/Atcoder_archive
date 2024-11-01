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
  char& operator[](const Point &p) {
    return grid[p.r][p.c];
  }
};
struct Query {
  QueryType type;
  Point a, b;
};
vector<Query> queries;
Grid grid;

void draw(const Point &p) {
  grid[p] = 1;
}
bool is_reachable(const Query &q) {
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
      draw(queries[i].a);
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