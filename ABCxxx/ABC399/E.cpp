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
  string S, T;
  cin >> S >> T;
  int ans = 0;
  int cnt = 0;
  char to[26];
  fill(to, to + 26, -1);
  rep(i, N) {
    char s = S[i] - 'a', t = T[i] - 'a';
    if (to[s] != -1 && to[s] != t) {
      return 0;
    }
    if (to[s] == -1) {
      to[s] = t;
      ++cnt;
    }
  }
  bool seen[26] = {0};
  function<bool(int)> solve = [&](int i) {
    char& dst = to[i];
    if (dst == -1) {
      seen[i] = true;
      return true;
    } else if (to[dst] == -1) {
      dst = -1;
      --cnt;
      seen[i] = true;
      ++ans;
      return true;
    } else {
      if (seen[dst]) {
        int j = 0;
        while (j < 26 && seen[j]) {
          ++j;
        }
        if (j == 26) {
          cout << -1 << endl;
          cerr << "j == 26" << endl;
          exit(0);
        }
        dst = j;
        ++ans;
        return false;
      } else {
        seen[i] = true;
        if (!solve(dst)) {
          return solve(i);
        }
      }
    }
    return true;
  };
  while (cnt) {
    rep(i, 26) {
      if (!seen[i]) {
        solve(i);
      }
    }
  }
  cout << ans << endl;
  return 0;
}