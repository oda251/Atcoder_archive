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
auto input = []() { return 0; }();

int main() {
  int N;
  cin >> N;
  int cnt = 1;
  int A = -1, B = -1;
  rep(i, N) {
    cin >> B;
    if (B == A) {
      cnt++;
      if (cnt == 3) {
        cout << "Yes" << endl;
        return 0;
      }
    } else {
      cnt = 1;
    }
    A = B;
  }
  cout << "No" << endl;
  return 0;
}