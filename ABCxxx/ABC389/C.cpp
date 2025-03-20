#include <bits/stdc++.h>
using namespace std;

struct Snake {
  long head_pos;
  long length;
};

int main() {
  vector<Snake> snakes;
  long Q;
  long st = 0;
  cin >> Q;
  for (long i = 0; i < Q; i++) {
    long t, x;
    cin >> t;
    switch (t) {
      case 1:
        cin >> x;
        switch (snakes.size()) {
          case 0:
            snakes.push_back({0, x});
            break;
          default:
            Snake& last_snake = snakes.back();
            snakes.push_back({last_snake.head_pos + last_snake.length, x});
            break;
        }
        break;
      case 2:
        st++;
        break;
      default:
        cin >> x;
        cout << snakes[st + x - 1].head_pos - snakes[st].head_pos << endl;
        break;
    }
  }
}