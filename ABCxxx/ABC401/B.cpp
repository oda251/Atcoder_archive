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
  int N;
  cin >> N;
  int cnt = 0;
  bool login = false;
  rep(i, N) {
    string S;
    cin >> S;
    if (S == "login") {
      login = true;
    } else if (S == "logout") {
      login = false;
    } else if (S == "public") {
    } else if (S == "private") {
      if (!login) {
        cnt++;
      }
    }
  }
  cout << cnt << endl;
  return 0;
}
