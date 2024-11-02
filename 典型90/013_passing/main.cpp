#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

ll N, M;
struct Edge {
  ll to, cost;
};
class City {
 public:
  ll id;
  vector<Edge> edge;
};
vector<City> cities;
auto init = [](){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> N >> M;
  cities.resize(N);
  for (ll i=0; i<M; i++) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--; b--;
    cities[a].edge.push_back({b, c});
    cities[b].edge.push_back({a, c});
  }
  return 0;
}();

vector<ll> dijkstra(ll start) {
  vector<ll> dists(N, LLONG_MAX);
  dists[start] = 0;
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, start});
  while (!pq.empty()) {
    auto [dist, from] = pq.top();
    pq.pop();
    for (auto [to, cost] : cities[from].edge) {
      if (dists[to] > dist + cost) {
        dists[to] = dist + cost;
        pq.push({dists[to], to});
      }
    }
  }
  return dists;
}

int main() {
  vector<ll> dist_from_s = dijkstra(0);
  vector<ll> dist_from_g = dijkstra(N-1);
  for (ll i=0; i<N; i++) {
    cout << dist_from_s[i] + dist_from_g[i] << endl;
  }
}
