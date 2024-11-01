#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
static const bool Booster = [](){
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
class Point {
	public:
		int x, y;
		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point &src) : x(src.x), y(src.y) {}
		struct Hash {
			size_t operator()(const Point &p) const {
				return hash<int>()(p.x) ^ hash<int>()(p.y);
			}
		};
		Point &operator=(const Point &src) {
			x = src.x;
			y = src.y;
			return *this;
		}
		Point operator+(const Point &src) const {
			return Point(x + src.x, y + src.y);
		}
		Point operator-(const Point &src) const {
			return Point(x - src.x, y - src.y);
		}
		Point operator*(const Point &src) const {
			return Point(x * src.x, y * src.y);
		}
		Point operator/(const Point &src) const {
			return Point(x / src.x, y / src.y);
		}
		Point &operator++(void) {
			x++;
			y++;
			return *this;
		}
		Point operator++(int) {
			Point tmp(*this);
			operator++();
			return tmp;
		}
		Point &operator--(void) {
			x--;
			y--;
			return *this;
		}
		Point operator--(int) {
			Point tmp(*this);
			operator--();
			return tmp;
		}
		bool operator==(const Point &src) const {
			return x == src.x && y == src.y;
		}
		bool operator!=(const Point &src) const {
			return x != src.x || y != src.y;
		}
		bool operator>(const Point &src) const {
			return x > src.x && y > src.y;
		}
		bool operator<(const Point &src) const {
			return x < src.x && y < src.y;
		}
		bool operator>=(const Point &src) const {
			return x >= src.x && y >= src.y;
		}
		bool operator<=(const Point &src) const {
			return x <= src.x && y <= src.y;
		}
};
ostream& operator<<(ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}
#define HERE cerr << "HERE" << endl
#define FOO cerr << "FOO" << endl
#define BAR cerr << "BAR" << endl
#define HOGE cerr << "HOGE" << endl
#define FUGA cerr << "FUGA" << endl
#define PIYO cerr << "PIYO" << endl
#define DEBUG(x) cerr << #x << ": " << x << endl
#define EXIT cerr << "EXIT" << endl; exit(0);
#define INF LLONG_MAX
#define range(index, a, b) for(ll index=a; i<b; i++)
#define rrange(index, a, b) for(ll index=a; i>=b; i--)
#define all(a) (a).begin(), (a).end()
