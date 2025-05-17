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
enum Dir { CLOCKWISE, COUNTERCLOCKWISE };
int main() {
  int N;  // amount of ants
  ll L;   // length of circle
  ll T;   // time
  cin >> N >> L >> T;
  vector<ll> X(N);
  vector<Dir> W(N);
  rep(i, N) {
    cin >> X[i];
    char c;
    cin >> c;
    W[i] = c == '1' ? CLOCKWISE : COUNTERCLOCKWISE;
  }
  // 1. T秒後の蟻の位置を求める
  vector<ll> pos(N);
  rep(i, N) {
    pos[i] = (W[i] == CLOCKWISE ? X[i] + T : X[i] - T) % L;
    if (pos[i] < 0) pos[i] += L;
  }
  ll pos_0 = pos[0];             // 蟻0が最終的にどこにいるか保存
  sort(pos.begin(), pos.end());  // 位置をソート
  // 2. 蟻0と各蟻との衝突回数をもとに、蟻0が最終的に何番になっているかを求める
  int idx = 0;
  rep2(i, 1, N) {
    if (W[i] == W[0]) {
      continue;
    } else {
      double t = T;
      // 蟻0とiの距離を求める
      // t -= abs(X[i] - X[0]) / 2; // 計算が誤っている
      int dist = (W[i] == CLOCKWISE ? X[i] - X[0] : L - X[i] + X[0]);
      t -= dist / 2;
      if (t < 0) {
        continue;
      } else {
        int dir = W[i] == CLOCKWISE ? 1 : -1;
        idx += 1 * dir;
        idx += (t / ((double)L / 2)) * dir;
      }
      idx %= N;
      if (idx < 0) idx += N;
    }
  }
  rep(i, N) { cout << pos[(i + idx) % N] << endl; }
  return 0;
}