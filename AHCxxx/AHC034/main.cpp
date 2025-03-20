#include "type.cpp"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

void make_plan_5(Data &d) {
	deque<Square5*> arr = deque<Square5*>(16);
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			arr[i*4+j] = &(d.map.getPoint5(Point(j*5, i*5)));
		}
	}
	sort(arr.begin(), arr.end(), [](Square5* a, Square5* b) {
		return (*a).totalHeight > (*b).totalHeight;
	});
	int total = 0;
	d.plan5.push_back(arr[0]);
	total += arr[0]->totalHeight;
	arr.pop_front();
	while (!arr.empty()) {
		label:
		int min = 10000;
		int tgt = 0;
		for (int i=arr.size() - 1; i>=0; i--) {
			int tmp = total + arr[i]->totalHeight;
			if (tmp > 0 && tmp < min) {
				min = tmp;
				tgt = i;
			}
		}
		if (min != 10000) {
			d.plan5.push_back(arr[tgt]);
			total += arr[tgt]->totalHeight;
			arr.erase(arr.begin() + tgt);
			goto label;
		}
		if (arr.empty())
			break;
		d.plan5.push_back(arr[0]);
		total += arr[0]->totalHeight;
		arr.pop_front();
	}
}

void move_point(Data &d, Point p) {
	auto &car = d.car;
	auto &map = d.map;
	auto &plan = d.plan5;
	while (true) {
		if (car.pos == p)
			break ;
		if (map.getPoint(car.pos).height > 0) {
			d.load(map.getPoint(car.pos).height);
		} else if (map.getPoint(car.pos).height < 0) {
			if (!d.unload(map.getPoint(car.pos).height) && car.gravel > 0) {
				d.unload(car.gravel);
			}
		}
		if (car.pos.x < p.x) {
			d.move(RIGHT);
		} else if (car.pos.x > p.x) {
			d.move(LEFT);
		} else if (car.pos.y < p.y) {
			d.move(DOWN);
		} else if (car.pos.y > p.y) {
			d.move(UP);
		}
	}
	if (map.getPoint(car.pos).height > 0) {
		d.load(map.getPoint(car.pos).height);
	} else if (map.getPoint(car.pos).height < 0) {
		if (!d.unload(map.getPoint(car.pos).height) && car.gravel > 0) {
			d.unload(car.gravel);
		}
	}
}

void clean_5(Data &d, Square5 &sq) {
	auto &car = d.car;
	auto &map = d.map;
	Point pos5 = Point(car.pos.x % 5, car.pos.y % 5);
	if (pos5 == Point(0, 0)) {
	while (pos5 != Point(4, 4)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(4, 4)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		} else {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		}
		if (pos5 == Point(4, 4)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(4, 4)) {
	while (pos5 != Point(0, 0)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(0, 0)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		} else {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		}
		if (pos5 == Point(0, 0)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(0, 4)) {
	while (pos5 != Point(4, 0)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(4, 0)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		} else {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y - 1));
			}
		}
		if (pos5 == Point(4, 0)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}} else if (pos5 == Point(4, 0)) {
	while (pos5 != Point(0, 4)) {
		pos5 = Point(car.pos.x % 5, car.pos.y % 5);
		if (pos5 == Point(0, 4)) {
			break ;
		}
		if (pos5.y % 2 == 0) {
			if (pos5.x > 0) {
				move_point(d, Point(car.pos.x - 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		} else {
			if (pos5.x < 4) {
				move_point(d, Point(car.pos.x + 1, car.pos.y));
			} else {
				move_point(d, Point(car.pos.x, car.pos.y + 1));
			}
		}
		if (pos5 == Point(0, 4)) {
			break ;
		}
		if (sq.remain_sq == 0) {
			break ;
		}
	}}
}
Point choose_point(Data &d, Point pos5) {
	Point p1 = pos5;
	Point p2 = Point(pos5.x + 4, pos5.y);
	Point p3 = Point(pos5.x, pos5.y + 4);
	Point p4 = Point(pos5.x + 4, pos5.y + 4);
	int dist1 = abs(d.car.pos.x - p1.x) + abs(d.car.pos.y - p1.y);
	int dist2 = abs(d.car.pos.x - p2.x) + abs(d.car.pos.y - p2.y);
	int dist3 = abs(d.car.pos.x - p3.x) + abs(d.car.pos.y - p3.y);
	int dist4 = abs(d.car.pos.x - p4.x) + abs(d.car.pos.y - p4.y);
	if (dist1 <= dist2 && dist1 <= dist3 && dist1 <= dist4) {
		return p1;
	} else if (dist2 <= dist1 && dist2 <= dist3 && dist2 <= dist4) {
		return p2;
	} else if (dist3 <= dist1 && dist3 <= dist2 && dist3 <= dist4) {
		return p3;
	} else {
		return p4;
	}
	return p1;
}
void do_plan5(Data &d) {
	auto &car = d.car;
	auto &map = d.map;
	auto &plan = d.plan5;
	label:
	auto sq = plan.front();
	plan.pop_front();
	if ((*sq).remain_sq == 0) {
		if (plan.empty())
		{
			return ;
		}
		goto label;
	}
	plan.push_back(sq);
	Point nex = choose_point(d, (*sq).pos);
	move_point(d, nex);
	clean_5(d, (*sq));
}

void all_clean(Data &data, int turn) {
	auto &map = data.map;
	auto &car = data.car;
	bool reversed = false;
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
}

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
	make_plan_5(data);
	for (turn=0; ; turn++) {
		do_plan5(data);
		if (data.is_finished())
			break ;
	}
	cerr << turn << endl;
	cout << data.ans << flush;
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
