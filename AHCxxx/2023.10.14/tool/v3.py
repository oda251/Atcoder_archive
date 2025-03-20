from collections import namedtuple
import math
from copy import deepcopy

NUM = 2
NUM2 = 2
N, D, Q = map(int, input().split())
INI_Q = Q
_ = math.ceil(math.log2(D))
C = math.floor(Q / (2 ** _ - 1))
memory = {}

def compare():
	global Q
	Q -= 1
	return (input())

def query(g1, g2):
	global Q

	switched = False
	if g1 > g2:
		switched = True
		g1, g2 = g2, g1
	tp = (tuple(g1), tuple(g2))
	for m in memory.keys():
		if tp == m:
			if switched:
				if memory[m] == ">":
					return "<"
				elif memory[m] == "<":
					return ">"
				else:
					return "="
			return memory[m]
	if not Q:
		return
	q = f'{len(g1)} {len(g2)} {" ".join(g1)} {" ".join(g2)}'
	print(q)
	r = compare()
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

def quick_sort(groups, start, end):
	global Q

	if (end - start <= 1):
		return
	pivot = start
	i = start + 1
	while i < end:
		if not Q:
			return
		if (query(groups[pivot], groups[i]) == ">"):
			groups.insert(start, groups.pop(i))
			pivot += 1
		i += 1
	quick_sort(groups, start, pivot)
	quick_sort(groups, pivot + 1, end)

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

# def shell_sort(groups):
# 	global Q

# 	for i in range((len(groups) // 4) + 1)

def sort_groups(groups):
	global Q

	if (len(groups) == 1):
		return groups
	if (len(groups) == 2):
		if not Q:
			return groups
		r = query(groups[0], groups[1])
		if (r == ">"):
			groups[0], groups[1] = groups[1], groups[0]
	# elif (len(groups) < 12):
		# groups = shell_sort(groups)
	else:
		# quick_sort(groups, 0, len(groups))
		groups = marge_sort(groups)
	return groups

# 二分法
def ave_sub(g0, start, end):
	mid = (start + end) // 2
	g1 = g0[:mid]
	g2 = g0[mid:]
	if end - start <= 1:
		return [g1, g2]
	if (not Q):
		return [g1, g2]
	res = query(g1, g2)
	if res == "<":
		return ave_sub(g0, mid, end)
	elif res == ">":
		return ave_sub(g0, start, mid)
	else:
		return [g1, g2]

def average_pair(g0, start, end):
	global Q
	res = ave_sub(g0, start, end)
	if Q > 0:
		if (len(res[0]) == 0 or len(res[1]) == 0):
			return res
		i = 0
		while (Q > 0):
			if (len(res[1]) <= 1):
				return res
			tmp = [deepcopy(res[0]), deepcopy(res[1])]
			tmp[0].append(tmp[1].pop(i))
			r = query(tmp[0], tmp[1])
			if r == "<" or r == "=":
				res = tmp
			if r == "=":
				return res
			if N // D > 20:
				i += 2
			else:
				i += 1
			if i >= len(res[1]):
				break
			
	return res

def aver_swap(g1, g2):
	if len(g1) > len(g2) and len(g1) > NUM2:
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
						r = query(tmp1, tmp2)
						if r == "<" or r == "=":
							g1 = tmp1
							g2 = tmp2
							return g1, g2
	else:
		for j in range(len(g1) // NUM):
			if Q > NUM:
				for i in range(len(g2) // NUM):
					if not Q:
						break
					if query([g1[j * NUM]], [g2[i * NUM]]) == "<":
						tmp1 = deepcopy(g1)
						tmp2 = deepcopy(g2)
						tmp1.append(tmp2.pop(i * NUM))
						tmp2.append(tmp1.pop(j * NUM))
						if not Q:
							break
						r = query(tmp1, tmp2)
						if r == "<" or r == "=":
							g1 = tmp1
							g2 = tmp2
	return g1, g2

groups = [[] for _ in range(D)]
for i in range(N):
	groups[i % D].append(str(i))

index = 0
while Q:
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
				if i <= 0:
					groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
			else:
				groups[i], groups[-i - 1] = aver_swap(groups[i], groups[-i - 1])
			groups[i].insert(0, groups[i].pop())
			groups[-i - 1].insert(0, groups[-i - 1].pop())
			i += 1
		index += 1

while Q:
	print(1, 1, 0, 1)
	Q -= 1

output(groups)