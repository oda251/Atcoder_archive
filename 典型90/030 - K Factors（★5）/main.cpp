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
  int N, K;
  cin >> N >> K;
  vector<int> c(N + 1, 0);
  int cnt = 0;
  rep(i, N + 1) {
    if (c[i] != 0) continue;
    for (int j = i; j < N + 1; j++) {
      if (c[j] % i == 0) {
        ++c[j];
        if (c[j] == K) ++cnt;
      }
    }
  }
  cout << cnt << endl;
  return 0;
}