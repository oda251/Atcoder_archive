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
class UnionFind {
 public:
  vector<int> par;
  vector<int> size;
  UnionFind(int n) : par(n), size(n, 1) {
    for (int i = 0; i < n; i++) par[i] = i;
  }
  int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }
  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (size[x] < size[y]) swap(x, y);
    par[y] = x;
    size[x] += size[y];
    return true;
  }
  int getSize(int x) { return size[find(x)]; }
};
int main() {
  int N, M;
  cin >> N >> M;
  bool ans = true;
  if (N != M) {
    ans = false;
  }
  UnionFind uf(N);
  vector<pair<int, int>> A(N, {-1, -1});
  rep(i, M) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    if (A[x].first == -1) {
      A[x].first = y;
    } else if (A[x].second == -1) {
      A[x].second = y;
    } else {
      ans = false;
    }
    if (A[y].second == -1) {
      A[y].second = x;
    } else if (A[y].first == -1) {
      A[y].first = x;
    } else {
      ans = false;
    }
    uf.unite(x, y);
  }
  if (uf.getSize(0) != N) {
    ans = false;
  }
  cout << (ans ? "Yes" : "No") << endl;
  return 0;
}
