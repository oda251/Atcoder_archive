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

int main() {
  ll N, M;
  cin >> N >> M;
  vector<ll> B(N);
  vector<ll> W(M);
  rep(i, N) { cin >> B[i]; }
  rep(i, M) { cin >> W[i]; }
  sort(B.rbegin(), B.rend());
  sort(W.rbegin(), W.rend());
  ll ans = 0;
  ll b_cnt = 0;
  for (b_cnt = 0; b_cnt < N; b_cnt++) {
    if (B[b_cnt] >= 0) {
      ans += B[b_cnt];
    } else {
      break;
    }
  }
  ll w_cnt = 0;
  for (w_cnt = 0; w_cnt < M && w_cnt < b_cnt; w_cnt++) {
    if (W[w_cnt] >= 0) {
      ans += W[w_cnt];
    } else {
      break;
    }
  }
  for (int i = w_cnt; i < M && b_cnt < N; i++) {
    if (B[b_cnt] + W[i] > 0) {
      ans += B[b_cnt] + W[i];
      b_cnt++;
    } else {
      break;
    }
  }
  cout << ans << endl;
  return 0;
}