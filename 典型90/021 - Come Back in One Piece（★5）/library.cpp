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
ll N, M;
vector<pair<ll, ll>> E;
auto input = []() {
  cin >> N >> M;
  E.resize(M);
  rep(i, M) {
    cin >> E[i].first >> E[i].second;
    E[i].first--;
    E[i].second--;
  }
  return 0;
}();

int main() {
  atcoder::scc_graph G(N);
  for (auto [u, v] : E) {
    G.add_edge(u, v);
  }
  auto groups = G.scc();
  ll sum = 0;
  for (auto group : groups) {
    sum += (ll)group.size() * (group.size() - 1) / 2;
  }
  cout << sum << endl;
  return 0;
}