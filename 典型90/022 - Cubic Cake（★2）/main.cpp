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

namespace euclidian {
long long gcd(long long a, long long b) {
  if (b > a) std::swap(a, b);
  while (b != 0) {
    long long r = a % b;
    a = b;
    b = r;
  }
  return a;
}
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
}  // namespace euclidian

int main() {
  ll A, B, C;
  cin >> A >> B >> C;
  ll gcd = euclidian::gcd(A, euclidian::gcd(B, C));
  cout << (A / gcd - 1) + (B / gcd - 1) + (C / gcd - 1) << endl;
  return 0;
}