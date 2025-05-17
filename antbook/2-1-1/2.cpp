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
// https://atcoder.jp/contests/abc079/tasks/abc079_c
/*####################################################*/
int main() {
  string s;
  cin >> s;
  int a = s[0] - '0';
  int b = s[1] - '0';
  int c = s[2] - '0';
  int d = s[3] - '0';
  for (int i = 0; i < 1 << 3; i++) {
    int op[3];
    rep(j, 3) { op[j] = i & 1 << j ? -1 : 1; }
#define op(i) (op[i] == 1 ? '+' : '-')
    if (a + op[0] * b + op[1] * c + op[2] * d == 7) {
      cout << a << op(0) << b << op(1) << c << op(2) << d << "=7" << endl;
      return 0;
    }
  }
  return 0;
}
