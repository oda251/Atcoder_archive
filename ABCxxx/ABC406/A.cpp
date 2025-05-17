#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, l, r) for (int i = l; i < r; ++i)
#define all(x) (x).begin(), (x).end()
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
time_t start = clock();
#define cerr_time() cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
/*####################################################*/
int main() {
  int A, B, C, D;
  cin >> A >> B >> C >> D;
  if (A > C) {
    cout << "Yes" << endl;
    return 0;
  }
  if (A < C) {
    cout << "No" << endl;
    return 0;
  }
  if (B > D) {
    cout << "Yes" << endl;
    return 0;
  } else {
    cout << "No" << endl;
    return 0;
  }
  return 0;
}