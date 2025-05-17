#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, l, r) for (int i = l; i < r; ++i)
#define all(x) (x).begin(), (x).end()
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
  ll N;
  cin >> N;
  vector<ll> P(N);
  rep(i, N) cin >> P[i];
  int phase = 0;        // 0: none, 1: up, 2: down, 3: up
  int cnt[2] = {0, 0};  // up, up
  ll ans = 0;
  for (int i = 1; i < N; i++) {
    switch (phase) {
      case 0:
        if (P[i] > P[i - 1]) {
          phase = 1;
          cnt[1]++;
        }
        break;
      case 1:
        if (P[i] < P[i - 1]) {
          phase = 2;
        } else {
          cnt[1]++;
          ans += cnt[0];
        }
        break;
      case 2:
        if (P[i] > P[i - 1]) {
          cnt[0] = cnt[1];
          ans += cnt[0];
          cnt[1] = 1;
          phase = 1;
        }
        break;
    }
  }
  cout << ans << endl;
  return 0;
}