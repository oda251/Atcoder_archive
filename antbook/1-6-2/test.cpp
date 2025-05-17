#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#define debugArr(...)
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define comp(v) (sort(all(v)), v.erase(unique(all(v)), v.end()))
#define lb(v, x) (lower_bound(all(v), x) - v.begin())
#define MAX(x, y) (x = max(x, y))
#define MIN(x, y) (x = min(x, y))
#define pb push_back
#define pi array<int, 2>
using namespace std;
#define int long long

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n, l, t;
  cin >> n >> l >> t;
  vector<pi> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0] >> a[i][1];  // a[i][0]: 初期位置, a[i][1]: 移動方向 (1:
                                // 時計回り, 2: 反時計回り)
  }

  int who = 0,
      dir = (a[0][1] == 1
                 ? 1
                 : -1);  // who: 衝突によって位置が入れ替わる蟻の数, dir:
                         // 最初の蟻の移動方向 (1: 時計回り, -1: 反時計回り)
  for (int i = 1; i < n; ++i) {
    if (a[0][1] == a[i][1])
      continue;  // 同じ方向に移動する蟻は衝突しないのでスキップ

    int dis = (a[0][1] == 1 ? a[i][0] - a[0][0]
                            : l - a[i][0] + a[0][0]);  // 蟻0と蟻iの距離
    (who += (max(t * 2 - dis - 1, 0ll) / l % n + (dis < t * 2)) * dir + n) %=
        n;  // 衝突回数を計算し、位置が入れ替わる蟻の数を更新
  }

  // debug(who);

  vector<int> vc;
  for (int i = 0; i < n; ++i) {
    vc.pb((a[i][0] + (a[i][1] == 1 ? t : -t) % l + l) %
          l);  // T秒後の各蟻の位置を計算
  }
  int zval = (a[0][0] + t * dir % l + l) % l;  // 最初の蟻のT秒後の位置
  sort(all(vc));                               // 位置でソート

  int p = lb(vc, zval);  // 最初の蟻の位置を二分探索
  if (a[0][1] == 2 && p + 1 < sz(vc) && vc[p + 1] == zval)
    ++p;  // 反時計回りの場合、同じ位置にいる蟻がいる場合はインデックスを調整
  p = (p - who + n) % n;  // 衝突による位置のずれを考慮
  for (int i = 0; i < n; ++i) {
    cout << (vc[(p + i) % n] + l) % l << '\n';
  }

  return 0;
}