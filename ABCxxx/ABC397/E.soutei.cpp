#include <bits/stdc++.h>

#include <atcoder/lazysegtree>
using namespace std;

// セグメント木の演算を定義
// 二つの値の最大値を返す
int op(int a, int b) { return max(a, b); }
// セグメント木の単位元（最小値として十分小さい値）
int e() { return -1e9; }
// 遅延評価用の関数：値xに操作fを適用（ここでは加算）
int mapping(int f, int x) { return f + x; }
// 遅延評価の合成関数：f, gを合成（ここでは加算の合成）
int composition(int f, int g) { return f + g; }
// 遅延評価の単位元（変化なし）
int id() { return 0; }

int main() {
  int n;
  cin >> n;

  // 数列Aを入力
  vector<int> a(n);
  for (auto& e : a) cin >> e;

  // x[i]: 区間[0,i]と区間[i+1,n-1]を最適に分割したときの種類数の和
  vector<int> x(n, 0);

  // suml[i]: 左端から位置iまでの部分列における異なる要素の数
  // sumr[i]: 位置iから右端までの部分列における異なる要素の数
  vector<int> suml(n), sumr(n);

  // 左からの累積種類数を計算
  int now = 0;
  vector<int> vis(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    if (++vis[a[i]] == 1) {
      // 新しい種類の要素が出現したらカウント増加
      now++;
    }
    suml[i] = now;
  }

  // 右からの累積種類数を計算
  vis = vector<int>(n + 1, 0);
  now = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (++vis[a[i]] == 1) {
      // 新しい種類の要素が出現したらカウント増加
      now++;
    }
    sumr[i] = now;
  }

  // 遅延セグメント木を初期化
  // 区間の最大値と区間加算を効率的に処理するためのデータ構造
  atcoder::lazy_segtree<int, op, e, int, mapping, composition, id> dp(n);

  // last[i]: 値iが最後に出現したインデックス（-1は未出現）
  vector<int> last(n + 1, -1);

  // 動的計画法で中間区間の最適な分割を計算
  for (int i = 0; i < n; ++i) {
    // 値a[i]が前回出現した位置から現在位置iまでの区間に+1を適用
    // これによりa[i]を含む区間の種類数を正確に計算
    dp.apply(last[a[i]] == -1 ? 0 : last[a[i]], i, 1);

    // x[i]は[0,i]の区間での最適な分割における種類数の和
    x[i] = dp.prod(0, i);

    // dp[i]に左端からiまでの種類数をセット
    dp.set(i, suml[i]);

    // a[i]の最後の出現位置を更新
    last[a[i]] = i;
  }

  // 最終的な答えを計算
  // ans = max(左区間の種類数 + 中間区間の最適種類数 + 右区間の種類数)
  int ans = 0;
  for (int i = 1; i < n - 1; ++i) {
    // x[i]: [0,i]での最適な2分割の種類数の和
    // sumr[i+1]: 右区間[i+1,n-1]の種類数
    ans = max(ans, x[i] + sumr[i + 1]);
  }

  cout << ans << endl;
}
