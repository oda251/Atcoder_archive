#include <bits/stdc++.h>

#include <atcoder/all>
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
  int H, W, N;
  cin >> H >> W >> N;
  vector<string> mp(H);
  pair<int, int> cur = {0, 0};
  rep(i, H) {
    cin >> mp[i];
    rep(j, W) {
      if (mp[i][j] == 'S') {
        cur = {i, j};
        mp[i][j] = '.';
      }
    }
  }
  int ans = 0;
  int vital = 1;
  int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  rep(i, N) {
    deque<pair<int, int>> que;
    que.push_back(cur);
    vector<vector<int>> dist(H, vector<int>(W, -1));
    dist[cur.first][cur.second] = 0;
    while (que.size()) {
      auto [x, y] = que.front();
      que.pop_front();
      cur = {x, y};
      if (isdigit(mp[x][y]) && mp[x][y] - '0' == vital) {
        ans += dist[x][y];
        ++vital;
        mp[x][y] = '.';
        break;
      }
      for (auto [dx, dy] : dir) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (mp[nx][ny] == 'X') continue;
        if (dist[nx][ny] != -1) continue;
        dist[nx][ny] = dist[x][y] + 1;
        que.push_back({nx, ny});
      }
    }
  }
  cout << ans << endl;
  return 0;
}