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
  // 長さKのパスとは、頂点数Kかつ一筆書きですべての頂点に到達できる部分木のこと。
  int N, K;
  cin >> N >> K;
  vector<vector<int>> to(N * K);
  rep(i, N * K - 1) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    to[u].push_back(v);
    to[v].push_back(u);
  }
  vector<bool> visited(N * K, false);
  function<int(int)> dfs = [&](int v) {
    visited[v] = true;
    // size: 部分木のサイズ
    // degree: vを含む部分木の子の数
    //  - パスは、一筆書きできるできる必要がある
    //    そのため、三股以上のノードを含む部分木は、サイズKであっても不可
    int size = 1;
    int degree = 0;
    for (int u : to[v]) {
      if (visited[u]) {
        continue;
      }
      auto s = dfs(u);
      size += s;
      if (s > 0) ++degree;
      // 以下のとき不可となる
      // - 部分木のサイズがKより大きい
      // - 部分木の次数が2より大きい
      // - 部分木のサイズがKより小さく、次数が1より大きい
      //   - これは、戻りがけに次数が3以上になり、パスを形成できなくなるから
      if (size > K || degree > 2 || (size < K && degree > 1)) {
        cout << "No" << endl;
        exit(0);
      }
    }
    if (size == K) {
      return 0;
    }
    return size;
  };
  dfs(0);
  cout << "Yes" << endl;
  return 0;
}