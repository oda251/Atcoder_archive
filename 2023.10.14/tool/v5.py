from collections import namedtuple
import math
from copy import deepcopy
from random import randint, shuffle

NUM = 2
N, D, Q = map(int, input().split())
INI_Q = Q
_ = math.ceil(math.log2(D))
C = math.floor(Q / (2 ** _ - 1))
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

def output(groups, seed):
	for i in range(N):
		for j, g in enumerate(groups):
			if str(i) in g:
				if (i < N - 1):
					print(str(j), end=" ")
				else:
					if len(seed):
						print(str(j), end=" ")
					else:
					print(str(j))
				break
	if len(seed):
		for i, n in enumerate(seed):
			if (i < len(seed) - 1):
				print(str(n), end=" ")
			else:
				print(str(n))

def c_output(groups, seed):
	print("#c ", end="")
	output(groups, seed)

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

	if (len(groups) == 1):
		return
	if (len(groups) == 2):
		if not Q:
			return groups
		r = query(groups[0], groups[1])
		if (r == ">"):
			groups[0], groups[1] = groups[1], groups[0]
		return groups
	else:
		return marge_sort(groups)

def set_mid(g0, start, end):
	global Q

	mid = (start + end) // 2
	g1 = g0[:mid]
	g2 = g0[mid:]
	if end - start <= 1:
		return [g1, g2]
	if (not Q):
		return [o1, o2]
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
		g1, g2 = deepcopy(o1), deepcopy(o2)
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
	switched = False
	if len(g1) < len(g2):
		g1, g2 = g2, g1
		switched = True
	NUM2 = len(g1) // len(g2)
	if NUM2 >= len(g1):
		if len(g1) != 1:
			NUM2 = len(g1) - 1
		else:
			if switched:
				return g2, g1
			return g1, g2
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
	if switched:
		return g2, g1
	return g1, g2

groups = [[] for _ in range(D)]
for i in range(N):
	groups[i % D].append(str(i))

for _ in range(2):
	new = sort_groups(deepcopy(groups))
	if Q:
		groups = new
	c_output(groups)
	for i in range(D // 2):
		if _ == 0:
			groups[i], groups[-i - 1] = set_mid(groups[i] + groups[-i - 1], 0, len(groups[i]) + len(groups[-i - 1]))
		else:
			groups[i], groups[-i - 1] = aver_move(groups[i], groups[-i - 1])
	c_output(groups)
	shuffle_groups(groups)

# for _ in range(2):
# 	new = sort_groups(deepcopy(groups))
# 	if Q:
# 		groups = new
# 	groups[0], groups[-1] = aver_swap(groups[0], groups[-1])
# 	c_output(groups)
# 	shuffle_groups(groups)

# for _ in range(2):
# 	new = sort_groups(deepcopy(groups))
# 	if Q:
# 		groups = new
# 	for i in range(D // 2):
# 		groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
# 	c_output(groups)
# 	shuffle_groups(groups)

# index = 0
# same = 0
# while Q:
# 	pre_g = [set(_) for _ in groups]
# 	new = sort_groups(deepcopy(groups))
# 	if Q:
# 		groups = new
# 	print("#c ", end="")
# 	output(groups)
# 	i = 0
# 	while i < len(groups) // 2:
# 		tmp = set_mid(groups[i] + groups[-i - 1], 0, len(groups[i]) + len(groups[-i - 1]))
# 		if Q:
# 			groups[i], groups[-i - 1] = tmp
# 		if INI_Q < N * 16:
# 			if N // D > 20:
# 				None
# 			elif i <= 0:
# 				groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
# 		else:
# 			groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
# 		shuffle(groups[i])
# 		shuffle(groups[-i - 1])
# 		i += 1
# 	index += 1
# 	if [set(_) for _ in groups] == pre_g:
# 		same += 1
# 		if same > 2 and D == 2:
# 			break
# 		if same > 100:
# 			break
# 	else:
# 		same = 0

# while Q and D > 2:
# 	if True:
# 		i = randint(0, D // 2)
# 		j = randint(i + 1, D - 1)
# 		tmp = average_pair(groups[i] + groups[j], 0, len(groups[i]) + len(groups[j]))
# 		if Q:
# 			groups[i], groups[j] = tmp
# 	pre_g = [set(_) for _ in groups]
# 	new = sort_groups(deepcopy(groups))
# 	if Q:
# 		groups = new
# 	print("#c ", end="")
# 	output(groups)
# 	i = randint(1, 2) * -1
# 	groups[0], groups[i] = aver_swap(groups[0], groups[i])
# 	shuffle(groups[0])
# 	shuffle(groups[i])
# 	i = randint(1, 2) * -1
# 	groups[1], groups[i] = aver_swap(groups[1], groups[i])
# 	shuffle(groups[1])
# 	shuffle(groups[i])
# 	index += 1
# 	if [set(_) for _ in groups] == pre_g:
# 		same += 1
# 		if same > 100:
# 			break

while Q:
	print(1, 1, 0, 1)
	Q -= 1
output(groups)