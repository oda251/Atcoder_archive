#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main() {
// input
int N, A, B, C;
cin >> N >> A >> B >> C;
// solve
int ans = INT_MAX;
for (int a=0; a<=min(N/A, 9999); a++) {
  for (int b=0; b<=min((N-a*A)/B, 9999); b++) {
    int c = (N-a*A-b*B)/C;
    if (c > 9999) continue;
    if (a*A+b*B+c*C == N) {
      ans = min(ans, a+b+c);
    }
  }
}
cout << ans << endl;
return 0;
} // main