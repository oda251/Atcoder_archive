#include <bits/stdc++.h>
using namespace std;

int main() {
  long X;

  long n = 1;
  long sum = 1;
  cin >> X;
  while (sum != X) {
    n++;
    sum *= n;
    if (sum > X) {
      cout << "excessed" << endl;
      break;
    }
  }
  cout << n << endl;
}
