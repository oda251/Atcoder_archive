#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
int main() {
  ll N, M;
  cin >> N >> M;
  vector<int> X(M), Y(M);
  vector<ll> Z(M);
  vector<vector<pair<int, ll>>> G(N + 1);
  rep(i, M) {
    cin >> X[i] >> Y[i] >> Z[i];
    G[X[i]].push_back({Y[i], Z[i]});
    G[Y[i]].push_back({X[i], Z[i]});
  }
  vector<bool> visited(N + 1, false);
  vector<ll> value(N + 1, -1);
  auto bfs = [&](int s) {
    uint a = 0, b = 0 - 1;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto [nv, w] : G[v]) {
        if (!visited[nv]) q.push(nv);
      }
    }
  };
  rep(i, N + 1) {
    if (G[i].empty()) {
      continue;
    }
  }
  rep(i, N + 1) return 0;
}