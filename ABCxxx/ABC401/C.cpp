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
  cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl
using mint = atcoder::static_modint<1000000000>;
/*####################################################*/
int main() {
  int N, K;
  cin >> N >> K;
  atcoder::fenwick_tree<mint> bit(N + 1);
  if (N < K) {
    cout << 0 << endl;
    return 0;
  }
  rep(i, K) bit.add(i, 1);
  rep2(i, K, N + 1) { bit.add(i, bit.sum(i - K, i)); }
  cout << bit.sum(N, N + 1).val() << endl;
  return 0;
}