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
  int N;
  cin >> N;
  vector<int> t(N);
  rep(i, N) cin >> t[i];
  int ans = INT_MAX;
  rep(i, 1 << N) {
    int sum_r = 0;
    int sum_l = 0;
    rep(j, N) {
      if (i & 1 << j) {
        sum_r += t[j];
      } else {
        sum_l += t[j];
      }
    }
    ans = min(ans, max(sum_r, sum_l));
  }
  cout << ans << endl;
  return 0;
}