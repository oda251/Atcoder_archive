#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int H, W, Q;
enum QueryType { Draw = 1, Check = 2 };
struct Point {
  int r, c;
  ll hash() const {
    return r*W+c;
  };
};
struct Query {
  QueryType type;
  Point a, b;
};
vector<Query> queries;

class UnionFind {
  public:
    vector<ll> parent;
    vector<ll> rank;
    UnionFind(ll n) : parent(n, -1), rank(n, 0) {
    }
    void on(ll x) {
      if (parent[x] == -1) {
        parent[x] = x;
      }
    }
    ll find(ll x) {
      if (parent[x] == -1 || parent[x] == x) {
        return parent[x];
      } else {
        parent[x] = find(parent[x]);
        return parent[x];
      }
    }
    void unite(ll x, ll y) {
      x = find(x);
      y = find(y);
      if (x == y) return;
      if (rank[x] < rank[y]) {
        parent[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
      } else {
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
      }
    }
};

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
  UnionFind uf(H*W);
  auto draw = [&](const Point& p) {
    uf.on(p.hash());
    Point d[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i=0; i<4; i++) {
      Point n = {p.r+d[i].r, p.c+d[i].c};
      if (n.r < 0 || n.r >= H || n.c < 0 || n.c >= W) continue;
      if (uf.find(n.hash()) != -1) uf.unite(p.hash(), n.hash());
    }
  };
  auto is_reachable = [&](const Query& q) -> bool {
    ll a = uf.find(q.a.hash());
    return a != -1 && a == uf.find(q.b.hash());
  };
  for (int i=0; i<Q; i++) {
    if (queries[i].type == Draw) {
      draw(queries[i].a);
    } else {
      if (is_reachable(queries[i])) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    }
  }
  return 0;
}