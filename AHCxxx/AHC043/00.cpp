#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define COST_STATION 5000
#define COST_RAIL 100
auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
/*####################################################*/
struct Point {
  ll i, j;
  Point() : i(0), j(0) {}
  Point(ll i, ll j) : i(i), j(j) {}
};
struct Person {
  Point s, t;
  Person() : s(Point()), t(Point()) {}
};
struct Data {
  // N: grid size, fixed to 50
  // M: number of people, 50 <= M <= 100
  // K: initial funds, 11000 <= K <= 20000
  // T: number of turns, fixed to 800
  ll N, M, K, T;
  vector<Person> people;
};
enum class PutType {
  Station = 0,
  Horizontal = 1,
  Vertical = 2,
  LeftToBot = 3,
  LeftToTop = 4,
  TopToRight = 5,
  BotToRight = 6,
  None = -1
};
/*####################################################*/
auto data = []() {
  Data data;
  cin >> data.N >> data.M >> data.K >> data.T;
  data.people.resize(data.M);
  rep(i, data.M) {
    cin >> data.people[i].s.i >> data.people[i].s.j;
    cin >> data.people[i].t.i >> data.people[i].t.j;
  }
  return data;
}();
/*####################################################*/

int main() {

  return 0;
}