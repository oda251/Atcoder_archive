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
  vector<pair<int, int>> A(N);
  rep(i, N) { cin >> A[i].first >> A[i].second; }
  double ans = 0;
  auto dist = [&](int i, int j) -> double {
    pair<int, int> x = A[i], y = A[j];
    return sqrt((x.first - y.first) * (x.first - y.first) +
                (x.second - y.second) * (x.second - y.second));
  };
  rep(i, N) rep2(j, i + 1, N) { ans = max(ans, dist(i, j)); }
  // ansを小数点第4位まで出力
  cout << fixed << setprecision(4) << ans << endl;
  return 0;
}