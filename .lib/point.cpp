class Point {
	public:
		int x;
		int y;
		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point &src) : x(src.x), y(src.y) {}
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
