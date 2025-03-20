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
auto input = []() {
  return 0;
}();

int main() {
  double i;
  cin >> i;
  if (i >= 38) {
    cout << 1 << endl;
  } else if (i < 37.5) {
    cout << 3 << endl;
  } else {
    cout << 2 << endl;
  }
  return 0;
}