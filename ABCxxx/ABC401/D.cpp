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
/*
- 最終、各iに対して、S[i] = oが可能かどうか判定する
*/
/*####################################################*/
enum Char { o = 0, p = 1, q = 2 };
int main() {
  int N, K;
  cin >> N >> K;
  string S;
  cin >> S;
  string ans = S;
  int remain;
  int max_q = 0;
  {
    int o_cnt = 0;
    int tmp = 0;
    rep(i, N) {
      if (ans[i] == 'o') {
        o_cnt++;
      } else if (ans[i] == '.') {
      } else if (ans[i] == '?') {
        if (i > 0 && ans[i - 1] == 'o') {
          ans[i] = '.';
        } else if (i < N - 1 && S[i + 1] == 'o') {
          ans[i] = '.';
        } else {
          ans[i] = '?';
          if (i > 0 && ans[i - 1] == '?') {
            tmp++;
          } else {
            max_q += int(ceil(float(tmp) / 2));
            tmp = 1;
          }
        }
      }
    }
    max_q += int(ceil(float(tmp) / 2));
    remain = K - o_cnt;
  }
  if (max_q == remain) {
    rep(i, N) {
      if (ans[i] == '?') {
        if (i > 0 && ans[i - 1] == 'o') {
          ans[i] = '.';
        } else {
          ans[i] = 'o';
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}