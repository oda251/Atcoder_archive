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

bool judge(ll a, ll b, ll c) {
  ll sum = 1;
  for (int i = 0; i < b; i++) {
    if (LLONG_MAX / c < sum) {
      return false;
    } else {
      sum *= c;
      if (sum > a) {
        return true;
      }
    }
  }
  return false;
}
int main() {
  ll a, b, c;
  cin >> a >> b >> c;
  cout << (judge(a, b, c) ? "Yes" : "No") << endl;
  return 0;
}