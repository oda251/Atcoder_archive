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
// https://atcoder.jp/contests/arc061/tasks/arc061_a
/*####################################################*/
int main() {
  string S;
  cin >> S;
  int len = S.size();
  ll ans = 0;
  auto get_num = [&](int l, int r) {
    ll num = 0;
    for (int i = l; i < r; i++) {
      num = num * 10 + (S[i] - '0');
    }
    return num;
  };
  function<void(int, int, int)> dfs = [&](int sum, int l, int r) {
    if (r == len) {
      ans += sum + get_num(l, r);
      return;
    }
    dfs(sum + get_num(l, r), r, r + 1);
    dfs(sum, l, r + 1);
  };
  dfs(0, 0, 1);
  cout << ans << endl;
  return 0;
}