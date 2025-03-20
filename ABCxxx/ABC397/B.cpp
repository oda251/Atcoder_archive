#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
auto input = []() { return 0; }();

int main() {
  string s;
  cin >> s;
  int cnt = 0;
  char prev;
  if (s[0] == 'o') {
    cnt++;
    prev = 'i';
  } else {
    prev = 'o';
  }
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == prev) {
      cnt++;
    }
    prev = s[i];
  }
  if ((cnt + s.size()) % 2 == 1) {
    cnt++;
  }
  cout << cnt << endl;
  return 0;
}
