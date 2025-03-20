#include <bits/stdc++.h>
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
ll N, Q;
vector<pair<ll, ll>> LR;
vector<ll> q;
auto input = []() {
  cin >> N;
  LR.resize(N);
  rep(i, N) {
    cin >> LR[i].first >> LR[i].second;
  }
  cin >> Q;
  q.resize(Q);
  rep(i, Q) {
    cin >> q[i];
  }
  return 0;
}();

int main() {
  
  return 0;
}