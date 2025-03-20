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
auto input = []() { return 0; }();

int main() {
  int N;
  cin >> N;
  vector<vector<char>> grid(N, vector<char>(N));
  for (int i = 1; i <= N; i++) {
    int j = N + 1 - i;
    if (i <= j) {
      char color;
      if (i % 2 == 1) {
        color = '#';
      } else {
        color = '.';
      }
      int s = i - 1 < j - 1 ? i - 1 : j - 1;
      int e = i - 1 < j - 1 ? j - 1 : i - 1;
      for (int k = s; k <= e; k++) {
        grid[i - 1][k] = color;
        grid[j - 1][k] = color;
        grid[k][i - 1] = color;
        grid[k][j - 1] = color;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << grid[i][j];
    }
    cout << '\n';
  }
  cout << endl;

  return 0;
}