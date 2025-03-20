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
auto input = []() { return 0; }();
struct Edge {
  pair<ll, ll> edge;
  ll w;
};
int main() {
  ll N, M;
  cin >> N >> M;
  vector<ll> cnt = vector<ll>(N, 0);
  vector<ll> nodes = vector<ll>(N, -1);
  vector<Edge> edges = vector<Edge>(M);
  rep(i, M) {
    ll u, v, w;
    cin >> u >> v >> w;
    edges[i].edge = {u, v};
    edges[i].w = w;
    cnt[u]++;
    cnt[v]++;
  }
  for (auto e : edges) {
    ll u = e.edge.first, v = e.edge.second, w = e.w;
    if (nodes[u] == -1 && nodes[v] == -1) {
      if (cnt[u] > cnt[v]) {
        nodes[u] = 0;
        nodes[v] = w;
      } else {
        nodes[v] = 0;
        nodes[u] = w;
      }
    } else if (nodes[u] != -1 && nodes[v] != -1) {
      if (nodes[u] ^ nodes[v] != w) {
        cout << -1 << endl;
        return 0;
      }
    } else if (nodes[u] == -1) {
      nodes[u] = nodes[v] ^ w;
    } else if (nodes[v] == -1) {
      nodes[v] = nodes[u] ^ w;
    }
  }
  rep(i, N) { cout << nodes[i] << endl; }
  return 0;
}