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
// op, mapping, composition, 等については問題によって適切に設定する
/*
  template <class S,                // セグメントの要素の型
            S (*op)(S, S),          // 二項演算関数
            S (*e)(),               // 単位元を返す関数
            class F,                // 作用素（更新値）の型
            S (*mapping)(F, S),     // 作用素を要素に適用する関数
            F (*composition)(F, F), // 作用素同士を合成する関数
            F (*id)()>              // 恒等作用素を返す関数
  class lazy_segtree;
*/
int op(int a, int b) { return max(a, b); }
int mp(int f, int x) { return max(f, x); }
int cm(int f, int g) { return max(f, g); }
int e() { return 0; }
int main() {
  int W, N;
  cin >> W >> N;
  atcoder::lazy_segtree<int, op, e, int, mp, cm, e> seg(W);
  rep(i, N) {
    int L, R;
    cin >> L >> R;
    --L;
    int h = seg.prod(L, R) + 1;
    cout << h << '\n';
    seg.apply(L, R, h);
  }
  return 0;
}