#include "type.cpp"

void do_circulate(Data &data, Clane &cln,
		function<void(Data &, Clane &)> else_f = [](Data &data, Clane &cln) {
			if (cln.pos.x == 2) {
				switch (cln.pos.y) {
					case 1:
						if (!cln.R(data) && !cln.U(data) && !cln.D(data))
							cln.dot(data);
						break;
					case 2:
						if (!cln.R(data) && !cln.D(data) && !cln.L(data))
							cln.dot(data);
						break;
					case 3:
						if (!cln.R(data) && !cln.D(data))
							cln.dot(data);
						break;
				}
			} else {
				switch (cln.pos.y) {
					case 1:
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 2:
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 3:
						if (!cln.R(data) && !cln.D(data) && !cln.U(data))
							cln.dot(data);
						break;
				}
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

void do_store(Data &data, Clane &cln) {
	int leftmask = (1 << 7) | (1 << 12) | (1 << 17);
	int rightmask = (1 << 8) | (1 << 13) | (1 << 18);
	if (cln.pos.x == 1 && cln.pos.y < 4 && (data.storage & leftmask) != leftmask) {
		if (!cln.R(data)) {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x == 2) {
		if (cln.pos.y == 0) {
			if ((data.storage & leftmask) != leftmask && cln.D(data)) {
			} else {
				do_circulate(data, cln);
			}
		} else if (cln.pos.y == 4) {
			do_circulate(data, cln);
		} else {
			if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {
			} else if (cln.pos.y < 3 && data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {
			} else if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				do_circulate(data, cln);
			}
		}
	} else if (cln.pos.x == 3) {
		if (cln.pos.y == 0) {
			do_circulate(data, cln);
		} else if (cln.pos.y == 4) {
			if ((data.storage & rightmask) != rightmask && cln.U(data)) {
			} else {
				do_circulate(data, cln);
			}
		} else {
			if (cln.pos.y > 1 && data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {
			} else if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				do_circulate(data, cln);
			}
		}
	} else if (cln.pos.x == 4 && cln.pos.y > 0 && (data.storage & rightmask) != rightmask) {
		if (!cln.L(data)) {
			do_circulate(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_pick(Data &data, Clane &cln) {
	if ((cln.pos.x == 0 && cln.pos.y == cln.tgt.pos)
		|| data.map[cln.pos.y][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.P(data)) {
			if ((cln.tgt.con != cln.has_con || (cln.tgt.con == cln.has_con && cln.tgt.dist != 0))
				&& (data.wanted & (1 << cln.has_con))) {
				for (auto &c: data.clanes) {
					if (c.tgt.dist == 0 && c.tgt.con == cln.has_con) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			} else if (cln.tgt.dist == 0 && cln.tgt.con != cln.has_con) {
				for (auto &c: data.clanes) {
					if (c.tgt.pos == cln.tgt.pos && c.tgt.dist > 0) {
						Target tmp;
						tmp = c.tgt;
						if (c.tgt.pos == 5 && cln.pos.x == 0) {
							c.is_working = false;
						}
						c.tgt = cln.tgt;
						cln.tgt = tmp;
						break;
					}
				}
			}
		} else {
			cln.is_working = false;
			do_circulate(data, cln);
		}
	} else if (cln.tgt.pos == 5) {
		if (cln.pos.y > 0) {
			switch (cln.pos.x) {
				case 1:
					if (cln.pos.y >= 2) {
						if (!cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.R(data))
							cln.dot(data);
					}
					break;
				case 2:
					switch (cln.pos.y) {
						case 4:
							do_circulate(data, cln);
							break;
						case 3:
							if (!cln.R(data))
								cln.dot(data);
							break;
						default:
							if (!cln.D(data))
								cln.dot(data);
					}
					break;
				case 3:
					switch (cln.pos.y) {
						case 4:
							do_circulate(data, cln);
							break;
						default:
							if (!cln.U(data))
								cln.dot(data);
					}
					break;
				default:
					do_circulate(data, cln);
			}
		} else {
			do_circulate(data, cln);
		}
	} else {
		switch(cln.pos.x) {
			case 0:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 1:
				if (cln.pos.y == 0) {
					if (!cln.R(data))
						cln.dot(data);
				} else if (cln.pos.y == 4) {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				if (cln.pos.y == 4) {
					if (!cln.L(data))
						cln.dot(data);
				} else {
					if (!cln.D(data))
						cln.dot(data);
				}
				break;
			default:
				do_circulate(data, cln);
		}
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4
		&& (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))) {
		if (cln.Q(data)) {
			cln.is_working = false;
		} else {
			cln.dot(data);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_clane(Data &data, Clane &cln) {
	if (cln.is_broken)
		return;
	if (cln.is_working) {
		if (cln.has_con < 0)
			do_pick(data, cln);
		else if (cln.has_con == cln.tgt.con)
			do_export(data, cln);
		else
			do_store(data, cln);
	} else {
		do_circulate(data, cln);
	}
}

void sim(Data &data) {
	while (data.turn < MAX_TURN) {
		for (auto &cln: data.clanes) {
			if (!cln.is_working) {
				if (data.plan.plan.size() > 0) {
					Target &tgt = data.plan.plan.front();
					data.wanted |= 1 << tgt.con;
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						data.plan.plan.pop_front();
					}
					//cerr << "tgt, cln: " << tgt.con << " " << cln.index << " | turn: " << data.turn << " | pos: " << cln.tgt.pos << endl;
					cln.is_working = true;
				} else {
					cln.B(data);
				}
			}
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
