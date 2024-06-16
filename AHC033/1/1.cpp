#include "type.cpp"

bool min_export(Data &data, Clane &cln) {
	if (cln.pos.y = cln.has_con / N && cln.pos.x == 0) {
		return cln.Q(data);
	}
	if (cln.pos.y < cln.has_con / N) {
		if (!cln.D(data)) {
			return cln.R(data);
		}
	} else if (cln.pos.y > cln.has_con / N) {
		if (!cln.U(data)) {
			return cln.R(data);
		}
	}
	return cln.R(data);
}

void do_clane(Data &data, Clane &cln) {
	if (cln.has_con < 0) {
		if (!cln.P(data)) {
			if (!cln.L(data)) {
				if (!cln.D(data)) {
					cln.dot(data);
				}
			}
		}
	} else {
		
	}
	return;
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
