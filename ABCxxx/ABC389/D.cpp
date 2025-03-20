#include <bits/stdc++.h>
using namespace std;
using ll = long long;
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
double R;
auto input = []() {
  cin >> R;
  return 0;
}();

int main() {
  ll ans = 0;
  for (double i = 0.5; i < R; i += 1) {
    ans += floor(sqrt(R * R - i * i) - 0.5);
  }
  cout << ans * 4 + 1 << endl;
  return 0;
}