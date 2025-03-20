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
auto input = []() {
  return 0;
}();

int main() {
  ll N, X;
  cin >> N >> X;
  vector<ll> U(N), D(N);
  ll max_h = 0;
  ll min_u = LLONG_MAX;
  rep(i, N) {
    cin >> U[i] >> D[i];
    if (max_h < U[i] + D[i]) {
      max_h = U[i] + D[i];
    }
    if (min_u > U[i]) {
      min_u = U[i];
    }
  }
  ll ok = 0, ng = max_h + 1;
  auto judge = [&](ll h) {
    for (int i = 0; i < N; i++) {
      ll u = U[i], d = D[i];
      if (u + d < h) {
        return false;
      }
      if (min_u + X < u && min_u + X + d < h) {
        return false;
      }
    }
    return true;
  };
  while (ng - ok > 1) {
    ll mid = (ok + ng) / 2;
    if (judge(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  ll ans = 0;
  rep(i, N) {
    ans += U[i] + D[i] - ok;
  }
  cout << ans << endl;
  return 0;
}