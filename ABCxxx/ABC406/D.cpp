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
  int H, W, N;
  cin >> H >> W >> N;
  vector<int> x(H), y(W);
  vector<set<int>> x_dust(H);
  vector<set<int>> y_dust(W);
  rep(i, N) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    x[a]++;
    y[b]++;
    x_dust[a].insert(b);
    y_dust[b].insert(a);
  }
  int Q;
  cin >> Q;
  rep(i, Q) {
    int type, pos;
    cin >> type >> pos;
    pos--;
    switch (type) {
      case 1:
        cout << x[pos] << '\n';
        for (int b : x_dust[pos]) {
          y[b]--;
          y_dust[b].erase(pos);
        }
        x[pos] = 0;
        x_dust[pos].clear();
        break;
      case 2:
        cout << y[pos] << '\n';
        for (int a : y_dust[pos]) {
          x[a]--;
          x_dust[a].erase(pos);
        }
        y[pos] = 0;
        y_dust[pos].clear();
        break;
    }
  }
  cout << flush;
  return 0;
}