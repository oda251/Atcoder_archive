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
#define cerr_time() \
  cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
/*####################################################*/
int main() {
  int N, M;
  cin >> N >> M;
  vector<ll> C(N);
  rep(i, N) cin >> C[i];
  vector<vector<int>> A(M);
  rep(i, M) {
    int k;
    cin >> k;
    A[i].resize(k);
    rep(j, k) {
      cin >> A[i][j];
      A[i][j]--;
    }
  }
  // input end

  int source = 0;
  int sink = N + M + 1;
  atcoder::mcf_graph<int, ll> g(sink + 1);
  rep(i, M) { g.add_edge(source, i + 1, 2, 0); }
  rep(i, M) {
    for (int zoo : A[i]) {
      g.add_edge(i + 1, zoo + M + 1, INT_MAX, 0);
    }
  }
  rep(i, N) { g.add_edge(i + M + 1, sink, INT_MAX, C[i]); }
  auto result = g.flow(source, sink, 2 * M);
  cout << result.second << endl;
  return 0;
}