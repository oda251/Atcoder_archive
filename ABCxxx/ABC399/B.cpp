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
#define cerr_time() \
  cerr << "time: " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
/*####################################################*/
int main() {
  int N;
  cin >> N;
  vector<tuple<int, int, int>> P(N);  // id, score, rank
  rep(i, N) { get<0>(P[i]) = i; }
  rep(i, N) { cin >> get<1>(P[i]); }
  sort(P.begin(), P.end(),
       [](auto a, auto b) { return get<1>(a) > get<1>(b); });
  int rank = 0;
  int same = 1;
  rep(i, N) {
    if (i > 0 && get<1>(P[i]) == get<1>(P[i - 1])) {
      same++;
    } else {
      rank += same;
      same = 1;
    }
    get<2>(P[i]) = rank;
  }
  sort(P.begin(), P.end(),
       [](auto a, auto b) { return get<0>(a) < get<0>(b); });
  rep(i, N) { cout << get<2>(P[i]) << endl; }
  return 0;
}