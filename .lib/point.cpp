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
		struct Hash {
			size_t operator()(const Point &p) const {
				return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
			}
		};
};
ostream& operator<<(ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}