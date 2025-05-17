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
  ll N, M;
  cin >> N >> M;
  vector<vector<ll>> to(N);
  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    to[a].push_back(b);
    to[b].push_back(a);
  }
  vector<bool> visited(N, false);
  ll cnt = 0;
  rep(i, N) {
    if (visited[i]) continue;
    queue<ll> que;
    que.push(i);
    visited[i] = true;
    while (!que.empty()) {
      ll v = que.front();
      que.pop();
      for (auto j : to[v]) {
        if (visited[j]) continue;
        visited[j] = true;
        ++cnt;
        que.push(j);
      }
    }
  }
  cout << M - cnt << endl;
  return 0;
}