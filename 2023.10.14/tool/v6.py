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
	print("#c " + com)

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

def aver_swap(g1, g2):
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

def init(Q, D, N):
	if ceil(log2(D * 2) * (D * 2)) < Q // 4:
		groups = [[] for _ in range(D * 2)]
		for i, n in enumerate(sample(range(N), N)):
			groups[i % (D * 2)].append(str(n))
		groups = sort_groups(groups)
		for i in range(D // 2):
			groups[i], groups[-i - 1] = aver_move(groups[i], groups[-i - 1])
		groups = sort_groups(groups)
		for i in range(D):
			groups[i].extend(groups[-i - 1])
		groups = groups[:D]
		groups = sort_groups(groups)
		return groups
	elif ceil(log2(D) * D) < Q // 2:
		groups = [[] for _ in range(D)]
		for i, n in enumerate(sample(range(N), N)):
			groups[i % (D)].append(str(n))
		groups = sort_groups(groups)
		for i in range(D // 2):
			groups[i], groups[-i - 1] = aver_move(groups[i], groups[-i - 1])
		return groups
		# g1 = [[] for _ in range(D)]
		# g2 = [[] for _ in range(D)]
		# for i, n in enumerate(sample(range(N), N)):
		# 	if i % 2 == 0:
		# 		g1[(i // 2) % D].append(str(n))
		# 	else:
		# 		g2[(i // 2) % D].append(str(n))
		# g1 = sort_groups(g1)
		# g2 = sort_groups(g2)
		# for i in range(len(g1) // 2):
		# 	g1[i], g1[-i - 1] = aver_move(g1[i], g1[-i - 1])
		# for i in range(len(g2) // 2):
		# 	g2[i], g2[-i - 1] = aver_move(g2[i], g2[-i - 1])
		# for i, g in enumerate(g2):
		# 	g1[i % len(g1)].extend(g)
		# return g1
	else:
		t1 = [str(i) for i in sample(range(N // 2), N // 2)]
		t2 = [str(i) for i in sample(range(N // 2, N), N - N // 2)]
		t1, t2 = aver_move(t1, t2)
		g1 = [[] for _ in range(D // 2)]
		g2 = [[] for _ in range(D - len(g1))]
		for i, n in enumerate(t1):
			g1[i % (len(g1))].append(n)
		for i, n in enumerate(t2):
			g2[i % (len(g2))].append(n)
		g1 = sort_groups(g1)
		g2 = sort_groups(g2)
		for i in range(len(g1) // 2):
			g1[i], g1[-i - 1] = aver_move(g1[i], g1[-i - 1])
		for i in range(len(g2) // 2):
			g2[i], g2[-i - 1] = aver_move(g2[i], g2[-i - 1])
		g1.extend(g2)
		return g1

groups = init(Q, D, N)
c_output(groups)
for i in range(D // 2):
	if i == D - i - 1 or not Q:
		break
	try:
		if len(groups[D - i - 1]) == 1:
			groups.append(groups.pop(D - i - 1))
			D -= 1
	except:
		print(groups, D, i)
	groups[i], groups[D - i - 1] = aver_move(groups[i], groups[D - i - 1])
c_output(groups)

new = sort_groups(groups[:])
if Q:
	groups = new
c_output(groups)
for i in range(2):
	if i == D - i - 1 or not Q:
		break
	groups[i], groups[D - i - 1] = aver_move(groups[i], groups[D - i - 1])
	groups[i], groups[D - i - 1] = aver_swap(groups[i], groups[D - i - 1])
c_output(groups)

# count = 0
# same_c = 0
# pre_g = [set(_) for _ in groups]
# while Q:
# 	new = sort_groups(deepcopy(groups))
# 	if Q:
# 		groups = new
# 	c_output(groups)
# 	if count % 2 == 0 or (N // D > 10 and count < 2):
# 		for i in range(min(ceil(D / 4), D // 2)):
# 			if len(groups[D - i - 1]) == 1:
# 				groups.append(groups.pop(D - i - 1))
# 				D -= 1
# 			if i == D - i - 1 or not Q:
# 				break
# 			groups[i], groups[D - i - 1] = aver_move(groups[i], groups[D - i - 1])
# 	else:
# 		for i in range(min(2, D // 2)):
# 			if len(groups[D - i - 1]) == 1:
# 				groups.append(groups.pop(D - i - 1))
# 				D -= 1
# 			if i == D - i - 1 or not Q:
# 				break
# 			groups[i], groups[D - i - 1] = aver_swap(groups[i], groups[D - i - 1])
# 			if not Q:
# 				break
# 	c_output(groups)
# 	if pre_g == [set(_) for _ in groups]:
# 		same_c += 1
# 		if same_c > 2:
# 			break
# 	else:
# 		same_c = 0
# 		pre_g = [set(_) for _ in groups]
# 	count += 1
# 	if count >= 4:
# 		break


while Q:
	print(1, 1, 0, 1)
	Q -= 1
output(groups)