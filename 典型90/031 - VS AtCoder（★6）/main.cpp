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
// 最終的に、全ての山についてw = 0, b < 2 となるよう操作する
/*####################################################*/
int main() {
  // input
  int N;
  cin >> N;
  vector<int> W(N), B(N);
  rep(i, N) cin >> W[i];
  rep(i, N) cin >> B[i];

  int max_w = 50;
  int max_b = 50 + max_w * (max_w + 1) / 2;
  int grundy[max_w + 1][max_b + 1] = {0};  // [w][b]
  // precompute Grundy number
  rep(w, max_w + 1) rep(b, max_b + 1) if (w >= 1 || b >= 2) {
    // minimum excludant:
    // 正の整数の集合Sに対して、Sに含まれない最小の整数
    char mex[max_b + max_w + 1] = {0};
    if (w >= 1 && b + w <= max_b) mex[grundy[w - 1][b + w]] = 1;
    if (b >= 2)
      for (int i = 1; i <= b / 2; i++) mex[grundy[w][b - i]] = 1;
    int g = 0;
    while (mex[g]) g++;
    grundy[w][b] = g;
  }

  // calculate answer
  int res = 0;
  rep(i, N) res ^= grundy[W[i]][B[i]];
  cout << (res ? "First" : "Second") << endl;
  return 0;
}