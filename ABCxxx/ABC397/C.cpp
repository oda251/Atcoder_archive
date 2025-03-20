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
  ll N;
  cin >> N;
  vector<ll> l_cnt(N);
  vector<ll> r_cnt(N);
  vector<ll> A(N);
  rep(i, N) { cin >> A[i]; }
  {
    vector<bool> cnt(N + 1, false);
    rep(i, N - 1) {
      if (i == 0) {
        l_cnt[i] = 0;
      } else {
        l_cnt[i] = l_cnt[i - 1];
      }
      ll n = A[i];
      if (cnt[n] == false) {
        l_cnt[i]++;
      }
      cnt[n] = true;
    }
  }
  {
    vector<bool> cnt(N + 1, false);
    rep(i, N - 1) {
      if (i == 0) {
        r_cnt[i] = 0;
      } else {
        r_cnt[i] = r_cnt[i - 1];
      }
      ll n = A[N - i - 1];
      if (cnt[n] == false) {
        r_cnt[i]++;
      }
      cnt[n] = true;
    }
  }
  ll ans = 0;
  rep(i, N - 1) { ans = max(ans, l_cnt[i] + r_cnt[N - i - 2]); }
  cout << ans << endl;
  return 0;
}
