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
struct Trie {
  Trie* next[26 + 10];
  int registered;
  Trie() {
    rep(i, 26 + 10) next[i] = nullptr;
    registered = -1;
  }
};
int serialize(char c) {
  if (isdigit(c))
    return c - '0' + 26;
  else
    return c - 'a';
}
bool insert(Trie& root, string& s, int date) {
  Trie* node = &root;
  for (char c : s) {
    int idx = serialize(c);
    if (node->next[idx] == nullptr) {
      node->next[idx] = new Trie();
    }
    node = node->next[idx];
  }
  if (node->registered != -1)
    return false;
  else
    node->registered = date;
  return true;
}
int main() {
  int N;
  cin >> N;
  Trie root;
  rep(i, N) {
    string s;
    cin >> s;
    if (insert(root, s, i + 1)) {
      cout << i + 1 << '\n';
    }
  }
  cout << flush;
  return 0;
}