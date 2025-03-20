#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#line 5 "atc.hpp"
static const bool Booster = []() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return true;
}();
using namespace std;
typedef long long ll;
int _;
clock_t start_time = clock();
void cerr_time(void) {
  cerr << "time: " << (double)(clock() - start_time) / 1000 << "ms" << endl;
}
#define HERE cerr << "HERE" << endl
#define HOGE cerr << "HOGE" << endl
#define FUGA cerr << "FUGA" << endl
#define PIYO cerr << "PIYO" << endl
#define FOO cerr << "FOO" << endl
#define BAR cerr << "BAR" << endl
#define DEBUG(x) cerr << #x << ": " << x << endl
#define EXIT              \
  cerr << "EXIT" << endl; \
  exit(0);
#define INF LLONG_MAX
#define range(index, a, b) for (ll index = a; i < b; i++)
#define rrange(index, a, b) for (ll index = a; i >= b; i--)
#define all(a) (a).begin(), (a).end()
#line 3 "graph.hpp"
struct Node {
  vector<size_t> edgeTo;
  vector<size_t> edgeFrom;
};
struct SccNode {
  size_t id;
  vector<size_t> nodesContain;
  vector<size_t> edgeTo;
  vector<size_t> edgeFrom;
  SccNode() : id(0) {}
};
// SccGraph
class SccGraph {
 public:
  size_t nodeSize, edgeSize;
  vector<SccNode> nodes;
  SccGraph();
  SccGraph(size_t max_node_size);
  SccNode& operator[](size_t index) { return nodes[index]; }
};
SccGraph::SccGraph() {}
SccGraph::SccGraph(size_t max_node_size) : nodes(max_node_size) {}
// Graph
class Graph {
 private:
  bool isSCCed;

 public:
  size_t nodeSize, edgeSize;
  vector<Node> nodes;
  SccGraph sccGraph;
  Graph() : isSCCed(false), nodeSize(0), edgeSize(0) {};
  Graph(size_t node_size, size_t edge_size)
      : isSCCed(false),
        nodeSize(node_size),
        edgeSize(edge_size),
        nodes(node_size){};
  SccGraph& scc();
  void resize(size_t size);

  Node& operator[](size_t index) { return nodes[index]; }
};
// Graph implementation
SccGraph& Graph::scc() {
  isSCCed = true;
  sccGraph.nodes.resize(nodeSize);
  vector<size_t> order;
  vector<bool> visited(nodeSize, false);
  {
    function<void(size_t)> dfs = [&](size_t node) -> void {
      visited[node] = true;
      for (auto next : nodes[node].edgeTo) {
        if (!visited[next]) {
          dfs(next);
        }
      }
      order.push_back(node);
    };
    for (size_t i = 0; i < nodeSize; i++) {
      if (!visited[i]) {
        dfs(i);
      }
    }
  }
  {
    size_t groupId = 0;
    fill(visited.begin(), visited.end(), false);
    reverse(order.begin(), order.end());
    for (size_t cur : order) {
      SccNode& scc_node = sccGraph[groupId];
      if (visited[cur]) continue;
      queue<size_t> que;
      que.push(cur);
      visited[cur] = true;
      while (!que.empty()) {
        size_t node = que.front();
        que.pop();
        scc_node.nodesContain.push_back(node);
        for (auto next : nodes[node].edgeFrom) {
          if (!visited[next]) {
            visited[next] = true;
            que.push(next);
          }
        }
      }
      groupId++;
      sccGraph.nodeSize = groupId;
    }
  }
  return sccGraph;
}
void Graph::resize(size_t size) {
  nodeSize = size;
  nodes.resize(size);
}
#line 4 "main.cpp"
int N, M;
Graph graph;
auto input = [](){
  cin >> N >> M;
  graph.resize(N);
  for (int i=0; i<M; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    graph[a].edgeTo.push_back(b);
    graph[b].edgeFrom.push_back(a);
  }
  return 0;
}();
auto solve = []() {
  auto sccGraph = graph.scc();
  ll ans = 0;
  for (auto& sccNode : sccGraph.nodes) {
    ans += sccNode.nodesContain.size() * (sccNode.nodesContain.size() - 1) / 2;
  }
  return ans;
};
int main() {
  cout << solve() << endl;
  return 0;
}
