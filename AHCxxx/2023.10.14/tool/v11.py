from collections import namedtuple
from math import log2, ceil, floor
from copy import deepcopy
from random import randint, shuffle, sample

NUM = 2
N, D, Q = map(int, input().split())
INI_Q = Q
memory = {}

def query(g1, g2):
	global Q
	global memory

	switched = False
	if g1 > g2:
		switched = True
		g1, g2 = g2, g1
	tp = (str(set(g1)), str(set(g2)))
	if tp in memory.keys():
		if switched:
			if memory[tp] == ">":
				return "<"
			elif memory[tp] == "<":
				return ">"
			else:
				return "="
		return memory[tp]
	if Q < 1:
		return
	q = f'{len(g1)} {len(g2)} {" ".join(g1)} {" ".join(g2)}'
	print(q)
	Q -= 1
	r = input()
	memory[tp] = r
	if switched:
		if r == ">":
			return "<"
		elif r == "<":
			return ">"
		else:
			return "="
	return r

def output(groups):
	for i in range(N):
		for j, g in enumerate(groups):
			if str(i) in g:
				if (i < N - 1):
					print(str(j), end=" ")
				else:
					print(str(j))
				break

def comment(com):
	print("# " + str(com))

def c_output(groups):
	print("#c ", end="")
	output(groups)

def shuffle_groups(groups):
	for g in groups:
		shuffle(g)

def marge(g1, g2):
	global Q
	i = 0
	j = 0
	dest = []

	while i < len(g1) and j < len(g2):
		if Q > 0:
			r = query(g1[i], g2[j])
			if r == "<":
				dest.append(g1[i])
				i += 1
			elif r == ">":
				dest.append(g2[j])
				j += 1
			else:
				dest.append(g1[i])
				dest.append(g2[j])
				i += 1
				j += 1
		else:
			break
	if i < len(g1):
		dest.extend(g1[i:])
	if j < len(g2):
		dest.extend(g2[j:])
	return dest

