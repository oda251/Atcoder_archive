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
  ll T;
  cin >> T;
  rep(t, T) {
    ll N;
    cin >> N;
    unordered_map<int, unordered_map<int, int>> mp;
    vector<bool> check(N * 2, false);
    ll cnt = 0;
    ll pre;
    cin >> pre;
    pre--;
    rep2(i, 1, N * 2) {
      ll nex;
      cin >> nex;
      nex--;
      if (pre == nex) {
        check[pre] = true;
      }
      int a = min(pre, nex), b = max(pre, nex);
      if (mp[a][b] > 0 && mp[a][b] + 1 < i) {
        if (!check[a] && !check[b]) {
          cnt++;
        }
        mp[a][b] = -1;
      } else if (mp[a][b] == 0) {
        mp[a][b] = i;
      }
      pre = nex;
    }
    cout << cnt << '\n';
  }
  cout << flush;
  return 0;
}