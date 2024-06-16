#include "type.cpp"

bool min_export(Data &data, Clane &cln) {
	if (cln.pos.y = cln.has_con / N && cln.pos.x == N - 1) {
		return cln.Q(data);
	} else {
		if (cln.pos.y < cln.has_con / N) {
			return (cln.D(data) || cln.R(data));
		} else if (cln.pos.y > cln.has_con / N) {
			return (cln.U(data) || cln.R(data));
		} else {
			return cln.R(data);
		}
	}
}

void do_clane(Data &data, Clane &cln) {
	if (cln.has_con < 0) {
		if (!cln.P(data)) {
			if (cln.pos.x == 4) {
				if (!cln.D(data)) {
					cln.dot(data);
				}
			} else if (cln.pos.y == 0) {
				if (!cln.R(data)) {
					cln.dot(data);
				}
			} else {
				if (!cln.L(data)) {
					if (!cln.U(data)) {
						cln.dot(data);
					}
				}
			}
		}
	} else {
		if (!min_export(data, cln)) {
			cln.dot(data);
			return;
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
