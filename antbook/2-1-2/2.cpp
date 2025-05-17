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
  vector<string> mp(10);
  int land_cnt = 0;
  pair<int, int> s = {-1, -1};
  rep(i, 10) {
    cin >> mp[i];
    rep(j, 10) if (mp[i][j] == 'o') {
      land_cnt++;
      if (s.first == -1) s = {i, j};
    }
  }
  rep(i, 10) rep(j, 10) {
    vector<string> cp = mp;
    int cnt = 0;
    if (cp[i][j] == 'o') ++cnt;
    cp[i][j] = 'o';
    function<void(int, int)> dfs = [&](int x, int y) {
      if (x < 0 || x >= 10 || y < 0 || y >= 10 || cp[x][y] == 'x') return;
      cp[x][y] = 'x';
      cnt++;
      dfs(x + 1, y);
      dfs(x - 1, y);
      dfs(x, y + 1);
      dfs(x, y - 1);
    };
    dfs(s.first, s.second);
    if (cnt == land_cnt + 1) {
      cout << "YES" << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}