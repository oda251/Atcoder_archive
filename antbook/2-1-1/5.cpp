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
  int N, M;
  cin >> N >> M;
  vector<int> r(N, 0);
  rep(i, N) r[i] = 1 << i;
  rep(i, M) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    r[a] |= 1 << b;
    r[b] |= 1 << a;
  }
  int ans = 0;
  rep(i, 1 << N) {  // i: 派閥の組み合わせ
    int cnt = 0;
    rep(j, N) {
      if (i & (1 << j)) {  // 議員jが派閥にいるとき
        if ((i & r[j]) == i) {
          cnt++;
        } else {
          break;
        }
      }
    }
    ans = max(ans, cnt);
  }
  cout << ans << endl;
  return 0;
}