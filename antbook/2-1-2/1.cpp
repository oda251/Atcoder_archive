#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, l, r) for (int i = l; i < r; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
time_t start = clock();
#define cerr_time() \
  cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;

struct UnionFind {
  vector<int> par;
  UnionFind(int n) : par(n, -1) {}
  int root(int x) {
    if (par[x] < 0) return x;
    return par[x] = root(par[x]);
  }
  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
  bool same(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -par[root(x)]; }
};

/*####################################################*/
int main() {
  int H, W;
  cin >> H >> W;
  vector<string> mp(H);
  rep(i, H) cin >> mp[i];
  int s, g;
  UnionFind uf(H * W);
  auto is_reachable = [&](int i, int j) {
    return 0 <= i && i < H && 0 <= j && j < W &&
           (mp[i][j] == '.' || mp[i][j] == 'g' || mp[i][j] == 's');
  };
  rep(i, H) rep(j, W) {
    if (mp[i][j] == '#') continue;
    if (mp[i][j] == 's')
      s = i * W + j;
    else if (mp[i][j] == 'g')
      g = i * W + j;
    if (is_reachable(i + 1, j)) uf.unite(i * W + j, (i + 1) * W + j);
    if (is_reachable(i, j + 1)) uf.unite(i * W + j, i * W + j + 1);
  }
  if (uf.same(s, g))
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}