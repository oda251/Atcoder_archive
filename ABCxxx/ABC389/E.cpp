#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
ll N, M;
vector<ll> P;
auto input = []() {
  cin >> N >> M;
  P.resize(N);
  for (ll i = 0; i < N; i++) {
    cin >> P[i];
  }
  return 0;
}();

int main() {
  ll ans, total;
  auto judge = [&](ll x) {
    total = 0;
    ans = 0;
    for (ll i = 0; i < N; i++) {
      ll j = (x / P[i] + 1) / 2;
      if (j == 0) continue;
      // NG
      //   if ((M - total) / (j * j) < P[i]) return false;
      // OK
      //   if ((M - total) / (j * j) < P[i]) return false;
      // OK
      if (M / j / j / P[i] == 0) return false;
      total += j * j * P[i];
      if (total > M) return false;
      ans += j;
    }
    return total <= M;
  };
  ll left = 0, right = M + 1, mid;
  while (right - left > 1) {
    mid = (left + right) / 2;
    if (judge(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  judge(left);
  // costがleft以下をすべて購入しており、かつ「left+1以下をすべて購入」はできない。よって、cost=left+1を残金分買うことで最大数購入できる
  if (total < M) ans += (M - total) / (left + 1);
  cout << ans << endl;
  return 0;
}