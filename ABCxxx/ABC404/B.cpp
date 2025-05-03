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
  vector<vector<bool>> S1(N, vector<bool>(N));
  vector<vector<bool>> S2(N, vector<bool>(N));
  vector<vector<bool>> S3(N, vector<bool>(N));
  vector<vector<bool>> S4(N, vector<bool>(N));
  vector<vector<bool>> T(N, vector<bool>(N));
  int cnt[4] = {0, 1, 2, 3};
  rep(i, N) {
    string s;
    cin >> s;
    rep(j, N) {
      S1[i][j] = s[j] == '#';
    }
  }
  rep(i, N) rep(j, N) {
    S2[j][N - 1 - i] = S1[i][j];
  }
  rep(i, N) rep(j, N) {
    S3[j][N - 1 - i] = S2[i][j];
  }
  rep(i, N) rep(j, N) {
    S4[j][N - 1 - i] = S3[i][j];
  }
  rep(i, N) {
    string s;
    cin >> s;
    rep(j, N) {
      T[i][j] = s[j] == '#';
      if (S1[i][j] != T[i][j]) {
        cnt[0]++;
      }
      if (S2[i][j] != T[i][j]) {
        cnt[1]++;
      }
      if (S3[i][j] != T[i][j]) {
        cnt[2]++;
      }
      if (S4[i][j] != T[i][j]) {
        cnt[3]++;
      }
    }
  }
  int ans = min(cnt[0], min(cnt[1], min(cnt[2], cnt[3])));
  cout << ans << endl;
  return 0;
}