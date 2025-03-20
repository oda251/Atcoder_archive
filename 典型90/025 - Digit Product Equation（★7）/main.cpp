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
  ll N, B;
  cin >> N >> B;
  ll cnt = 0;
  auto judge = [&](ll x) -> bool {
    list<int> digit;
    ll f = 1;
    for (ll n = x; n > 0; n /= 10) {
      digit.push_back(n % 10);
      f *= n % 10;
    }
    ll m = B + f;
    // バリデータ大事ね
    if (m > N) return false;
    for (ll n = m; n > 0; n /= 10) {
      auto it = find(digit.begin(), digit.end(), n % 10);
      if (it != digit.end()) {
        digit.erase(it);
      } else {
        return false;
      }
    }
    return digit.empty();
  };
  function<void(ll)> dfs = [&](ll x) {
    if (x > N) return;
    if (judge(x)) {
      cnt++;
    }
    for (int i = x != 0 ? x % 10 : 1; i < 10; i++) {
      dfs(x * 10 + i);
    }
  };
  // いずれかの桁に0を含むケース
  {
    ll m = B;  // ∵ f(m) = 0
    if (m <= N) {
      for (; m > 0; m /= 10) {
        if (m % 10 == 0) {
          ++cnt;
          break;
        }
      }
    }
  }
  // それ以外のケース
  dfs(0);
  cout << cnt << endl;
  return 0;
}