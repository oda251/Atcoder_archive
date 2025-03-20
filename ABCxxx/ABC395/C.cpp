#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
auto input = []() { return 0; }();

int main() {
  ll N;
  cin >> N;
  vector<ll> prev_appear(1000000, -1);
  ll ans = LLONG_MAX;
  rep(i, N) {
    ll a;
    cin >> a;
    a--;
    if (prev_appear[a] != -1) {
      ans = min(ans, i - prev_appear[a] + 1);
    }
    prev_appear[a] = i;
  }
  cout << (ans == LLONG_MAX ? -1 : ans) << endl;
  return 0;
}