def marge_sort(groups):
	global Q

	divided = [[_] for _ in groups]
	while Q > 0:
		new = []
		if Q > 0 and len(divided) % 2 == 1:
			new.append(divided.pop())
		for i in range(len(divided) // 2):
			if Q > 0:
				new.append(marge(divided[i * 2], divided[i * 2 + 1]))
		divided = new
		if len(divided) == 1:
			break
	return divided[0]

def sort_groups(groups):
	global Q
	global D

	if (D == 1):
		return
	if (D == 2):
		if not Q:
			return groups
		r = query(groups[0], groups[1])
		if (r == ">"):
			groups[0], groups[1] = groups[1], groups[0]
		return groups
	else:
		return marge_sort(groups[:D]) + groups[D:]

def sort_one(groups):
	new = sort_groups(groups)
	if Q:
		return new
	else:
		return groups

def sort_two(g1, g2):
	g1 = sort_one(g1)
	g2 = sort_one(g2)
	return g1, g2

def set_mid(g0, start, end):
	global Q

	mid = (start + end) // 2
	if mid == 0:
		return [g0[:1], g0[1:]]
	elif mid == len(g0):
		return [g0[:-1], g0[-1:]]
	g1 = g0[:mid]
	g2 = g0[mid:]
	if end - start <= 1:
		return [g1, g2]
	if (not Q):
		return [g1, g2]
	res = query(g1, g2)
	if res == "<":
		return set_mid(g0, mid, end)
	elif res == ">":
		return set_mid(g0, start, mid)
	else:
		return [g1, g2]

def aver_move(o1, o2):
	global Q

	i = 0
	while (Q > 0):
		if (len(o2) <= 1):
			return o1, o2
		g1, g2 = o1[:], o2[:]
		g1.append(g2.pop(i))
		r = query(g1, g2)
		if r == "<" or r == "=":
			o1, o2 = g1, g2
			i -= 1
		if r == "=":
			return o1, o2
		i += 1
		if i >= len(o2):
			return o1, o2
	return o1, o2

def aver_swap_detail(g1, g2):
	if len(g1) == 1 or len(g2) == 1:
		return g1, g2
	switched = False
	if len(g1) < len(g2):
		g1, g2 = g2, g1
		switched = True
	NUM2 = len(g1) // len(g2)
	if NUM2 >= len(g1):
		if len(g1) != 1:
			NUM2 = len(g1) - 1
	for _ in range(NUM2 + 1):
		for j in range((len(g1) - NUM2)):
			if Q <= NUM2 or j + NUM2 >= len(g1):
				break
			for i in range(len(g2)):
				if Q < 2:
					break
				if query(g1[j:j + NUM2], [g2[i]]) == "<":
					tmp1 = g1[:]
					tmp2 = g2[:]
					tmp1.append(tmp2.pop(i))
					trimmed = tmp1[j:j + NUM2]
					for _ in range(NUM2):
						tmp1.pop(j)
					tmp2.extend(trimmed)
					if query(tmp1, tmp2) == "<":
						g1 = tmp1
						g2 = tmp2
						break
		NUM2 -= 1
		if NUM2 < 1:
			break
	if switched:
		return g2, g1
	return g1, g2

def aver_swap_detail_neo(g1, g2):
	if len(g1) == 1 or len(g2) == 1:
		return g1, g2
	switched = False
	if len(g1) < len(g2):
		g1, g2 = g2, g1
		switched = True
	NUM2 = ceil(N // D / 2)
	if NUM2 > len(g1):
		if len(g1) != 1:
			NUM2 = len(g1) - 1
	for _ in range(NUM2 + 1):
		if NUM2 < 1:
			break
		for j in range((len(g1) - NUM2)):
			if Q <= NUM2 or j + NUM2 >= len(g1):
				break
			for i in range(len(g2)):
				if Q < 2:
					break
				if query(g1[j:j + NUM2], [g2[i]]) == "<":
					tmp1 = g1[:]
					tmp2 = g2[:]
					tmp1.append(tmp2.pop(i))
					trimmed = tmp1[j:j + NUM2]
					for _ in range(NUM2):
						tmp1.pop(j)
					tmp2.extend(trimmed)
					if query(tmp1, tmp2) == "<":
						g1 = tmp1
						g2 = tmp2
						break
		else:
			NUM2 -= 1
			continue
		break
	if switched:
		return g2, g1
	return g1, g2

def aver_swap_const(g1, g2, num):
	if len(g1) == 1 or len(g2) == 1 or num == 0:
		return g1, g2
	switched = False
	if len(g1) < len(g2):
		g1, g2 = g2, g1
		switched = True
	for j in range((len(g1) - num)):
		if Q <= num or j + num >= len(g1):
			break
		for i in range(len(g2)):
			if Q < 2:
				break
			if query(g1[j:j + num], [g2[i]]) == "<":
				tmp1 = g1[:]
				tmp2 = g2[:]
				tmp1.append(tmp2.pop(i))
				trimmed = tmp1[j:j + num]
				for _ in range(num):
					tmp1.pop(j)
				tmp2.extend(trimmed)
				if query(tmp1, tmp2) == "<":
					g1 = tmp1
					g2 = tmp2
					break
	if switched:
		return g2, g1
	return g1, g2

def aver_swap_neo(g1, g2):
	if len(g1) == 1 or len(g2) == 1:
		return g1, g2
	switched = False
	if len(g1) < len(g2):
		g1, g2 = g2, g1
		switched = True
	NUM2 = ceil(N // D / 2)
	if NUM2 >= len(g1):
		NUM2 = len(g1) - 1
	for _ in range(NUM2):
		if NUM2 < N // D // 3:
			break
		for j in range((len(g1) - NUM2)):
			if Q <= NUM2 or j + NUM2 >= len(g1):
				break
			for i in range(len(g2)):
				if Q < 2:
					break
				if query(g1[j:j + NUM2], [g2[i]]) == "<":
					tmp1 = g1[:]
					tmp2 = g2[:]
					tmp1.append(tmp2.pop(i))
					trimmed = tmp1[j:j + NUM2]
					for _ in range(NUM2):
						tmp1.pop(j)
					tmp2.extend(trimmed)
					if query(tmp1, tmp2) == "<":
						g1 = tmp1
						g2 = tmp2
						break
		else:
			NUM2 -= 1
			break
		break
	if switched:
		return g2, g1
	return g1, g2

def init_large_D(Q, D, N):
	t1 = [str(i) for i in range(N // 2)]
	t2 = [str(i) for i in range(N // 2, N)]
	t1, t2 = aver_move(t1, t2)
	g1 = [[] for _ in range(ceil(D / 2))]
	g2 = [[] for _ in range(ceil(D / 2))]
	for i, n in enumerate(t1):
		g1[i % (len(g1))].append(n)
	for i, n in enumerate(t2):
		g2[i % (len(g2))].append(n)
	g1, g2 = sort_two(g1, g2)
	if D % 2 == 1:
		g1[0].extend(g2.pop(0))
	for i in range(len(g1) // 2):
		g1[i], g2[-i - 1] = aver_move(g1[i], g2[-i - 1])
	for i in range(len(g2) // 2):
		g2[i], g1[-i - 1] = aver_move(g2[i], g1[-i - 1])
	comment("init_large_D")
	return g1, g2

def init_mid_D(Q, D, N):
	if N // D <= 10:
		g = [[] for _ in range(D)]
		for i in range(N):
			g[i % D].append(str(i))
		g = sort_one(g)
		for i in range(D // 4):
			g[i], g[-i - 1] = aver_swap_const(g[i], g[-i - 1], ceil(N // D / 2))
			g[i], g[-i - 1] = aver_move(g[i], g[-i - 1])
		return g
	else:
		if D <= 10:
			g = [[] for _ in range(D)]
			for i in range(N):
				g[i % D].append(str(i))
			g = sort_one(g)
			for i in range(D // 2):
				g[i], g[-i - 1] = set_mid(g[i] + g[-i - 1], 0, len(g[i]) + len(g[-i - 1]))
			g = sort_one(g)
			for i in range(D // 2):
				g[i], g[-i - 1] = aver_move(g[i], g[-i - 1])
		else:
			g = init_large_D(Q, D, N)
		return g

def solve_large_D(Q, D, N):
	g1, g2 = init_large_D(Q, D, N)
	g1[0], g2[-1] = aver_swap_const(g1[0], g2[-1], ceil(N // D / 2))
	g2[0], g1[-1] = aver_swap_const(g2[0], g1[-1], ceil(N // D / 2))
	c_output(g1 + g2)
	comment("init_large_D")
	g1, g2 = sort_two(g1, g2)
	c_output(g1 + g2)
	comment("sort_init")
	shuffle_groups(g1)
	shuffle_groups(g2)
	for i in range(2):
		# g1[i], g2[-i - 1] = aver_swap_const(g1[i], g2[-i - 1], ceil(N // D / 2))
		pre = g1[i] + g2[-i - 1]
		g1[i], g2[-i - 1] = aver_move(g1[i], g2[-i - 1])
		if pre == g1[i] + g2[-i - 1]:
			g1[i], g2[-i - 1] = aver_swap_const(g1[i], g2[-i - 1], ceil(N // D / 2))
		# g2[i], g1[-i - 1] = aver_swap_const(g2[i], g1[-i - 1], ceil(N // D / 2))
		pre = g2[i] + g1[-i - 1]
		g2[i], g1[-i - 1] = aver_move(g2[i], g1[-i - 1])
		if pre == g2[i] + g1[-i - 1]:
			g2[i], g1[-i - 1] = aver_swap_const(g2[i], g1[-i - 1], ceil(N // D / 2))
	comment("aver_swap_const")
	c_output(g1 + g2)
	pre_g = [set(g) for g in g1 + g2]
	same = 0
	comment("start_loop")
	while Q:
		g1, g2 = sort_two(g1, g2)
		c_output(g1 + g2)
		shuffle_groups(g1)
		shuffle_groups(g2)
		comment("sorted")
		for i in range(2):
			g1[i], g1[-i - 1] = aver_swap_detail_neo(g1[i], g1[-i - 1])
			g1[i], g1[-i - 1] = aver_move(g1[i], g1[-i - 1])
			g2[i], g2[-i - 1] = aver_swap_detail_neo(g2[i], g2[-i - 1])
			g2[i], g2[-i - 1] = aver_move(g2[i], g2[-i - 1])
		if pre_g == [set(g) for g in g1 + g2]:
			same += 1
			if same >= 2:
				break
		else:
			pre_g = [set(g) for g in g1 + g2]
			same = 0
	return g1 + g2

def solve_mid_D(Q, D, N):
	g = init_mid_D(Q, D, N)
	g = sort_one(g)
	comment("init_mid_D")
	c_output(g)
	index = 0
	pre_g = [set(g) for g in g]
	same = 0
	while Q:
		shuffle_groups(g)
		if index % 2 == 0:
			for i in range(D // 2):
				g[i], g[-i - 1] = aver_move(g[i], g[-i - 1])
		else:
			for i in range(max(D // 4, 1)):
				g[i], g[-i - 1] = aver_swap_const(g[i], g[-i - 1], ceil(N // D / 2))
		g = sort_one(g)
		c_output(g)
		if pre_g == [set(g) for g in g]:
			same += 1
			if same >= 2:
				break
		else:
			pre_g = [set(g) for g in g]
			same = 0
		index += 1
	return g

if D < 12:
	groups = solve_mid_D(Q, D, N)
else:
	groups = solve_large_D(Q, D, N)
c_output(groups)
comment("end_main_part")

pre_g = [set(g) for g in groups]
while Q:
	c_output(groups)
	shuffle_groups(groups)
	for i in range(D // 2):
		if not Q:
			break
		groups[i], groups[-i - 1] = aver_swap_detail_neo(groups[i], groups[-i - 1])
		groups[i], groups[-i - 1] = aver_move(groups[i], groups[-i - 1])
	c_output(groups)
	comment("yeah")
	if not Q:
		break
	groups = sort_one(groups)
	c_output(groups)
	comment("sorted")
	if pre_g == [set(g) for g in groups]:
		break
	else:
		pre_g = [set(g) for g in groups]
while Q:
	comment("end_second_part")
	shuffle_groups(groups)
	pre_g = [set(g) for g in groups]
	if D > 3:
		groups[0], groups[-2] = aver_swap_detail_neo(groups[0], groups[-2])
		groups[1], groups[-1] = aver_swap_detail_neo(groups[1], groups[-1])
		groups[0], groups[-1] = aver_move(groups[0], groups[-1])
		groups[1], groups[-2] = aver_move(groups[1], groups[-2])
	elif D == 3:
		aver_move(groups[0], groups[1])
		aver_move(groups[0], groups[2])
		aver_move(groups[1], groups[2])
		groups[0], groups[1] = aver_swap_detail_neo(groups[0], groups[1])
		groups[0], groups[2] = aver_swap_detail_neo(groups[0], groups[2])
		groups[1], groups[2] = aver_swap_detail_neo(groups[1], groups[2])
	groups = sort_one(groups)
	if pre_g == [set(g) for g in groups]:
		comment("end_part_3")
		break

while Q:
	print("1 1 0 1")
	Q -= 1
output(groups)