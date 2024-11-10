#include "atc.hpp"
#include <atcoder/modint>
#include "comb.hpp"
using mint = atcoder::modint1000000007;
int N;
auto input = []() {
    cin >> N;
    return 0;
}();
Comb<mint> C(N);
mint solve(int k) {
  mint ans = 0;
  // 選ぶボールの数c
  for (int c = 1; c <= N; c++) {
    if (N-(c-1)*(k-1) <= 0) break;
    mint tmp = C.exec(N-(c-1)*(k-1), c);
    if (tmp == 0) break;
    ans += tmp;
  }
  return ans;
}
int main() {
  // 任意の2つのボールの差がk以上
  for (int k=1; k<=N; k++) {
    mint ans = solve(k);
    if (ans == 0) break;
    cout << ans.val() << endl;
  }
  cerr_time();
  return 0;
}