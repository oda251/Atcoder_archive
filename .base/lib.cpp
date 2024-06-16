#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int _;
clock_t start_time = clock();
void cerr_time(void) {
	cerr << "time: " << (double)(clock() - start_time) / 1000 << "ms" << endl;
}
class Point {
	public:
		int x;
		int y;
		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point &src) : x(src.x), y(src.y) {}
		void move(int a, int b) { x+=a; y+=b; }
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
typedef enum e_dir {
	UP,
	RIGHT,
	DOWN,
	LEFT,
} t_dir;
#define HERE cerr << "HERE" << endl
#define HOGE cerr << "HOGE" << endl
#define FUGA cerr << "FUGA" << endl
#define PIYO cerr << "PIYO" << endl
#define DEBUG(x) cerr << #x << ": " << x << endl
#define EXIT cerr << "EXIT" << endl; exit(0);
#define INF LLONG_MAX
#define range(index, a, b) for(ll index=a; i<b; i++)
#define rrange(index, a, b) for(ll index=a; i>=b; i--)
#define all(a) (a).begin(), (a).end()
