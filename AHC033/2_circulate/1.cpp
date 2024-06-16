#include "type.cpp"

void do_circulate(Data &data, Clane &cln,
		function<void(Data &, Clane &)> else_f = [](Data &data, Clane &cln) {
			if (cln.pos.x == 2) {
				if (!cln.R(data) && !cln.D(data))
					cln.dot(data);
			} else {
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
			}
		}
	) {
	// 下辺：左向レーン
	if (cln.pos.y == 4 && cln.pos.x > 1) {
		if (!cln.L(data)) {
			cln.dot(data);
		}
	// 右辺：下降レーン
	} else if (cln.pos.x == 4) {
		if (!cln.D(data)) {
			cln.dot(data);
		}
	// 左２辺：上昇レーン
	} else if (cln.pos.x <= 1 && cln.pos.y != 0) {
		if (cln.pos.x == 0) {
			if (!cln.U(data) && !cln.R(data)) {
				cln.dot(data);
			}
		} else {
			if (!cln.U(data)) {
				cln.dot(data);
			}
		}
	// 上辺：右向レーン
	} else if (cln.pos.y == 0) {
		if (!cln.R(data)) {
			cln.dot(data);
		}
	// 中央：貯蔵
	} else {
		else_f(data, cln);
	}
}

void do_pick(Data &data, Clane &cln) {
	if (!cln.P(data)) {
		if (cln.pos.x == 1) {
			if (!cln.L(data)) {
				do_circulate(data, cln);
			}
		} else {
			do_circulate(data, cln);
		}
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (!cln.Q(data)) {
			cln.dot(data);
		}
	} else {
		// 第三引数で最適化の余地
		do_circulate(data, cln);
	}
}

void do_clane(Data &data, Clane &cln) {
	if (cln.has_con < 0) {
		do_pick(data, cln);
	} else {
		do_export(data, cln);
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
