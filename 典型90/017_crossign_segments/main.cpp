#include "atc.hpp"
int N, M;
struct Edge {
  int l, r;
};
vector<Edge> E;
struct Point {
  int l, r;
  int lIsLargerThanHereCount;
  Point() : l(0), r(0) {}
};
vector<Point> P;
auto input = []() {
  cin >> N >> M;
  E.resize(M);
  P.resize(N);
  for (int i = 0; i < M; i++) {
    cin >> E[i].l >> E[i].r;
    P[E[i].l].l++;
    P[E[i].r].r++;
  }
  sort(E.begin(), E.end(), [](Edge a, Edge b) {
    return a.r < b.r;
  });
  P[N-1].lIsLargerThanHereCount = 0;
  for (int i = N-2; i >= 0; i--) {
    P[i].lIsLargerThanHereCount = P[i+1].l + P[i+1].lIsLargerThanHereCount;
  }
  return 0;
}();
ll one() {
  ll ans = 0;
  for (int s=0; s<N; s++) {
    ans += P[s].r * P[s].lIsLargerThanHereCount;
  }
  return ans;
}
ll two() {
  ll ans = 0;
  for (int i=0; i<N; i++) {
    int size = P[i].l + P[i].r;
    ans += size * (size - 1) / 2;
  }
  return ans;
}
ll three() {
  // いやだ
}
int main() {

} // main