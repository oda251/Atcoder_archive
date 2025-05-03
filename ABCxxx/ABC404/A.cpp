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
  char list[26];
  for (int i = 0; i < 26; i++) {
    list[i] = 'a' + i;
  }
  string S;
  cin >> S;
  for (auto c : S) {
    list[c - 'a'] = '.';
  }
  for (int i = 0; i < 26; i++) {
    if (list[i] != '.') {
      cout << list[i] << endl;
      return 0;
    }
  }
  return 0;
}