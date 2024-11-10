#include "atc.hpp"

double T, L, X, Y, Q;
vector<double> E;
auto input = []() {
  cin >> T >> L >> X >> Y >> Q;
  E.resize(Q);
  for (int i = 0; i < Q; i++) {
    cin >> E[i];
  }
  return 0;
}();
struct Point {
  double x, y, z;
  Point() : x(0), y(0), z(0) {}
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
};
int main() {
  for (int i=0; i<Q; i++) {
    double t = E[i] / T;
    double rad = 2 * M_PI * t;
    double x = 0;
    double y = -L / 2 * sin(rad);
    double z = L/2 - L/2 * cos(rad);
    Point p(x, y, z);
    double adjacent = sqrt(pow(p.x - X, 2) + pow(p.y - Y, 2));
    double opposite = p.z;
    double ans = atan2(opposite, adjacent) * 180 / M_PI;
    cout << fixed << setprecision(9) << ans << endl;
  }
}
