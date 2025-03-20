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

enum Query {
  Move = 1,
  Swap = 2,
  Check = 3
};

int main() {
  ll N, Q;
  cin >> N >> Q;
  // 鳩がいる巣のインデックス
  vector<ll> belong_idx(N);
  // 巣の番号とインデックスの対応
  vector<ll> nest_to_idx(N);
  vector<ll> idx_to_nest(N);
  vector<vector<ll>> nests(N); 
  rep(i, N) {
    belong_idx[i] = i;
    nest_to_idx[i] = i;
    idx_to_nest[i] = i;
    nests[i].push_back(i);
  }
  rep(i, Q) {
    int q;
    cin >> q;
    switch (q) {
      case 1: {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        ll dest_idx = nest_to_idx[b];
        belong_idx[a] = dest_idx;
      }
      break;
      case 2: {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        ll a_idx = nest_to_idx[a];
        ll b_idx = nest_to_idx[b];
        nest_to_idx[a] = b_idx;
        nest_to_idx[b] = a_idx;
        idx_to_nest[a_idx] = b;
        idx_to_nest[b_idx] = a;
      }
      break;
      case 3: {
        ll a;
        cin >> a;
        a--;
        cout << idx_to_nest[belong_idx[a]] + 1 << endl;
      }
      break;
    }
  }
  return 0;
}