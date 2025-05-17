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
  int N, K;
  cin >> N >> K;
  vector<ll> A(N);
  rep(i, N) cin >> A[i];
  ll lim = pow(10, K);
  ll ans = 1;
  for (int i = 0; i < N; i++) {
    if (lim / ans < A[i]) {
      ans = 1;
    } else {
      ans *= A[i];
      if (ans >= lim) {
        ans = 1;
      }
    }
  }
  cout << ans << endl;
  return 0;
}