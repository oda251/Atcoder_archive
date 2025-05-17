#ifdef NACHIA
#define _GLIBCXX_DEBUG
#else
#define NDEBUG
#endif
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using i64 = long long;
using u64 = unsigned long long;
#define rep(i, n) for (i64 i = 0; i < i64(n); i++)
const i64 INF = 1001001001001001001;
template <typename A>
void chmin(A& l, const A& r) {
  if (r < l) l = r;
}  // 最小値の更新を行うヘルパー関数
template <typename A>
void chmax(A& l, const A& r) {
  if (l < r) l = r;
}  // 最大値の更新を行うヘルパー関数
using namespace std;

void testcase() {
  i64 N, K;
  cin >> N >> K;
  string S;
  cin >> S;

  // 'o'の左右の文字を'.'に変更（'o'は隣接できないというルールを適用）
  rep(i, N - 1) if (S[i] == 'o') S[i + 1] = '.';
  rep(i, N - 1) if (S[i + 1] == 'o') S[i] = '.';

  // すでに'o'となっている文字の数をカウントし、残りの配置可能な'o'の数を計算
  i64 cnt0 = K;
  for (char c : S)
    if (c == 'o') cnt0 -= 1;

  // いもす法のための配列を初期化（区間に対する加減算を行うためのデータ構造）
  vector<i64> imos(N + 1);

  // 文字列をスキャンして'?'を見つけ、'o'を配置できる候補位置を返すラムダ関数
  auto scanS = [&]() -> vector<i64> {
    vector<i64> res;
    i64 i = 0;
    while (i < N && i64(res.size() < cnt0)) {
      if (S[i] == '?') {
        res.push_back(i);  // '?'の位置を記録
        i += 2;            // 'o'を配置したら隣の文字は'o'にできないためスキップ
      } else {
        i += 1;
      }
    }
    return res;
  };

  // 左から右へスキャンして'o'を配置できる候補位置を取得
  auto A = scanS();

  // 文字列を反転して右から左への走査を行う
  reverse(S.begin(), S.end());
  auto B = scanS();  // 右から左へスキャン

  // 元の向きに戻す
  reverse(S.begin(), S.end());
  reverse(B.begin(), B.end());

  // インデックスを変換（右から左へのスキャン結果を元の座標系に変換）
  for (auto& b : B) b = N - 1 - b;

  // いもす法で区間に対する操作を行うための準備
  rep(i, A.size()) imos[A[i]] += 1;  // 左からのスキャンで見つけた位置にマーク
  rep(i, B.size()) imos[B[i] + 1] -=
      1;  // 右からのスキャンで見つけた位置の次の位置にマーク解除

  // 左と右の両方のスキャンで見つかった位置には'o'を配置
  rep(i, A.size()) if (A[i] == B[i]) S[A[i]] = 'o';

  // いもす法による累積和を計算
  rep(i, N) imos[i + 1] += imos[i];

  // 累積和が0の位置にある'?'は'.'に変更（'o'を配置できない位置）
  rep(i, N) if (S[i] == '?' && imos[i] == 0) S[i] = '.';

  cout << S << "\n";  // 結果を出力
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);      // 入出力の高速化設定
  rep(i, 1) testcase();  // テストケースを実行
  return 0;
}
