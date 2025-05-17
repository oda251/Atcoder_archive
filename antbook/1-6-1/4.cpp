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
  vector<ll> L(N);
  rep(i, N) { cin >> L[i]; }
  int ans = 0;
  rep(i, N) rep2(j, i + 1, N) rep2(k, j + 1, N) {
    if (L[i] == L[j] || L[j] == L[k] || L[k] == L[i]) {
      continue;
    }
    ll set[3] = {L[i], L[j], L[k]};
    sort(set, set + 3);
    if (set[0] + set[1] > set[2]) {
      ++ans;
    }
  }
  cout << ans << endl;
  return 0;
}