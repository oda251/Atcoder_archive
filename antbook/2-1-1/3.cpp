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
// https://atcoder.jp/contests/abc104/tasks/abc104_c
/*####################################################*/
int main() {
  int D, G;
  cin >> D >> G;
  vector<int> p(D), c(D);
  rep(i, D) cin >> p[i] >> c[i];
  int ans = INT_MAX;
  rep(i, 1 << D) {
    int sum = 0;
    int cnt = 0;
    rep(j, D) {
      if (i & 1 << j) {
        sum += p[j] * (j + 1) * 100 + c[j];
        cnt += p[j];
      }
    }
    if (sum >= G) {
      ans = min(ans, cnt);
    } else {
      for (int j = D - 1; j >= 0; j--) {
        if (i & 1 << j) continue;
        rep(k, p[j]) {
          if (sum >= G) break;
          sum += (j + 1) * 100;
          cnt++;
        }
      }
      ans = min(ans, cnt);
    }
  }
  cout << ans << endl;
  return 0;
}