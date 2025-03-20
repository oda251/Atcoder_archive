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
int main() {
  int N;
  cin >> N;
  unordered_map<string, int> mp;
  rep(i, N) {
    string s;
    cin >> s;
    if (mp[s] == 0) {
      cout << i + 1 << '\n';
    }
    ++mp[s];
  }
  cout << flush;
  return 0;
}