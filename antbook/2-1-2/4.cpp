#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, l, r) for (int i = l; i < r; ++i)
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
time_t start = clock();
#define cerr_time() \
  cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
/*####################################################*/
int main() {
  while (true) {
    int w, h;
    cin >> w >> h;
    if (w == 0 && h == 0) break;
    vector<vector<bool>> mp(h, vector<bool>(w));
    rep(i, h) rep(j, w) {
      int a;
      cin >> a;
      mp[i][j] = a == 1;
    }
    vector<vector<bool>> visited(h, vector<bool>(w));
    int ans = 0;
    function<void(int, int)> dfs = [&](int x, int y) {
      if (x < 0 || x >= h || y < 0 || y >= w || visited[x][y] || !mp[x][y])
        return;
      visited[x][y] = true;
      for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) dfs(x + dx, y + dy);
    };
    rep(i, h) rep(j, w) {
      if (visited[i][j] || !mp[i][j]) continue;
      dfs(i, j);
      ans++;
    }
    cout << ans << endl;
  }
  return 0;
}
