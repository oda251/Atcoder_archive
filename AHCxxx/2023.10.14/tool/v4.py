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

def output(groups):
	for i in range(N):
		for j, g in enumerate(groups):
			if str(i) in g:
				if (i < N - 1):
					print(str(j), end=" ")
				else:
					print(str(j))
				break

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
	mid = (start + end) // 2
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

def average_pair(g0, start, end):
	global Q

	res = set_mid(g0, start, end)
	if Q > 0:
		i = 0
		while (Q > 0):
			if (len(res[1]) <= 2):
				return res
			tmp = [deepcopy(res[0]), deepcopy(res[1])]
			tmp[0].append(tmp[1].pop(i))
			r = query(tmp[0], tmp[1])
			if r == "<":
				res = tmp
			if r == "=":
				return tmp
			i += 1
			if i >= len(res[1]):
				break
			
	return res

def aver_swap(g1, g2):
	if len(g1) > len(g2):
		NUM2 = len(g1) // len(g2)
		NUM2 = randint(max(1, NUM2 - 1), NUM2)
		if NUM2 < 1:
			NUM2 = 1
		for j in range((len(g1) - NUM2)):
			if Q > NUM2:
				for i in range(len(g2)):
					if not Q:
						break
					if j > len(g1) - NUM2:
						break
					if query(g1[j:j + NUM2], [g2[i]]) == "<":
						tmp1 = deepcopy(g1)
						tmp2 = deepcopy(g2)
						tmp1.append(tmp2.pop(i))
						trimmed = tmp1[j:j + NUM2]
						for _ in range(NUM2):
							tmp1.pop(j)
						tmp2.extend(trimmed)
						if not Q:
							break
						if query(tmp1, tmp2) == "<":
							g1 = tmp1
							g2 = tmp2
							return g1, g2
	return g1, g2

groups = [[] for _ in range(D)]
for i in range(N):
	groups[i % D].append(str(i))

index = 0
same = 0
while Q:
	pre_g = [set(_) for _ in groups]
	new = sort_groups(deepcopy(groups))
	if Q:
		groups = new
	print("#c ", end="")
	output(groups)
	i = 0
	while i < len(groups) // 2:
		tmp = average_pair(groups[i] + groups[-i - 1], 0, len(groups[i]) + len(groups[-i - 1]))
		if Q:
			groups[i], groups[-i - 1] = tmp
		if INI_Q < N * 16:
			if N // D > 20:
				None
			elif i <= 0:
				groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
		else:
			groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
		shuffle(groups[i])
		shuffle(groups[-i - 1])
		i += 1
	index += 1
	if [set(_) for _ in groups] == pre_g:
		same += 1
		if same > 2 and D == 2:
			break
		if same > 100:
			break
	else:
		same = 0

while Q and D > 2:
	if True:
		i = randint(0, D // 2)
		j = randint(i + 1, D - 1)
		tmp = average_pair(groups[i] + groups[j], 0, len(groups[i]) + len(groups[j]))
		if Q:
			groups[i], groups[j] = tmp
	pre_g = [set(_) for _ in groups]
	new = sort_groups(deepcopy(groups))
	if Q:
		groups = new
	print("#c ", end="")
	output(groups)
	i = randint(1, 2) * -1
	groups[0], groups[i] = aver_swap(groups[0], groups[i])
	shuffle(groups[0])
	shuffle(groups[i])
	i = randint(1, 2) * -1
	groups[1], groups[i] = aver_swap(groups[1], groups[i])
	shuffle(groups[1])
	shuffle(groups[i])
	index += 1
	if [set(_) for _ in groups] == pre_g:
		same += 1
		if same > 100:
			break

while Q:
	print(1, 1, 0, 1)
	Q -= 1
output(groups)