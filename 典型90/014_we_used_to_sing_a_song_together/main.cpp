#include <bits/stdc++.h>
using namespace std;
using ll = long long;
auto boostio = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return nullptr;
}();

int N;
vector<pair<ll, int>> A, B;
auto input = []() {
  cin >> N;
  A.resize(N);
  B.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i].first;
    A[i].second = i;
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i].first;
    B[i].second = i;
  }
  return nullptr;
}();

int main() {
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ans += abs(A[i].first - B[i].first);
  }
  cout << ans << endl;
}