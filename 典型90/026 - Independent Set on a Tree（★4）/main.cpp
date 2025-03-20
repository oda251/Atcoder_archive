#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
int main() {
  int N;
  cin >> N;
  vector<vector<int>> to(N);
  rep(i, N - 1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    to[u].push_back(v);
    to[v].push_back(u);
  }
  vector<bool> visited(N, false);
  // 二部グラフに分けられるが、一方がN/2より大きく、もう一方が小さくなる場合は十分ある
  vector<int> group1, group2;
  int cnt = 0;
  function<void(int, bool)> dfs = [&](int v, bool flag) {
    visited[v] = true;
    if (flag)
      group1.push_back(v + 1);
    else
      group2.push_back(v + 1);
    for (int u : to[v]) {
      if (visited[u]) continue;
      dfs(u, !flag);
    }
  };
  dfs(0, true);
  vector<int>* ans = group1.size() > group2.size() ? &group1 : &group2;
  rep(i, N / 2) {
    if (i < N / 2 - 1)
      cout << (*ans)[i] << " ";
    else
      cout << (*ans)[i] << endl;
  }
  return 0;
}
