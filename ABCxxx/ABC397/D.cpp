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

pair<ll, ll> solve(ll a, ll b) {
  ll alpha_2_x_3 = 4 * b - a * a;
  if (alpha_2_x_3 % 3 != 0) {
    return {-1, -1};
  }
  ll alpha_2 = alpha_2_x_3 / 3;
  ll alpha = sqrt(alpha_2);
  if (alpha * alpha != alpha_2) {
    return {-1, -1};
  }
  if ((alpha + a) % 2 != 0) {
    return {-1, -1};
  }
  ll x = (alpha + a) / 2;
  ll y = alpha - x;
  if (x <= 0 || y <= 0) {
    return {-1, -1};
  }
  return {x, y};
}

int main() {
  ll N;
  cin >> N;
  if (N % 2 == 0) {
    auto tmp = solve(1, N / 2);
    if (tmp.first != -1) {
      cout << tmp.first << " " << tmp.second << endl;
      return 0;
    }
    for (ll i = 2; i * i <= N; i += 2) {
      if (N % i == 0) {
        tmp = solve(i, N / i);
        if (tmp.first != -1) {
          cout << tmp.first << " " << tmp.second << endl;
          return 0;
        }
      }
    }
  } else {
    for (ll i = 1; i * i <= N; i += 2) {
      if (N % i == 0) {
        auto tmp = solve(i, N / i);
        if (tmp.first != -1) {
          cout << tmp.first << " " << tmp.second << endl;
          return 0;
        }
      }
    }
  }
  cout << -1 << endl;
}
