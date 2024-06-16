#include "type.cpp"

void do_clane(Data &data, Clane &cln) {
	if (cln.has_con >= 0 && cln.pos.y == cln.has_con / N && cln.pos.x == N - 1) {
		if (!cln.Q(data)) {
			cln.dot(data);
		}
	} else if (cln.P(data)) {
	} else {
		if (cln.pos.y == 4 && cln.pos.x > 1) {
			if (!cln.L(data)) {
				cln.dot(data);
			}
		} else if (cln.pos.x == 4) {
			if (!cln.D(data)) {
				cln.dot(data);
			}
		} else if (cln.pos.y == 0) {
			if (!cln.R(data)) {
				cln.dot(data);
			}
		} else {
			if (cln.has_con < 0) {
				if (!cln.L(data)) {
					if (!cln.U(data)) {
						cln.dot(data);
					}
				}
			} else {
				if (cln.pos.x == 0) {
					if (!cln.U(data)) {
						if (!cln.R(data)) {
							cln.dot(data);
						}
					}
				} else {
					if (!cln.U(data)) {
						cln.dot(data);
					}
				}
			}
		}
	}
}

void sim(Data &data) {
	while (data.turn < 10000) {
		for (auto &cln: data.clanes) {
			do_clane(data, cln);
		}
		data.proceed();
		if (data.remain_con == 0)
			break;
	}
}

int main() {
	Data data;
	data.input();
	sim(data);
	data.output();
	return 0;
}
