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
time_t start = clock();
#define cerr_time() cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
/*####################################################*/
int main() {
  int N;
  cin >> N;
  vector<ll> A(N);
  ll sum = 0;
  rep(i, N) {
    cin >> A[i];
    sum ^= A[i];
  }
  rep(i, N) cout << (sum ^ A[i]) << (i == N - 1 ? '\n' : ' ');
  cout << flush;
  return 0;
}
