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
auto input = []() { return 0; }();

struct Node {
  int idx;
  // to, w
  vector<pair<int, ll>> edge;
};

int main() {
  int N, M;
  cin >> N >> M;
  vector<Node> nodes = vector<Node>(N);
  rep(i, N) { nodes[i].idx = i; }
  rep(i, M) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    u--;
    v--;
    nodes[u].edge.push_back({v, w});
    nodes[v].edge.push_back({u, w});
  }
  vector<bool> visited(N, false);
  ll x = 0;
  ll ans = LLONG_MAX;
  function<void(int, ll)> dfs = [&](int cur, ll w) {
    visited[cur] = true;
    if (cur == N - 1) {
      ans = min(ans, x);
    } else {
      for (auto &e : nodes[cur].edge) {
        if (!visited[e.first]) {
          x ^= e.second;
          dfs(e.first, e.second);
          x ^= e.second;
        }
      }
    };
    visited[cur] = false;
  };
  dfs(0, 0);
  cout << ans << endl;
  return 0;
}