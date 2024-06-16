#include "type.cpp"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);

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
			//if (!cln.U(data) && !cln.R(data)) {
			if (!cln.R(data) && !cln.U(data)) {
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

void do_store2(Data &data, Clane &cln) {
	switch (cln.pos.x) {
		case 0:
			if (!cln.R(data))
				cln.dot(data);
			break;
		case 1:
			switch (cln.pos.y) {
				case 4:
					if (!cln.U(data))
						cln.dot(data);
					break;
				case 0:
					if (!cln.R(data))
						cln.dot(data);
					break;
				default:
					if ((data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 || data.map[cln.pos.y][cln.pos.x + 2].is_con < 0)
						&& cln.R(data)) {}
					else if (!cln.U(data))
						cln.dot(data);
			}
			break;
		case 2:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 3:
					if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {}
					else if (!cln.Q(data) && !cln.D(data))
						cln.dot(data);
					break;
				case 4:
					if (data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {}
					else {
						if (!cln.L(data))
							cln.dot(data);
					}
					break;
				default:
					if (data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {}
					else if (data.map[cln.pos.y][cln.pos.x + 1].is_con < 0 && cln.R(data)) {}
					else if (!cln.Q(data) && !cln.D(data) && !cln.R(data) && !cln.L(data))
						cln.dot(data);
			}
			break;
		case 3:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 3:
					if (!cln.Q(data) && !cln.D(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 4:
					if (data.map[cln.pos.y - 1][cln.pos.x].is_con < 0 && cln.U(data)) {}
					else {
						if (!cln.L(data))
							cln.dot(data);
					}
					break;
				default:
					if (data.map[cln.pos.y + 1][cln.pos.x].is_con < 0 && cln.D(data)) {}
					else if (!cln.Q(data) && !cln.D(data) && !cln.R(data))
						cln.dot(data);
			}
			break;
		case 4:
			switch (cln.pos.y) {
				case 0:
					if (!cln.D(data))
						cln.dot(data);
					break;
				case 4:
					if (!cln.L(data))
						cln.dot(data);
					break;
				default:
					if (data.map[cln.pos.y][cln.pos.x - 1].is_con < 0 && cln.L(data)) {}
					else {
						if (!cln.D(data))
							cln.dot(data);
					}
					break;
			}
			break;
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
	} else if (cln.pos.x > 0 && data.map[cln.pos.y][cln.pos.x - 1].is_con == cln.tgt.con) {
		if (cln.L(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x < 4 && data.map[cln.pos.y][cln.pos.x + 1].is_con == cln.tgt.con) {
		if (cln.R(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y > 0 && data.map[cln.pos.y - 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.U(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y < 4 && data.map[cln.pos.y + 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.D(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.tgt.pos == 5) {
		if (cln.pos.y > 0) {
			switch (cln.pos.x) {
				case 1:
					if (cln.pos.y <= 1) {
						if (!cln.R(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
					break;
				case 2:
					switch (cln.pos.y) {
						case 4:
							if (!cln.L(data))
								cln.dot(data);
							break;
						case 3:
							if (!cln.L(data) && !cln.D(data))
								cln.dot(data);
							break;
						default:
							if (!cln.D(data))
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
			default:
				if (cln.tgt.pos > cln.pos.y) {
					if (!cln.D(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.D(data))
						cln.dot(data);
				}
		}
	}
}

void do_pick2(Data &data, Clane &cln) {
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
	} else if (cln.pos.x > 0 && data.map[cln.pos.y][cln.pos.x - 1].is_con == cln.tgt.con) {
		if (cln.L(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.x < 4 && data.map[cln.pos.y][cln.pos.x + 1].is_con == cln.tgt.con) {
		if (cln.R(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y > 0 && data.map[cln.pos.y - 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.U(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.pos.y < 4 && data.map[cln.pos.y + 1][cln.pos.x].is_con == cln.tgt.con) {
		if (cln.D(data)) {
		} else {
			do_circulate(data, cln);
		}
	} else if (cln.tgt.pos == 5) {
		if (cln.pos.y > 0) {
			switch (cln.pos.x) {
				case 1:
					if (cln.pos.y <= 1) {
						if (!cln.R(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
					break;
				case 2:
					switch (cln.pos.y) {
						case 4:
							if (!cln.L(data))
								cln.dot(data);
							break;
						case 3:
							if (!cln.L(data) && !cln.D(data))
								cln.dot(data);
							break;
						default:
							if (!cln.D(data))
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
			default:
				if (cln.pos.x == 2 && cln.tgt.pos > cln.pos.y) {
					if (!cln.D(data))
						cln.dot(data);
				} else {
					if (!cln.L(data) && !cln.D(data))
						cln.dot(data);
				}
		}
	}
}

bool min_export(Data &data, Clane &cln) {
	if (cln.pos.y < cln.has_con / N)
		return (cln.D(data) || cln.R(data));
	else if (cln.pos.y > cln.has_con / N) 
		return (cln.U(data) || cln.R(data));
	else {
		return cln.R(data);
	}
}

void do_export(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	//} else if (data.exported_count > 20) {
	//	if (!min_export(data, cln)) {
	//		do_circulate(data, cln);
	//	}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

void do_export2(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void do_export3(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	} else if (data.exported_count > 20) {
		if (!min_export(data, cln)) {
			do_circulate(data, cln);
		}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

void do_export4(Data &data, Clane &cln) {
	if (cln.pos.y == cln.has_con / N && cln.pos.x == 4) {
		if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1)))) {
			if (cln.Q(data)) {
				cln.is_working = false;
			} else {
				cln.dot(data);
			}
		} else {
			do_circulate(data, cln);
		}
	//} else if (data.exported_count > 20) {
	//	if (!min_export(data, cln)) {
	//		do_circulate(data, cln);
	//	}
	} else {
		if (cln.pos.y == 4) {
			switch (cln.pos.x) {
				case 0:
					if (!cln.U(data) && !cln.R(data))
						cln.dot(data);
					break;
				case 1:
					if (!cln.U(data))
						cln.dot(data);
					break;
				default:
					if (!cln.L(data))
						cln.dot(data);
			}
			return;
		} else if (cln.pos.y == 0) {
			if (cln.pos.x == 4) {
				if (!cln.D(data))
					cln.dot(data);
			} else if (!cln.R(data))
				cln.dot(data);
			return;
		}
		switch (cln.pos.x) {
			case 0:
				if (!cln.R(data) && !cln.U(data))
					cln.dot(data);
				break;
			case 1:
				if (cln.tgt.con / N >= cln.pos.y) {
					SquareState right = data.map[cln.pos.y][cln.pos.x + 1];
					SquareState right2 = data.map[cln.pos.y][cln.pos.x + 2];
					if (cln.is_large) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else if ((right.is_con < 0 && right2.is_con < 0)
						&& ((!right.is_clane || right.is_clane->tgt.dist == 0) && (!right2.is_clane || right2.is_clane->tgt.dist == 0))
					) {
						if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
					} else {
						if (!cln.U(data))
							cln.dot(data);
					}
				} else {
					if (!cln.U(data))
						cln.dot(data);
				}
				break;
			case 2:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data) && !cln.U(data))
							cln.dot(data);
						break;
					case 2:
						if (cln.tgt.con / N < 2) {
							if (!cln.U(data) && !cln.R(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (cln.tgt.con / N == cln.pos.y) {
							if (!cln.R(data))
								cln.dot(data);
						} else if (cln.tgt.con / N > cln.pos.y) {
							if (!cln.R(data) && !cln.D(data))
								cln.dot(data);
						} else {
							if (!cln.D(data) && !cln.L(data) && !cln.R(data))
								cln.dot(data);
						}
						break;
				}
				break;
			case 3:
				switch (cln.pos.y) {
					case 1:
						if (cln.tgt.con / N == 0) {
							if (!cln.U(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					case 2:
						if (cln.tgt.con / N < 2) {
							if (!cln.U(data) && !cln.R(data))
								cln.dot(data);
						} else if (!cln.R(data))
							cln.dot(data);
						break;
					default:
						if (!cln.R(data))
							cln.dot(data);
						break;
				}
				break;
			case 4:
				if (!cln.D(data))
					cln.dot(data);
				break;
		}
	}
}

bool wait_export(Data &data, Clane &cln) {
	switch (cln.pos.x) {
		case 0:
			cln.dot(data);
			return true;
		case 1:
			switch (cln.pos.y) {
				case 4:
					if (cln.L(data))
						return true;
					break;
				default:
					if (cln.L(data))
						return true;
					else if (cln.R(data))
						return false;
			}
			break;
		case 2:
			switch (cln.pos.y) {
				case 0:
					if (cln.D(data))
						return false;
					break;
				case 4:
					if (cln.U(data))
						return false;
					break;
				default:
					cln.dot(data);
					return true;
			}
			break;
		case 3:
			switch (cln.pos.y) {
				case 0:
					if (cln.D(data))
						return false;
					break;
				case 4:
					if (cln.U(data))
						return false;
					break;
				default:
					cln.dot(data);
					return true;
			}
			break;
		default:
			if (0 < cln.pos.y && cln.pos.y < 4) {
				if (cln.L(data))
					return false;
			}
	}
	data.dexport(data, cln);
	return false;
}

void do_clane(Data &data, Clane &cln){
	if (cln.is_broken)
		return;
	if (cln.is_working) {
		if (cln.has_con < 0)
			data.dpick(data, cln);
		else if (cln.has_con == cln.tgt.con) {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				data.dexport(data, cln);
			else {
				if (cln.pos.y == cln.tgt.con / N && cln.pos.x == 4)
					data.passed_log.push_back({data.turn, cln.tgt, cln.index});
				//do_circulate(data, cln);
				data.dexport(data, cln);
			}
		} else {
			if (cln.has_con % N == 0 || (data.exported & (1 << (cln.has_con - 1))))
				data.dexport(data, cln);
			else
				data.dstore(data, cln);
		}
	} else {
		do_circulate(data, cln);
	}
}

void sim(Data &data) {
	while (data.turn < 250) {
		for (auto &cln: data.clanes) {
			if (!cln.is_working) {
				label:
				if (data.plan.plan.size() > 0) {
					Target &tgt = data.plan.plan.front();
					data.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: data.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								data.plan.plan.pop_front();
								goto label;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						data.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(data);
				}
			}
			do_clane(data, cln);
			//if (cln.actions.size() != data.turn + 1 && cln.actions[cln.actions.size() - 1] != 'B') {
				//cerr << "cln: " << cln.index << " | turn: " << data.turn << " | pos: " << cln.pos.y << " " << cln.pos.x << "|tgt: " << cln.tgt.con << endl;
			//}
		}
		for (auto &cln: data.clanes) {
			if (cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(data, cln);
			}
		}
		data.proceed();
		if (data.remain_con == 0)
			break;
	}
}

bool sim_kaizen(Data &dest, Data &src, TargetLog log, int padding = 0) {
	int prev_arive_turn;
	int turn_to_wait;
	// log.cln_iがtgtをlog.tgt.conにするまで進める
	while (dest.clanes[log.cln_i].tgt != log.tgt && dest.turn < 250) {
		for (auto &cln: dest.clanes) {
			if (!cln.is_working) {
				labbel:
				if (dest.plan.plan.size() > 0) {
					Target &tgt = dest.plan.plan.front();
					dest.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: dest.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								dest.plan.plan.pop_front();
								goto labbel;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						dest.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(dest);
				}
			}
			do_clane(dest, cln);
		}
		for (auto &cln: dest.clanes) {
			if (cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(dest, cln);
			}
		}
		dest.proceed();
		if (dest.remain_con == 0)
			break;
	}
	if (dest.turn == 250)
		return false;
	// 必要な計算
	prev_arive_turn = src.exported_turn[log.tgt.con];
	turn_to_wait = src.exported_turn[log.tgt.con - 1] - log.turn + padding;
	// log.cln_i以外はそのまま、log.cln_iのみ待機を試しながら進める
	while (dest.turn < prev_arive_turn && !(dest.exported & (1 << log.tgt.con))) {
		for (auto &cln: dest.clanes) {
			if (cln.index == log.cln_i) {
				if (turn_to_wait > 0) {
					if (wait_export(dest, dest.clanes[log.cln_i])) {
						turn_to_wait--;
					}
				} else {
					do_clane(dest, dest.clanes[log.cln_i]);
				}
				continue;
			}
			if (!cln.is_working) {
				labbbel:
				if (dest.plan.plan.size() > 0) {
					Target &tgt = dest.plan.plan.front();
					dest.wanted |= 1 << tgt.con;
					if (tgt.dist == 0) {
						for (auto &c: dest.clanes) {
							if (c.has_con == tgt.con) {
								c.tgt = tgt;
								dest.plan.plan.pop_front();
								goto labbbel;
							}
						}
					}
					cln.tgt = tgt;
					if (tgt.dist > 0) {
						tgt.dist--;
					} else {
						dest.plan.plan.pop_front();
					}
					cln.is_working = true;
				} else {
					cln.B(dest);
				}
			}
			do_clane(dest, cln);
		}
		for (auto &cln: dest.clanes) {
			if (cln.index != log.cln_i && cln.actions.back() == '.') {
				cln.actions.pop_back();
				do_clane(dest, cln);
			}
		}
		dest.proceed();
		if (dest.remain_con == 0)
			break;
	}
	// srcより到着ターンが早まったら入れ替え
	if (dest.exported_turn[log.tgt.con] >= prev_arive_turn)
		return false;
	sim(dest);
	if (dest.turn < src.turn) {
		src = dest;
		return true;
	}
	return false;
}

void kaizen(Data &initData, Data &data, vector<TargetLog> logs) {
	Data tmp;
	//cerr << "--- kaizen ---" << endl;
	labebel:
	//for (auto &log: logs) {
	//	cerr << "<" << log.cln_i << "," << log.tgt.con << ">" << " ";
	//}
	//cerr << endl;
	for (auto &log: logs) {
		for (int i=0; i<3; i++) {
			tmp = initData;
			tmp.dexport = data.dexport;
			tmp.dpick = data.dpick;
			tmp.dstore = data.dstore;
			if (data.plan_flag == 1)
				tmp.plan = tmp.plan2;
			if (sim_kaizen(tmp, data, log, i)) {
				DEBUG(data.turn);
				logs = data.passed_log;
				goto labebel;
			}
		}
	}
}

void sims(Data &data) {
	Data best;
	int min_turn = INT_MAX;
	Data tmp;
	for (int i=0; i<2; i++) {
	for (int j=0; j<2; j++) {
	for (int k=0; k<4; k++) {
	for (int l=0; l<2; l++) {
		tmp = data;
		if (i == 0)
			tmp.plan_flag = 0;
		else {
			tmp.plan = tmp.plan2;
			tmp.plan_flag = 1;
		}
		if (j == 0)
			tmp.dstore = do_store;
		else
			tmp.dstore = do_store2;
		if (k == 0)
			tmp.dexport = do_export;
		else if (k == 1)
			tmp.dexport = do_export2;
		else if (k == 2)
			tmp.dexport = do_export3;
		else
			tmp.dexport = do_export4;
		if (l == 0)
			tmp.dpick = do_pick;
		else
			tmp.dpick = do_pick2;
		//cerr << "--- sim ---" << endl;
		sim(tmp);
		//cerr << "turn: " << tmp.turn << endl;
		if (tmp.turn < 250)
			kaizen(data, tmp, tmp.passed_log);
		if (tmp.turn < min_turn) {
			best = tmp;
			min_turn = tmp.turn;
		}
	}}}}
	//kaizen(data, best, best.passed_log);
	data = best;
}

int main() {
	clock_t start = clock();
	Data data;
	data.input();
	sims(data);
	data.output();
	clock_t end = clock();
	cerr << "time: " << (double)(end - start) / 1000 << "ms" << endl;
	return 0;
}
