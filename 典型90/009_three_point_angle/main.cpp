#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
class Point {
public:
	double x, y;
	Point operator-(const Point& p) const {
		return Point{x - p.x, y - p.y};
	}
};
vector<Point> A;

double get_angle(Point p) {
	double angle = atan2(p.y, p.x);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

double get_angle_between(double a, double b) {
	double diff = b - a;
	if (diff < 0)
		diff += 2 * M_PI;
	if (diff > M_PI)
		diff = 2 * M_PI - diff;
	return diff;
}

double radians_to_degrees(double rad) {
	return rad * 180.0 / M_PI;
}

int	main()
{
	cin >> N;
	A.resize(N);
	for (int i=0; i<N; i++) {
		cin >> A[i].x >> A[i].y;
	}
	double ans = 0;

	for (int i=0; i<N; i++) {
		vector<double> deflection;
		// 偏角を前計算してソートする
		// 二分法を使うために、ソート済み配列が必要 ∴ベクトルではなく、偏角を使う
		for (int j=0; j<N; j++) {
			if (i == j)
				continue;
			Point vec = {A[j].x - A[i].x, A[j].y - A[i].y};
			double angle = get_angle(vec);
			deflection.push_back(angle);
		}
		sort(deflection.begin(), deflection.end());
		// 点A,Bを全探索し、Cを二分法で探索することでN^3を(N^2)*logNにする
		for (int j=0; j<N; j++) {
			if (i == j)
				continue;
			Point base_vec = {A[j].x - A[i].x, A[j].y - A[i].y};
			Point inv_vec = {-base_vec.x, -base_vec.y};
			double base_angle = get_angle(base_vec);
			double inv_angle = get_angle(inv_vec);
			// lower_boundはkey以上の中でできるだけ左側
			// upper_boundはkeyより大きいなかでできるだけ左側
			auto idx = lower_bound(
				deflection.begin(), deflection.end(), inv_angle
			) - deflection.begin();
			ans = max(ans, get_angle_between(base_angle, deflection[idx % (N-1)]));
			ans = max(ans, get_angle_between(base_angle, deflection[(idx+1) % (N-1)]));
		}
	}
	// double型の出力時に桁数を指定する 勝手に丸められてしまうため
	cout << fixed << setprecision(8) << radians_to_degrees(ans) << endl;
	return 0;
}