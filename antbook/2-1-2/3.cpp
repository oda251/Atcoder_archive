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
/*####################################################*/
int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> to(N);
  rep(i, M) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    to[a].push_back(b);
    to[b].push_back(a);
  }
  vector<bool> visited(N, false);
  int ans = 0;
  function<int(int, int)> dfs = [&](int from, int v) {
    visited[v] = true;
    for (int u : to[v]) {
      if (visited[u]) {
        if (u != from) return 0;
        continue;
      }
      if (dfs(v, u) == 0) return 0;
    }
    return 1;
  };
  rep(i, N) {
    if (visited[i]) continue;
    ans += dfs(-1, i);
  }
  cout << ans << endl;
  return 0;
}