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
  int mp[1001][1001] = {};
  rep(i, N) {
    int lx, ly, rx, ry;
    cin >> lx >> ly >> rx >> ry;
    mp[lx][ly]++;
    mp[rx][ry]++;
    mp[lx][ry]--;
    mp[rx][ly]--;
  }
  rep(i, 1001) rep(j, 1000) mp[i][j + 1] += mp[i][j];
  rep(j, 1001) rep(i, 1000) mp[i + 1][j] += mp[i][j];
  vector<int> ans(N + 1, 0);
  rep(i, 1001) rep(j, 1001) ans[mp[i][j]]++;
  for (int i = 1; i <= N; i++) cout << ans[i] << endl;
  return 0;
}
