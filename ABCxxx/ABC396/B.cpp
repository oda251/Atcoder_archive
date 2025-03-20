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
auto input = []() {
  return 0;
}();

int main() {
  int Q;
  cin >> Q;
  deque<int> x(100, 0);
  rep(i, Q) {
    int q;
    cin >> q;
    switch(q) {
      case 1: {
        int c;
        cin >> c;
        x.push_back(c);
        break;
      }
      case 2: {
        int c;
        c = x.back();
        x.pop_back();
        cout << c << endl;
        break;
      }
    }
  }
  return 0;
}