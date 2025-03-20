#include "type.cpp"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

int main() {
	clock_t start = clock();
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Data data;
	auto& car = data.car;
	auto& map = data.map;
	bool reversed = false;
	int turn;
	for (turn=0; ; turn++) {
		auto h = map.getPoint(car.pos).height;
		if (h > 0) {
			data.load(h);
		} else if (h < 0) {
			if (!data.unload(h) && car.gravel > 0) {
				data.unload(car.gravel);
			}
		}
		if (reversed == false) {
			if (car.pos.y % 2 == 0) {
				if (!data.move(RIGHT) && !data.move(DOWN)) {
					cerr << "error" << endl;
					exit(1);
				}
			} else {
				if (!data.move(LEFT) && !data.move(DOWN)) {
					reversed = true;
				}
			}
		} else {
			if (car.pos.y % 2 == 0) {
				if (!data.move(LEFT) && !data.move(UP)) {
					reversed = false;
				}
			} else {
				if (!data.move(RIGHT) && !data.move(UP)) {
					cerr << "error" << endl;
					exit(1);
				}
			}
		}
		if (data.is_finished())
			break ;
	}
	cerr << turn << endl;
	cout << data.ans << flush;
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
