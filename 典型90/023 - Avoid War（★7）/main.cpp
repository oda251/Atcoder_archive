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
auto start = chrono::system_clock::now();
void debug() {
  auto end = chrono::system_clock::now();
  double elapsed =
      chrono::duration_cast<chrono::milliseconds>(end - start).count();
  cerr << "elapsed time: " << elapsed << "ms" << endl;
}
/*####################################################*/
struct Pattern {
  int w;
  // [k(0 <= k <= W)], kごとのパターン数を記録
  vector<ll> cnt;
  // [k(0 <= k <= W)][l(0 <= l <= cnt[k])], kのl番目のパターンを記録
  vector<vector<ll>> state;
  // [k(0 <= k <= W)][state], kにおいてstateが何番目のパターンかを記録
  vector<unordered_map<ll, ll>> mp;
  Pattern(int w_) : w(w_) {
    cnt.resize(w, 0);
    state.resize(w);
    mp.resize(w);
    // 立っているビットが連続しないようなパターンを生成
    function<void(int, int, int)> dfs = [&](int k, int bit, int bit_size) {
      if (bit_size == w) {
        state[k].push_back(bit);
        mp[k][bit] = cnt[k]++;
        return;
      } else {
        if (bit & 1) {
          dfs(k, bit << 1, bit_size + 1);
          // 例外的に、立っているビットが連続するパターンを処理
          if (bit_size + k == w) {
            dfs(k, bit << 1 | 1, bit_size + 1);
          }
        } else {
          dfs(k, bit << 1, bit_size + 1);
          dfs(k, bit << 1 | 1, bit_size + 1);
        }
      }
    };
    rep(i, w) { dfs(i, 0, 0); }
  }
};
int main() {
  int H, W;
  cin >> H >> W;
  Pattern p(W);
  int idx = 0;
  vector<ll> next(1 << W, 0);
  debug();
  return 0;
}
