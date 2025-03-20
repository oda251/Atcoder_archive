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
  int prev = 0;
  rep(i, N) {
    if (i == 0) {
      cin >> prev;
      continue;
    }
    int n;
    cin >> n;
    if (n <= prev) {
      cout << "No" << endl;
      return 0;
    } else {
      prev = n;
    }
  }
  cout << "Yes" << endl;
  return 0;
}