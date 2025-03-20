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
  int N;
  ll K;
  cin >> N >> K;
  vector<ll> A(N);
  vector<ll> B(N);
  rep(i, N) {
    cin >> A[i];
  }
  rep(i, N) {
    cin >> B[i];
  }
  ll cnt = 0;
  rep(i, N) {
    cnt += abs(A[i] - B[i]);
  }
  if (cnt > K) {
    cout << "No" << endl;
  } else if ((K - cnt) % 2 == 0) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}